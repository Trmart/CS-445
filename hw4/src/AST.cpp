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

#include "AST.hpp"
#include "scanType.hpp"
#include "parser.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int WSC = 0;

//Setters
void Node::setExpType(ExpressionType type)
{
    m_expType = type;
}


void Node::setIsArray(bool isArray)
{
    m_isArray = isArray;
}


void Node::setIsStatic(bool isStat)
{
    m_isStatic = isStat;
}


void Node::setIsGlobal(bool isGlobal)
{
    m_isGlobal = isGlobal;
}


void Node::setIsInit(bool isInit)
{
    m_isInit = isInit;
}


void Node::setWarningReported(bool isReported)
{
    m_warningReported = isReported;
}


void Node::setWasUsed(bool isUsed)
{
    m_wasUsed = isUsed;
}


void Node::setIsDeclared(bool isDeclared)
{
    m_isDeclared = isDeclared;
}


void Node::setDeclErr(bool isError)
{
    m_declErr = isError;
}


void Node::setWasUsedErr(bool isError)
{
    m_wasUsedErr = isError;
}


void Node::setIsIndexed(bool isIndexed)
{
    m_isIndexed = isIndexed;
}


void Node::setIsIO(bool isIO)
{
    m_isIO = isIO;
}

void Node::addSiblingNode(Node* left, Node* sibling)
{
    if(current != nullptr) 
    {
        Node* temp = current;
        
        while (temp->m_sibling != nullptr) 
        {
            temp = temp->m_sibling;
        }


        temp->m_sibling = sibling;

        return current;
    }
    return sibling;

    if(current == nullptr)
    {
        return sibling;   
    }
    else if(sibling == nullptr)
    {
        return current;
    }
}


void Node::setType(Node* node, ExpressionType type)
{
    while(node != nullptr)
    {
        node->setExpType(type);
        node = node->m_sibling;
    }
}


Node* Node::newDeclNode(DeclarationType declType, TokenData* tokenData)
{
    Node* node = new Node();

    if(node == nullptr)
    {
        std::cout << "Out of memory error at line " << tokenData->m_lineNumber << std::endl;
    }
    else
    {
        for (int i = 0; i < MAXCHILDREN; i++)
        {
            node->m_childernNodes[i] = nullptr;
            node->m_siblingNode = nullptr;
            node->m_nodeType = DECLARATION;
            node->setNodeType(declType);
            node->setLineNum(tokenData->m_lineNumber);
            node->setExpType(VOID);
            node->nodeAttributes.name = tokenData->tokenContent;
        }
    }

    return node;

}


Node* Node::newStmtNode(StatementType stmtType, TokenData* tokenData)
{
    Node* node = new Node();

    if(node == nullptr)
    {
        std::cout << "Out of memory error at line " << tokenData->m_lineNumber << std::endl;
    }
    else
    {
        for (int i = 0; i < MAXCHILDREN; i++)
        {
            node->m_childernNodes[i] = nullptr;
            node->m_siblingNode = nullptr;
            node->m_nodeType = DECLARATION;
            node->setNodeType(stmtType);
            node->setLineNum(tokenData->m_lineNumber);
            node->setExpType(VOID);
            node->nodeAttributes.name = tokenData->tokenContent;
        }
    }

    return node;

}


Node* Node::newExpNode(ExpressionType expType, TokenData* tokenData)
{
    Node* node = new Node();

    if(node == nullptr)
    {
        std::cout << "Out of memory error at line " << tokenData->m_lineNumber << std::endl;
    }
    else
    {
        for (int i = 0; i < MAXCHILDREN; i++)
        {
            node->m_childernNodes[i] = nullptr;
            node->m_siblingNode = nullptr;
            node->m_nodeType = DECLARATION;
            node->setNodeType(expType);
            node->setLineNum(tokenData->m_lineNumber);
            node->setExpType(VOID);
            node->nodeAttributes.name = tokenData->tokenContent;
        }
    }

    return node;

}


//function for setting up IO functions since we can't take in any tokenData
Node* Node::newDeclNodeIO(DeclarationType decltype)
{
    Node* node = new Node();

    for(int i = 0; i<MAXCHILDREN; i++)
    {
        node->m_childernNodes[i] = nullptr;
        node->m_siblingNode = nullptr;
        node->m_nodeType = DECLARATION;
        node->nodeData.declaration = decltype;
        node->setExpType(VOID);
    }

    return node;
}

//Print the Formatting Output Tabs for the Correct AST Output 
void printOutputTabs(const int numTabs)
{
    for(int i = 0; i < numTabs; i++)
    {
        std::cout << ".   "; 
    }
}

//prints expected type in grammar, eliminates use of more if statements. 
void printExpression(ExpressionType expType)
{

    switch(expType)
    {

        case ReturnType::VOID:
                        {
                            std::cout << "void";
                        }
                        break;


        case ReturnType::INT:
                        {
                            std::cout << "int";
                        }
                        break;

        case ReturnType::CHAR:
                            {
                                std::cout << "char";
                            }

                            break;

        case ReturnType::BOOLEAN:
                            {
                                std::cout << "bool";
                            }
                            break;

        case ReturnType::UNDEFINED:
                                {
                                    std::cout << "undefined";
                                }
                                break;

        default:
            {
                std::cout << "ERROR: Expression Type Not Found"<< std::endl;
            }
            break; 
    }
}

//function to print tree, uses recursion
void printAST(Node* node, int nsiblings, bool alltype)
{
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
                printWhiteSpace(WSC);
                printf("Child: %d  ", i);
                printTree(tree->child[i], 0, ALLTYPE);
                WSC--;
            }
        }

        if(tree->sibling != NULL){
            nsiblings++;
            printWhiteSpace(WSC);
            printf("Sibling: %d  ", nsiblings);
        }
        tree = tree->sibling;
    }
}

