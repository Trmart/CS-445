/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW6
Dr. Wilder
DUE: 4/16/2023

FILE: AST.c
DESC: This file contains the functions that are used to create the abstract syntax tree.
      The functions in this file are used to create the nodes for the syntax tree and
      to print the syntax tree. The functions in this file are called by the parser.y file.
      The functions in this file are called by the parser.y file.
*/

#include "AST.h"
#include "scanType.h"
#include "parser.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int numTabs = 0;

extern bool isPrintingMemorySize;

//adds sibling to node
TreeNode* addSibling(TreeNode* node, TreeNode* sibling)
{

    if(node == NULL)
    {
        return sibling;   
    }
    if(sibling == NULL)
    {
        return node;
    }
    if (node!=NULL && sibling!=NULL) 
    {
        TreeNode *tmp = node;
        
        while (tmp != NULL && tmp->sibling != NULL)
        {
            tmp = tmp->sibling;
        } 
        
        tmp->sibling = sibling;
        
        return node;
    }

    return sibling;
}

// Function Passes the type attributes down the sibling list.
void setType(TreeNode* node, ExpType type)
{
    while (node != NULL) 
    {
        node->expType = type;
        node = node->sibling;
    }
}

// Creates a new declaration node for syntax tree construction
TreeNode* newDeclNode(DeclKind kind, TokenData* token)
{
    TreeNode* node = (TreeNode *) malloc(sizeof(TreeNode));
    
    int i;
    
    if( node==NULL)
    {
        printf("Out of memory error at line %d\n", token->lineno);
    }
    else
    {
        for(i=0; i<MAXCHILDREN; i++)
        {
            node->child[i] = NULL;
            node->sibling = NULL;
            node->nodekind = DeclK;
            node->subkind.decl = kind;
            node->lineno = token->lineno;
            node->expType = Void;
            node->attr.name = strdup(token->tokenstr);
            node->memorySize = 1; //default memory size
        }
    }

    return node;
}


TreeNode *newDeclNodeIO(DeclKind kind)
{
    TreeNode* node = (TreeNode *)malloc(sizeof(TreeNode));
    int i;

    for(i = 0; i<MAXCHILDREN; i++)
    {
        node->child[i] = NULL;
        node->sibling = NULL;
        node->nodekind = DeclK;
        node->subkind.decl = kind;
        node->expType = Void;
        node->memorySize = 1; //default memory size

    }

    return node;
}


TreeNode* newStmtNode(StmtKind kind, TokenData *token)
{
    TreeNode* node = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    
    if(node ==NULL)
    {
        printf("Out of memory error at line %d\n", token->lineno);
    }
    else
    {
        for(i=0; i<MAXCHILDREN; i++)
        {
            node->child[i] = NULL;
            node->sibling = NULL;
            node->nodekind = StmtK;
            node->subkind.stmt = kind;
            node->lineno = token->lineno;
            node->expType = Void;
            node->attr.name = strdup(token->tokenstr);
            node->memorySize = 1; //default memory size
        }
    }

    return node;
}


TreeNode* newExpNode(ExpKind kind, TokenData *token)
{
    TreeNode* node = (TreeNode *) malloc(sizeof(TreeNode));
    
    int i;
    
    if( node==NULL)
    {
        printf("Out of memory error at line %d\n", token->lineno);
    }  
    else
    {
        for(i=0; i < MAXCHILDREN; i++)
        {
            node->child[i] = NULL;
            node->sibling = NULL;
            node->nodekind = ExpK;
            node->subkind.exp = kind;
            node->lineno = token->lineno;
            node->expType = Void;
            node->memorySize = 1; //default memory size
        }
    }

    return node;
}

void printMemoryType(VarKind var)
{
    switch(var)
    {
        case Global:
                {
                    printf("Global");
                }
                break;

        case Local:
                {
                    printf("Local");
                }
                break;
        
        case LocalStatic:
                    {
                        printf("LocalStatic");
                    }
                    break;

        case Parameter:
                    {
                        printf("Parameter");
                    }
                    break;

        case None:
                {
                    printf("None");
                }
                break; 

        default:
                {
                    printf("Error: Memory type not found");
                }
                break;
    }
}

void printMemorySizeAndOffset(TreeNode* node)
{
    printf(" [mem: ");
    printMemoryType(node->memoryType);
    printf(" loc: %d size: %d]", node->memoryOffset, node->memorySize);
}

void printExp(ExpType type)
{

    switch(type)
    {

        case Void:
                {
                    printf("void");
                }
                break;


        case Integer:
                    {
                        printf("int");
                    }
                    break;

        case Char:
                {
                    printf("char");
                }
                break;

        case CharInt:
                    {
                        printf("CharInt");
                    }
                    break;

        case Boolean:
                    {
                        printf("bool");
                    }
                    break;

        case UndefinedType:
                        {
                            printf("UndefinedType");
                        }
                        break;

        default:
                {
                    printf("Error: Type not found");
                }
                break;
    }
}


