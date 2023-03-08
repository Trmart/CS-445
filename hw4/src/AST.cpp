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
// #include "parser.tab.h"
#include <iostream>
#include <stdlib.h>


int numTabs = 0;


Node* addSiblingNode(Node* leftSibling, Node* rightSibling)
{
    if(leftSibling != nullptr) 
    {
        Node* temp = leftSibling;
        
        while (temp->m_siblingNode != nullptr) 
        {
            temp = temp->m_siblingNode;
        }


        temp->m_siblingNode = rightSibling;

        return leftSibling;
    }
    return rightSibling;

    if(leftSibling == nullptr)
    {
        return rightSibling;   
    }
    else if(leftSibling == nullptr)
    {
        return rightSibling;
    }
}

void setSiblingsType(Node* node, ExpressionType expType)
{
    while(node != nullptr)
    {
        node->nodeSubType.expression = expType;
        node = node->m_siblingNode;
    }
}



Node* newDeclNode(DeclarationType declType, TokenData* tokenData)
{
    Node* node = (Node*)malloc(sizeof(Node));

    if(node == nullptr)
    {
        std::cout << "Out of memory error at line " << tokenData->tokenLineNumber << std::endl;
    }
    else
    {
        for (int i = 0; i < MAXCHILDREN; i++)
        {
            node->m_childernNodes[i] = nullptr;
            node->m_siblingNode = nullptr;
            node->m_nodeType = DECLARATION;
            node->nodeSubType.declaration = declType;
            node->m_lineNumber = tokenData->tokenLineNumber;
            node->m_parmType = VOID;
            node->nodeAttributes.name = tokenData->tokenContent;
        }
    }

    return node;

}


Node* newStmtNode(StatementType stmtType, TokenData* tokenData)
{
    Node* node = (Node*)malloc(sizeof(Node));


    if(node == nullptr)
    {
        std::cout << "Out of memory error at line " << tokenData->tokenLineNumber << std::endl;
    }
    else
    {
        for (int i = 0; i < MAXCHILDREN; i++)
        {
            node->m_childernNodes[i] = nullptr;
            node->m_siblingNode = nullptr;
            node->m_nodeType = STATEMENT;
            node->nodeSubType.statement = stmtType;
            node->m_lineNumber = tokenData->tokenLineNumber;
            node->m_parmType = VOID;
            node->nodeAttributes.name = tokenData->tokenContent;
        }
    }

    return node;

}


Node* newExpNode(ExpressionType expType, TokenData* tokenData)
{
    Node* node = (Node*)malloc(sizeof(Node));


    int numTabs = 0;

    if(node == nullptr)
    {
        std::cout << "Out of memory error at line " << tokenData->tokenLineNumber << std::endl;
    }
    else
    {
        for (int i = 0; i < MAXCHILDREN; i++)
        {
            node->m_childernNodes[i] = nullptr;
            node->m_siblingNode = nullptr;
            node->m_nodeType = EXPRESSION;
            node->m_lineNumber = tokenData->tokenLineNumber;
            node->nodeSubType.expression = expType;
            node->m_parmType = VOID;
            node->nodeAttributes.name = tokenData->tokenContent;
        }
    }

    return node;

}


