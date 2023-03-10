/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/

#include "AST.h"
#include "scanType.h"
#include "parser.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int WSC = 0;

//function adds a sibling
TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (t!=NULL) 
    {
        TreeNode *tmp;
        
        tmp = t;
        while (tmp->sibling!=NULL) tmp = tmp->sibling;
        tmp->sibling = s;
        return t;
    }
    return s;

    if(t == NULL){
        return s;   
    }
    else if(s == NULL){
        return t;
    }
}

// Function Passes the type attributes down the sibling list.
void setType(TreeNode *t, ExpType type){

    while (t != NULL) {
        t->expType = type;
        t = t->sibling;
    }

}
/* Function newDeclNode creates a new declaration
 * node for syntax tree construction
 */
TreeNode *newDeclNode(DeclKind kind, TokenData* token){
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if( t==NULL){
        printf("Out of memory error at line %d\n", token->lineno);
    }
    else{
        for(i=0; i<MAXCHILDREN; i++){
            t->child[i] = NULL;
            t->sibling = NULL;
            t->nodekind = DeclK;
            t->subkind.decl = kind;
            t->lineno = token->lineno;
            t->expType = Void;
            t->attr.name = strdup(token->tokenstr);
        }
    }

    return t;
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode *newStmtNode(StmtKind kind, TokenData *token){
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if( t==NULL){
        printf("Out of memory error at line %d\n", token->lineno);
    }
    else{
        for(i=0; i<MAXCHILDREN; i++){
            t->child[i] = NULL;
            t->sibling = NULL;
            t->nodekind = StmtK;
            t->subkind.stmt = kind;
            t->lineno = token->lineno;
            t->expType = Void;
            t->attr.name = strdup(token->tokenstr);
        }
    }

    return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode *newExpNode(ExpKind kind, TokenData *token){
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if( t==NULL){
        printf("Out of memory error at line %d\n", token->lineno);
    }  
    else{
        for(i=0; i<MAXCHILDREN; i++){
            t->child[i] = NULL;
            t->sibling = NULL;
            t->nodekind = ExpK;
            t->subkind.exp = kind;
            t->lineno = token->lineno;
            t->expType = Void;
        }
    }

    return t;
}

//prints expected type in grammar, eliminates use of more if statements. 
void printExp(ExpType t){

    switch(t){

        case Void:
            printf("void");
            break;

        case Integer:
            printf("int");
            break;

        case Char:
            printf("char");
            break;

        case CharInt:
            printf("CharInt");
            break;

        case Boolean:
            printf("bool");
            break;

        case Equal:
            printf("Equal");
            break;

        case UndefinedType:
            printf("undefined type");
            break;

        default:
            printf("exprType not found\n");
            break;
    }
}

//function to print tree, uses recursion
void printAST(TreeNode *tree, int nsiblings, bool alltype){
    int i;
    bool ALLTYPE = alltype;

    if(tree==NULL){
        printf("Unable to print tree\n");
    }
    while(tree != NULL){
            
        if(tree->nodekind == DeclK){

            switch(tree->subkind.decl){

                case VarK:
                    if(tree->isArray == true){
                        printf("Var: %s is array of type ", tree->attr.name);
                        printExp(tree->expType);
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    else if(!ALLTYPE){
                        if(tree->isStatic == true){
                        printf("Var: %s of static type ", tree->attr.name);
                        printExp(tree->expType);
                        printf(" [line: %d]\n", tree->lineno);
                        }
                    }
                    else{
                        printf("Var: %s of type ", tree->attr.name);
                        printExp(tree->expType);
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    break;

                case FuncK:
                    printf("Func: %s returns type ", tree->attr.name);
                    printExp(tree->expType);
                        printf(" [line: %d]\n", tree->lineno);
                    break;

                case ParamK:
                    if(tree->isArray){
                        printf("Parm: %s is array of type ", tree->attr.name);
                        printExp(tree->expType);
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    else{
                        printf("Parm: %s of type ", tree->attr.name);
                        printExp(tree->expType);
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    break;
                
                default:
                printf("Unknown Decl Kind Line:%d\n", tree->lineno);
            }
        }

        else if(tree->nodekind == StmtK){
            switch(tree->subkind.stmt){
                
                case NullK:
                    printf("NULL [line: %d]\n", tree->lineno);
                break;

                case IfK:
                    printf("If [line: %d]\n", tree->lineno);
                break;

                case WhileK:
                    printf("While [line: %d]\n", tree->lineno);
                break;

                case ForK:
                    printf("For [line: %d]\n", tree->lineno);
                break;

                case BreakK:
                    printf("Break [line: %d]\n", tree->lineno);
                break;

                case CompoundK:
                    printf("Compound [line: %d]\n", tree->lineno);
                break;

                case ReturnK:
                    printf("Return [line: %d]\n", tree->lineno);
                break;

                case RangeK:
                    printf("Range [line: %d]\n", tree->lineno);
                break;

                default:
                break;
            }
        }
        //Added statments for the -P option.
        else if(tree->nodekind == ExpK){

            switch(tree->subkind.exp){
                
                case OpK:

                if(tree->child[1] != NULL && !strcmp(tree->attr.name, "=")){
                    printf("Op: %s", tree->attr.name);
                    if(tree->expType == UndefinedType){
                       
                        if(ALLTYPE){
                            printf(" of undefined type");
                        }
                    }
                    else{
                        
                        if(ALLTYPE){
                            printf(" of type bool");
                            //printExp(tree->expType);
                        }
                    }
                    printf(" [line: %d]\n", tree->lineno);
                }
                                                
                else if(tree->child[1] == NULL && !strcmp(tree->attr.name, "-")){
                    
                    printf("Op: chsign");
                    if(ALLTYPE){
                        if(tree->expType == UndefinedType){
                            printf(" of undefined type");
                        }
                        else{
                            printf(" of type ");
                            printExp(tree->expType);
                        }
                    }
                    printf(" [line: %d]\n", tree->lineno);
                    
                }

                else if(tree->child[1] == NULL && !strcmp(tree->attr.name, "*")){
                    printf("Op: sizeof");
                    if(ALLTYPE){
                        if(tree->expType == UndefinedType || !tree->child[0]->isArray){
                            printf(" of undefined type");
                        }
                        else{
                            printf(" of type ");
                            printExp(tree->expType);
                        }
                    }
                    printf(" [line: %d]\n", tree->lineno);
                }

                else if(!strcmp(tree->attr.name, "%")){
                    printf("Op: %s", tree->attr.name);
                    if(ALLTYPE){
                        if(tree->expType == UndefinedType){
                            printf(" of undefined type");
                        }
                        else{
                            printf(" of type ");
                            printExp(tree->expType);
                        }
                    }
                    printf(" [line: %d]\n", tree->lineno);
                }

                else{
                    printf("Op: %s", tree->attr.name);
                    if(ALLTYPE){
                        if(tree->expType == UndefinedType){
                            printf(" of undefined type");
                        }
                        
                        else{
                            printf(" of type ");
                            printExp(tree->expType);
                        }
                    }
                    printf(" [line: %d]\n", tree->lineno);
                }
                break;
                case ConstantK:

                if(tree->expType == Boolean){
                    printf("Const %s", tree->attr.name);

                    if(ALLTYPE){
                        printf(" of type bool");
                    }

                    printf(" [line: %d]\n", tree->lineno);
                }

                else if(tree->expType == CharInt){
                    printf("Const is array ");
                    printf("%s", tree->attr.name);

                    if(ALLTYPE){
                        printf(" of type char");
                    }

                    printf(" [line: %d]\n", tree->lineno);
                }

                else if(tree->expType == Char){
                    printf("Const \'%c\'", tree->thisTokenData->cvalue);

                    if(ALLTYPE){
                        printf(" of type char");
                    }

                    printf(" [line: %d]\n", tree->lineno);
                }

                else{
                    printf("Const %d", tree->attr.value);

                    if(ALLTYPE){
                        printf(" of type int");
                    }

                    printf(" [line: %d]\n", tree->lineno);
                }
                break;

                case AssignK:
                    printf("Assign: %s", tree->attr.name);
                    
                    if(ALLTYPE){
                        printf(" of type ");
                        printExp(tree->expType);
                    }

                    printf(" [line: %d]\n", tree->lineno);
                break;
 
                case IdK:
                    printf("Id: %s", tree->attr.name);

                    if(ALLTYPE){
                        if(tree->expType == UndefinedType || tree->expType == Void){
                            printf(" of undefined type");
                        }
                        else{
                            printf(" of type ");
                            printExp(tree->expType);
                        }
                    }

                    printf(" [line: %d]\n", tree->lineno);
                break;

                case InitK:
                break;

                case CallK:
                     printf("Call: %s", tree->attr.name);
                    
                    if(ALLTYPE){
                        printf(" of type ");
                        printExp(tree->expType);
                    }

                    printf(" [line: %d]\n", tree->lineno);
                break;

                default:
                    printf("ERROR %i ", CallK);
                    printf("Unknown ExpNode subkind Line: %d\n", tree->lineno);
                break;
            }
        }

        else{
            printf("Unknown node type: %d Line: %d\n", tree->nodekind, tree->lineno);
        }
        
        for(i=0; i< MAXCHILDREN; i++){
            if(tree->child[i] != NULL){
                WSC++;
                printTabs(WSC);
                printf("Child: %d  ", i);
                printAST(tree->child[i], 0, ALLTYPE);
                WSC--;
            }
        }

        if(tree->sibling != NULL){
            nsiblings++;
            printTabs(WSC);
            printf("Sibling: %d  ", nsiblings);
        }
        tree = tree->sibling;
    }
}

//Function to print white spaces
void printTabs(int WS){
    int i;
    for(i = 0; i < WS; i++){
        printf(".   ");
    }
}

//function for setting up IO functions since we can't take in any tokenData
TreeNode *newDeclNodeIO(DeclKind kind){
    TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;

    for(i = 0; i<MAXCHILDREN; i++){
        t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = DeclK;
        t->subkind.decl = kind;
        t->expType = Void;
    }

    return t;
}