void printAST(TreeNode* tree, int nsiblings, bool isShowingTypes)
{
    int i;

    if(tree==NULL)
    {
        printf("Unable to print tree\n");
    }

    while(tree != NULL)
    {
        switch (tree->nodekind)
        {
            case DeclK:
                    {
                        printDeclNode(tree, isShowingTypes);
                    }
                    break;

            case StmtK:
                    {
                        printStmtNode(tree, isShowingTypes);
                    }
                    break;

            case ExpK:
                    {
                        printExpNode(tree, isShowingTypes);
                    }
                    break;

            default:
                    {
                        printf("Unknown node type: %d Line: %d\n", tree->nodekind, tree->lineno);
                    }
                    break;
        }

        //print and analyze children
        for(i=0; i< MAXCHILDREN; i++)
        {

            if(tree->child[i] != NULL)
            {
                numTabs++;
                printTabs(numTabs);
                printf("Child: %d  ", i);
                printAST(tree->child[i], 0, isShowingTypes);
                numTabs--;
            }
        }

        //print and analyze siblings
        if(tree->sibling != NULL)
        {
            nsiblings++;
            printTabs(numTabs);
            printf("Sibling: %d  ", nsiblings);
        }
        
        tree = tree->sibling;
    }
}


void printStmtNode(TreeNode* tree, bool isShowingTypes)
{
    switch(tree->subkind.stmt)
    {
        
        case BreakK:
                {
                    printf("Break [line: %d]\n", tree->lineno);
                }
                break;

        case CompoundK:
                    {
                        printf("Compound");

                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    break;

        case ForK:
                {
                    printf("For");

                    if (isPrintingMemorySize)
                    {
                        printMemorySizeAndOffset(tree);
                    }
                    printf(" [line: %d]\n", tree->lineno);
                }
                break;

        case IfK:
                {
                    printf("If [line: %d]\n", tree->lineno);
                }
                break;

        case NullK:
                {
                    printf("NULL [line: %d]\n", tree->lineno);
                }
                break;

        case RangeK:
                {
                    printf("Range [line: %d]\n", tree->lineno);
                }
                break;

        case ReturnK:
                    {
                        printf("Return [line: %d]\n", tree->lineno);
                    }
                    break;

        case WhileK:
                {
                    printf("While [line: %d]\n", tree->lineno);
                }
                break;
        
        default:
            {
                printf("Unknown StmtNode type: %d Line: %d\n", tree->subkind.stmt, tree->lineno);
            }
            break;
    }
}


void printDeclNode(TreeNode* tree, bool isShowingTypes)
{
    switch(tree->subkind.decl)
    {
        case FuncK:
                {
                    printf("Func: %s returns type ", tree->attr.name);
                    printExp(tree->expType);

                    if (isPrintingMemorySize)
                    {
                        printMemorySizeAndOffset(tree);
                    }
                    printf(" [line: %d]\n", tree->lineno);
                }
                break;



        case ParamK:
                {
                    if(tree->isArray)
                    {
                        printf("Parm: %s is array of type ", tree->attr.name);
                        printExp(tree->expType);

                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    else
                    {
                        printf("Parm: %s of type ", tree->attr.name);
                        printExp(tree->expType);
                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                }
                break;
        
        case VarK:
                {
                    if(tree->isArray && tree->isStatic)
                    {
                        printf("Var: %s of static array of type ", tree->attr.name);
                        printExp(tree->expType);
                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    else if(tree->isArray)
                    {
                        printf("Var: %s of array of type ", tree->attr.name);
                        printExp(tree->expType);
                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    else if(!isShowingTypes)
                    {
                        if(tree->isStatic)
                        {
                            printf("Var: %s of static type ", tree->attr.name);
                            printExp(tree->expType);
                            if (isPrintingMemorySize)
                            {
                                printMemorySizeAndOffset(tree);
                            }
                            printf(" [line: %d]\n", tree->lineno);
                        }
                    }
                    else if(tree->isStatic)
                    {
                        printf("Var: %s of static type ", tree->attr.name);
                        printExp(tree->expType);
                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                    else
                    {
                        printf("Var: %s of type ", tree->attr.name);
                        printExp(tree->expType);
                        if (isPrintingMemorySize)
                        {
                            printMemorySizeAndOffset(tree);
                        }
                        printf(" [line: %d]\n", tree->lineno);
                    }
                }
                break;
        default:
        {
            printf("Unknown Decl Kind Line:%d\n", tree->lineno);
        }
        break;
    }
}


void printConstantNode(TreeNode* tree, bool isShowingTypes)
{
    if(tree->expType == Boolean)
    {
        printf("Const %s", tree->attr.name);

        if(isShowingTypes)
        {
            printf(" of type bool");
        }

        printf(" [line: %d]\n", tree->lineno);
    }

    else if(tree->expType == CharInt)
    {
        printf("Const ");
        
        printf("%s", tree->attr.name);

        if(isShowingTypes)
        {
            printf(" of array of type char");
        }

        if (isPrintingMemorySize)
        {
            printMemorySizeAndOffset(tree);
        }

        printf(" [line: %d]\n", tree->lineno);
    }

    else if(tree->expType == Char)
    {
        printf("Const \'%c\'", tree->thisTokenData->cvalue);

        if(isShowingTypes)
        {
            printf(" of type char");
        }

        if(tree->isArray)
        {
            if(isPrintingMemorySize)
            {
                printMemorySizeAndOffset(tree);
            }
        }

        printf(" [line: %d]\n", tree->lineno);
    }

    else
    {
        printf("Const %d", tree->attr.value);

        if(isShowingTypes)
        {
            printf(" of type int");
        }

        printf(" [line: %d]\n", tree->lineno);
    }
}


void printOpNode(TreeNode* tree, bool isShowingTypes)
{
    if(tree->child[1] != NULL && !strcmp(tree->attr.name, "="))
    {
        printf("Op: %s", tree->attr.name);
        
        if(tree->expType == UndefinedType)
        {
            
            if(isShowingTypes)
            {
                printf(" of undefined type");
            }
        }
        else
        {
            if(isShowingTypes)
            {
                printf(" of type bool");
            }
        }
        printf(" [line: %d]\n", tree->lineno);
    }
                                        
    else if(tree->child[1] == NULL && !strcmp(tree->attr.name, "-"))
    {
        
        printf("Op: chsign");
        
        if(isShowingTypes)
        {
            if(tree->expType == UndefinedType)
            {
                printf(" of undefined type");
            }
            else
            {
                printf(" of type ");
                printExp(tree->expType);
            }
        }
        printf(" [line: %d]\n", tree->lineno);
        
    }

    else if(tree->child[1] == NULL && !strcmp(tree->attr.name, "*"))
    {
        printf("Op: sizeof");
        
        if(isShowingTypes){
            if(tree->expType == UndefinedType || !tree->child[0]->isArray)
            {
                printf(" of undefined type");
            }
            else
            {
                printf(" of type ");
                printExp(tree->expType);
            }
        }
        printf(" [line: %d]\n", tree->lineno);
    }

    else if(!strcmp(tree->attr.name, "%"))
    {
        printf("Op: %s", tree->attr.name);
        
        if(isShowingTypes)
        {
            if(tree->expType == UndefinedType)
            {
                printf(" of undefined type");
            }
            else
            {
                printf(" of type ");
                printExp(tree->expType);
            }
        }
        printf(" [line: %d]\n", tree->lineno);
    }

    else
    {
        printf("Op: %s", tree->attr.name);
        if(isShowingTypes)
        {
            if(tree->expType == UndefinedType)
            {
                printf(" of undefined type");
            }
            
            else
            {
                printf(" of type ");
                printExp(tree->expType);
            }
        }
        printf(" [line: %d]\n", tree->lineno);
    }
}


void printExpNode(TreeNode* tree, bool isShowingTypes)
{
    switch(tree->subkind.exp)
    {
        
        case OpK:
                {
                    printOpNode(tree, isShowingTypes);
                }
                break;
        
        case ConstantK:
                    {
                        printConstantNode(tree, isShowingTypes);
                    }
                    break;

        case AssignK:
                    {
                        printf("Assign: %s", tree->attr.name);
                        
                        if(isShowingTypes)
                        {
                            if(tree->child[0]->isArray)
                            {
                                printf(" of array of type ");
                                printExp(tree->expType);
                            }
                            else
                            {
                                printf(" of type ");
                                printExp(tree->expType);
                            }
                        }

                        printf(" [line: %d]\n", tree->lineno);
                    }
                    break;

        case IdK:
                {
                    printf("Id: %s", tree->attr.name);

                    if(isShowingTypes)
                    {
                        if(tree->expType == UndefinedType)
                        {
                            printf(" of undefined type");
                        }
                        else if(tree->isArray && tree->isStatic)
                        {
                            printf(" of static array of type ");
                            printExp(tree->expType);
                        }
                        else if(tree->isStatic)
                        {
                            printf(" of static type ");
                            printExp(tree->expType);
                        }
                        else if(tree->isArray)
                        {
                            printf(" of array of type ");
                            printExp(tree->expType);
                        }
                        else
                        {
                            printf(" of type ");
                            printExp(tree->expType);
                        }
                    }
                    if (isPrintingMemorySize)
                    {
                        printMemorySizeAndOffset(tree);
                    }

                    printf(" [line: %d]\n", tree->lineno);
                }
                break;

        case InitK:
                {
                    //do nothing
                }
                break;

        case CallK:
                {
                    printf("Call: %s", tree->attr.name);
                    
                    if(isShowingTypes)
                    {
                        printf(" of type ");
                        printExp(tree->expType);
                    }

                    printf(" [line: %d]\n", tree->lineno);
                }
                break;

        default:
                {
                    printf("ERROR %i ", ExpK);
                    printf("Unknown ExpNode subkind Line: %d\n", tree->lineno);
                }
                break;
    }
}


void printTabs(int numTabs)
{
    int i;
    for(i = 0; i < numTabs; i++)
    {
        printf(".   ");
    }
}