//function for setting up IO functions since we can't take in any tokenData
Node* newDeclNodeIO(DeclarationType type)
{
    Node* node = (Node*)malloc(sizeof(Node));


    for(int i = 0; i < MAXCHILDREN; i++)
    {
        node->m_childernNodes[i] = nullptr;
        node->m_siblingNode = nullptr;
        node->m_nodeType = DECLARATION;
        node->nodeSubType.declaration = type;
        node->m_parmType = VOID;
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
void printParameterType(ParmType parmType)
{

    switch(parmType)
    {

        case ParmType::VOID:
                        {
                            std::cout << "void";
                        }
                        break;


        case ParmType::INTEGER:
                        {
                            std::cout << "int";
                        }
                        break;

        case ParmType::CHAR:
                            {
                                std::cout << "char";
                            }

                            break;

        case ParmType::BOOL:
                            {
                                std::cout << "bool";
                            }
                            break;

        case ParmType::UNDEFINED:
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
        switch(node->m_nodeType)
        {
            case NodeType::DECLARATION:
            {
                switch(node->nodeSubType.declaration)
                {
                    case DeclarationType::VARIABLE:
                    {

                        if(node->m_isArray)
                        {
                            std::cout << "Var: " << node->nodeAttributes.name << " is array of type ";
                            printParameterType(node->m_parmType);
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else if(!isShowingType)
                        {
                            if(node->m_isStatic)
                            {
                                std::cout << "Var: " << node->nodeAttributes.name << " of static type ";
                                printParameterType(node->m_parmType);
                                std::cout << " [line: " << node->m_lineNumber<< "]" << std::endl;
                            }
                        }

                        else
                        {
                            std::cout << "Var: " << node->nodeAttributes.name << " of type ";
                            printParameterType(node->m_parmType);
                            std::cout << " [line: " << node->m_lineNumber<< "]" << std::endl;
                        }
                    }
                    break;

                    case DeclarationType::FUNCTION:
                    {
                        std::cout << "Func: " << node->nodeAttributes.name << " returns type ";
                        printParameterType(node->m_parmType);
                        std::cout << " [line: " << node->m_lineNumber<< "]" << std::endl;
                    }
                    break;

                    case DeclarationType::PARAMETER:
                    {
                        if(node->m_isArray)
                        {
                            std::cout << "Param: " << node->nodeAttributes.name << " is array of type ";
                            printParameterType(node->m_parmType);
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }
                        else
                        {
                            std::cout << "Param: " << node->nodeAttributes.name << " of type ";
                            printParameterType(node->m_parmType);
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
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
                        std::cout << "If [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break;

                    case StatementType::WHILE:
                    {
                        std::cout << "While [line: " << node->m_lineNumber  << "]" << std::endl;
                    }
                    break;

                    case StatementType::RETURN:
                    {
                        std::cout << "Return [line: " << node->m_lineNumber  << "]" << std::endl;
                    }
                    break;

                    case StatementType::COMPOUND:
                    {
                        std::cout << "Compound [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break; 

                    case StatementType::RANGE:
                    {
                        std::cout << "Range [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break; 

                    case StatementType::BREAK:
                    {
                        std::cout << "Break [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break; 

                    case StatementType::FOR:
                    {
                        std::cout << "For [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break;

                    case StatementType::NULLSTMT:
                    {
                        std::cout << "Null [line: " << node->m_lineNumber << "]" << std::endl;
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
                switch(node->nodeSubType.expression)
                {
                    case ExpressionType::OP:
                    {
                        if(node->m_childernNodes[1] != nullptr && node->nodeAttributes.name != "=")
                        {
                            std::cout << "Op: " << node->nodeAttributes.name; 
                            if(node->m_parmType == ParmType::UNDEFINED)
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
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else if(node->m_childernNodes[1] == nullptr && node->nodeAttributes.name != "-")
                        {
                            std::cout << "Op: chsign";
                            
                            if(isShowingType)
                            {
                                if(node->m_parmType == ParmType::UNDEFINED)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type "; 
                                    printParameterType(node->m_parmType);
                                }
                            }
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else if(node->m_childernNodes[1] == nullptr && node->nodeAttributes.name != "*")
                        {
                            std::cout << "Op: sizeof" << node->nodeAttributes.name; 
                            
                            if(isShowingType)
                            {
                                if(node->m_parmType== ParmType::UNDEFINED || !node->m_isArray)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type "; 
                                    printParameterType(node->m_parmType);
                                }
                            }
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else if(node->nodeAttributes.name != "%")
                        {
                            std::cout << "Op: " << node->nodeAttributes.name; 
                            
                            if(isShowingType)
                            {
                                if(node->m_parmType == ParmType::UNDEFINED)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type "; 
                                    printParameterType(node->m_parmType);
                                }
                            }
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else
                        {
                            std::cout << "Op: " << node->nodeAttributes.name; 
                            
                            if(isShowingType)
                            {
                                if(node->m_parmType== ParmType::UNDEFINED)
                                {
                                    std::cout << " of undefined type"; 
                                }
                                else
                                {
                                    std::cout << " of type ";
                                    printParameterType(node->m_parmType);
                                }
                            }
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }
                    }
                    break;

                    case ExpressionType::CONSTANT:
                    {
                        if(node->m_parmType == ParmType::BOOL)
                        {
                            std::cout << "Const: " << node->nodeAttributes.name; 

                            if(isShowingType)
                            {
                                std::cout << " of type bool";
                            }
                            
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else if(node->m_parmType == ParmType::CHARINT)
                        {
                            std::cout << "Const is array  " << node->nodeAttributes.name; 

                            if(isShowingType)
                            {
                                std::cout << " of type char";
                            }
                            
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else if(node->m_parmType == ParmType::CHAR)
                        {
                            std::cout << "Const '" << node->m_tokenData->charValue << "'";; 

                            if(isShowingType)
                            {
                                std::cout << " of type char";
                            }
                            
                            std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                        }

                        else
                        {
                            std::cout << "Const: " << node->nodeAttributes.intVal; 

                            if(isShowingType)
                            {
                                std::cout << " of type int";
                            }
                            
                            std::cout << " [line: " << node->m_lineNumber<< "]" << std::endl;
                        }

                    }
                    break;

                    case ExpressionType::CALL:
                    {
                        std::cout << "Call: " << node->nodeAttributes.name; 

                        if(isShowingType)
                        {
                            std::cout << " of type "; 
                            printParameterType(node->m_parmType);
                        }
                        std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break;

                    case ExpressionType::IDENTIFIER:
                    {
                        std::cout << "Id: " << node->nodeAttributes.name; 

                        if(isShowingType)
                        {
                            if(node->m_parmType == ParmType::UNDEFINED || node->m_parmType == ParmType::VOID)
                            {
                                std::cout << " of undefined type";
                            }

                            else
                            {
                                std::cout << " of type "; 
                                printParameterType(node->m_parmType);
                            }
                        }
                        std::cout << " [line: " << node->m_lineNumber << "]" << std::endl;
                    }
                    break;

                    case ExpressionType::INIT:
                    {
                        //do nothing. init not analyzed
                    }

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
                std::cout << "PrintAST() ERROR: Node Type Not Found on line " << node->m_lineNumber << std::endl;
            }
        }

        for(int i = 0; i < MAXCHILDREN; i++)
        {
            if(node->m_childernNodes[i] != nullptr)
            {
                numTabs++;
                printOutputTabs(numTabs);
                std::cout << "Child: " << i << " ";
                printAST(node->m_childernNodes[i], 0, isShowingType);
                numTabs--;
            }
        }

        if(node->m_siblingNode != nullptr)
        {
            numSiblings++;
            printOutputTabs(numTabs);
            std::cout << "Sibling: " << numSiblings << " ";
        }

        node = node->m_siblingNode;
    }
}