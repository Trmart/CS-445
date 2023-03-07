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

void Node::setNodeType(NodeType type)
{
    m_nodeType = type;
}


void Node::setSiblingsType(Node* node, ExpressionType type)
{
    while(node != nullptr)
    {
        node->setExpType(type);
        node = node->m_sibling;
    }
}

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
            node->setNodeType(DECLARATION);
            node->nodeSubType.declaration = declType;
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
            node->setNodeType(STATEMENT);
            node->nodeSubType.statement = stmtType;
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

    int numTabs = 0;

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
            node->setNodeType(EXPRESSION);
            node->setLineNum(tokenData->m_lineNumber);
            node->nodeSubType.expression = expType;
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
        node->setNodeType(DECLARATION);
        node->nodeSubType.declaration = decltype;
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
void printAST(Node* node, int numSiblings, bool isShowingType)
{

    if(node==nullptr)
    {
        std::cout << "PrintAST() ERROR: Node is Null. Cannot Print AST" << std::endl;
        exit(1);
    }

    while(node != nullptr)
    {
        switch(node->getNodeType())
        {
            case NodeType::DECLARATION:
            {
                switch(node->nodeSubType.declaration)
                {
                    case DeclarationType::VAR:
                    {

                        if(node->getIsArray())
                        {
                            std::cout << "Var: " << node->nodeAttributes.name << " is array of type ";
                            printExpression(node->getExpType());
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                        else if(!isShowingType)
                        {
                            if(node->getIsStatic())
                            {
                                std::cout << "Var: " << node->nodeAttributes.name << " of static type "<<  node->printExpression(node->getExpType()) <<" [line: " << node->getLineNum() << "]" << std::endl;
                            }
                        }

                        else
                        {
                            std::cout << "Var: " << node->nodeAttributes.name << " of type ";
                            printExpression(node->getExpType());
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }
                    }
                    break;

                    case DeclarationType::FUNC:
                    {
                        std::cout << "Func: " << node->nodeAttributes.name << " returns type ";
                        printExpression(node->getExpType());
                        std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break;

                    case DeclarationType::PARAM:
                    {
                        if(node->getIsArray())
                        {
                            std::cout << "Param: " << node->nodeAttributes.name << " is array of type ";
                            printExpression(node->getExpType());
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }
                        else
                        {
                            std::cout << "Param: " << node->nodeAttributes.name << " of type ";
                            printExpression(node->getExpType());
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }
                    }
                    break;

                    default:
                    {
                        std::cout << "PrintAST() ERROR: Declaration Type Not Found" << std::endl;
                    }
                    break;
                }
            }
            break;

            case NodeType::STATEMENT:
            {
                switch(node->nodeSubType.statement)
                {
                    case StatementType::IF:
                    {
                        std::cout << "If [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break;

                    case StatementType::WHILE:
                    {
                        std::cout << "While [line: " << node->getLineNum()  << "]" << std::endl;
                    }
                    break;

                    case StatementType::RETURN:
                    {
                        std::cout << "Return [line: " << node->getLineNum()  << "]" << std::endl;
                    }
                    break;

                    case StatementType::COMPOUND:
                    {
                        std::cout << "Compound [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break; 

                    case StatementType::RANGE:
                    {
                        std::cout << "Range [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break; 

                    case StatementType::BREAK:
                    {
                        std::cout << "Break [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break; 

                    case StatementType::FOR:
                    {
                        std::cout << "For [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break;

                    case StatementType::NULLSTMT:
                    {
                        std::cout << "Null [line: " << node->getLineNum() << "]" << std::endl;
                    }
                    break;

                    default:
                    {
                        std::cout << "PrintAST() ERROR: Statement Type Not Found" << std::endl;
                    }
                    break;
                }
            }
            break; 


            case NodeType::EXPRESSION:
            {
                switch(node->nodeData.expression)
                {
                    case ExpressionType::OP:
                    {
                        if(node->m_childernNodes[1] != nullptr && node->nodeAttributes.name != "=")
                        {
                            std::cout << "Op: " << node->nodeAttributes.name; 
                            if(node->getExpType() == ReturnType::UNDEFINED)
                            {

                                if(isShowingType)
                                {
                                    std::cout << " of undefined type"; 
                                }
                            }
                            else
                            {
                                if(isShowingType)
                                {
                                    std::cout << " of type bool";
                                }
                            }
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                        else if(node->m_childernNodes[1] == nullptr && node->nodeAttributes.name != "-")
                        {
                            std::cout << "Op: chsign";
                            
                            if(isShowingType)
                            {
                                if(node->getExpType() == ReturnType::UNDEFINED)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type " << node->printExpression(node->getExpType());
                                }
                            }
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                        else if(node->m_childernNodes[1] == nullptr && node->nodeAttributes.name != "*")
                        {
                            std::cout << "Op: sizeof" << node->nodeAttributes.name; 
                            
                            if(isShowingType)
                            {
                                if(node->getExpType() == ReturnType::UNDEFINED || !node->getIsArray())
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type " << node->printExpression(node->getExpType());
                                }
                            }
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                        else if(node->nodeAttributes.name != "%")
                        {
                            std::cout << "Op: " << node->nodeAttributes.name; 
                            
                            if(isShowingType)
                            {
                                if(node->getExpType() == ReturnType::UNDEFINED)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type " << node->printExpression(node->getExpType());
                                }
                            }
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                        else
                        {
                            std::cout << "Op: " << node->nodeAttributes.name; 
                            
                            if(isShowingType)
                            {
                                if(node->getExpType() == ReturnType::UNDEFINED)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type " << node->printExpression(node->getExpType());
                                }
                            }
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }
                    }
                    break;

                    case ExpressionType::CONST:
                    {
                        if(node->getExpType() == ReturnType::BOOL)
                        {
                            std::cout << "Const: " << node->nodeAttributes.name; 

                            if(isShowingType)
                            {
                                std::cout << " of type bool";
                            }
                            
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                        else if(node->getExpType() == ReturnType::CHARINT)
                        {
                            std::cout << "Const is array  " << node->nodeAttributes.name; 

                            if(isShowingType)
                            {
                                std::cout << " of type char";
                            }
                            
                            std::cout << " [line: " << node->getLineNum() << "]" << std::endl;
                        }

                    }
                    break;

                    case ExpressionType::CALL:
                    {

                    }
                    break;

                    case ExpressionType::ID:
                    {

                    }
                    break;

                    default:
                    {
                        std::cout << "PrintAST() ERROR: Expression Type Not Found" << std::endl;
                    }
                    break;
                }
            }
            break; 

            default:
            {
                std::cout << "PrintAST() ERROR: Node Type Not Found on line " << node->getLineNum() << std::endl;
            }
        }

        for(int i = 0; i < MAXCHILDREN; i++)
        {
            if(tree->child[i] != nullptr)
            {
                numTabs++;
                printOutputTabs(numTabs);
                std::cout << "Child: " << i << " ";
                printAST(tree->child[i], 0, isShowingType);
                numTabs--;
            }
        }

        if(tree->sibling != nullptr)
        {
            numSiblings++;
            printOutputTabs(numTabs);
            std::cout << "Sibling: " << numSiblings << " ";
        }

        tree = tree->sibling;
    }
}