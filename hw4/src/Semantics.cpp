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

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Semantics.hpp"
#include "EmitDiagnostics.hpp"

#define MAXCHILDREN 3


char Buffer[256]; 
int nErrors; 
int nWarnings;
bool scopeDepth = true;
bool Flag = false;
bool loop = false;
bool range = false;
int loopDepth = 1;

bool inFor = false;
bool sizeOfArrayFlg = false;
int rangePos = 0;
int returnm_lineNumber;
int functionLine;

std::string functionName;

Node* curFunc = nullptr;

ParmType functionReturnType;
ParmType actualReturnType;
SymbolTable symbolTable;

//function retrives symbol table
SymbolTable getSymbolTable() 
{
    return symbolTable;
}

//analyzes the three types of nodes in the AST (Decl, Exp, Stmt) and calls the appropriate function
void analyze(Node* node, int& nErrors, int& nWarnings)
{

    if(node == NULL)
    {
        return;
    }
    switch(node->m_nodeType)
    {
        case DECLARATION:
                    {
                        analyzeDecl(node, nErrors, nWarnings);
                    }
                    break;

        case STATEMENT:
                    {
                        analyzeStmt(node, nErrors, nWarnings);
                    }
                    break;

        case EXPRESSION:
                    {
                        analyzeExp(node, nErrors, nWarnings);
                    } 
                    break;
    }

    if(node->m_siblingNode != nullptr)
    {
        analyze(node->m_siblingNode, nErrors, nWarnings);
    }
}

//function analyzes semantics. Also checks for undefined main warnings
void semanticAnalysis(Node* node, int& errors, int& warnings)
{

    analyze(node, nErrors, nWarnings);

    symbolTable.applyToAll(analyzeWarnings);
    symbolTable.applyToAllGlobal(analyzeWarnings);

 
    Node* mainCheck = (Node*)symbolTable.lookup("main");
    
    if(mainCheck == nullptr)
    {
        EmitDiagnostics::Error::emitLinkerError("A function named 'main' with no parameters must be defined.");
        //printError(16, 0, 0, NULL, NULL, NULL, 0);
    }
    else if(mainCheck != nullptr)
    {
        if(mainCheck->m_nodeType == NodeType::DECLARATION && mainCheck->nodeSubType.declaration != DeclarationType::FUNCTION)
        {
            EmitDiagnostics::Error::emitLinkerError("A function named 'main' with no parameters must be defined.");
            //printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
        else if(mainCheck->m_childernNodes[0] != nullptr && mainCheck->m_childernNodes[0]->nodeSubType.declaration == DeclarationType::PARAMETER)
        {
            EmitDiagnostics::Error::emitLinkerError("A function named 'main' with no parameters must be defined.");
            //printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
    }

    // PrintErrorss();
    // errors = nErrors;
    // warnings = nWarnings;
}

//function checks to see if warnings were used.
void analyzeWarnings(std::string symbol, void* t)
{

    Node* node;

    node = (Node *)symbolTable.lookup(symbol.c_str());     

    if(!node->m_isUsed && !node->m_isGlobal)
    {

        if(node->nodeSubType.declaration == DeclarationType::PARAMETER && !node->m_isUsedError && node->nodeAttributes.name == "main")
        {
            node->m_isUsedError = true;
            EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber,"The parameter '" + node->nodeAttributes.name + "' seems not to be used.");
            //printError(21, node->m_lineNumber, 0, node->nodeAttributes.name, NULL, NULL, 0);
        }

        else if(node->nodeSubType.declaration == DeclarationType::FUNCTION && !node->m_isUsedError && node->nodeAttributes.name == "main")
        {
            node->m_isUsedError = true;
            EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber,"The function '" + node->nodeAttributes.name + "' seems not to be used.");
            // printError(20, node->m_lineNumber, 0, node->nodeAttributes.name, NULL, NULL, 0);
        }

        else
        {
            node->m_isUsedError = true;
            EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber,"The variable '" + node->nodeAttributes.name + "' seems not to be used.");
            // printError(17, node->m_lineNumber, 0, node->nodeAttributes.name, NULL, NULL, 0);
        }
    }

    else if(!node->m_isUsed && node->m_isGlobal && node->nodeSubType.declaration == DeclarationType::FUNCTION)
    {
        
        if(node->nodeAttributes.name == "main" && !node->m_isUsedError)
        {
            node->m_isUsedError = true;
            EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber,"The function '" + node->nodeAttributes.name + "' seems not to be used.");
            // printError(20, node->m_lineNumber, 0, node->nodeAttributes.name, NULL, NULL, 0);
        }
    }

    else if(!node->m_isUsed && node->m_isGlobal && !node->m_isUsedError)
    {
        node->m_isUsedError = true;
        EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber,"The variable '" + node->nodeAttributes.name + "' seems not to be used.");
        // printError(17, node->m_lineNumber, 0, node->nodeAttributes.name, NULL, NULL, 0);
    }
}

//function prints errors encountered for array data containers
void printArrayErrors(Node* node)
{

   Node* leftNode = node->m_childernNodes[0];
   Node* rightNode = node->m_childernNodes[1];


   if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER)
    {
        leftNode = (Node* )symbolTable.lookup(node->m_childernNodes[0]->nodeAttributes.name);
        
        if(leftNode != nullptr)
        {
            node->m_childernNodes[0]->m_parmType = leftNode->m_parmType;
            node->m_parmType = leftNode->m_parmType;
        }


        if(leftNode == nullptr || !leftNode->m_isArray)
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot index nonarray '" + node->m_childernNodes[0]->nodeAttributes.name + "'."); 
            // printError(15, t->m_lineNumber, 0, t->child[0]->nodeAttributes.name, NULL, NULL, 0);
        }
    }
   else
    {
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot index nonarray '" + node->m_childernNodes[0]->nodeAttributes.name + "'."); 
        // printError(15, t->m_lineNumber, 0, t->child[0]->nodeAttributes.name, NULL, NULL, 0);
    }
    if(node->m_childernNodes[1] != nullptr)
    {
        if(node->m_childernNodes[1]->m_parmType != ParmType::INTEGER && node->m_childernNodes[1]->m_parmType != ParmType::UNDEFINED)
        {

            if(node->m_childernNodes[1]->nodeSubType.declaration == DeclarationType::PARAMETER && node->m_childernNodes[1]->nodeSubType.expression != ExpressionType::CALL && node->m_childernNodes[1]->m_parmType == ParmType::VOID)
            {
                //do nothing
            }
            else
            {
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Array '" + node->m_childernNodes[0]->nodeAttributes.name + "' should be indexed by type int but got type '" + ConvertParmToString(node->m_childernNodes[1]->m_parmType) + "'.");
                // printError(14, t->m_lineNumber, 0, t->m_childernNodes[0]->nodeAttributes.name, ExpTypetwo(t->child[1]->expType), NULL, 0);
            }
            
        }
    }
   if(node->m_childernNodes[1] != nullptr && node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::IDENTIFIER)
   {
        if(rightNode != nullptr && rightNode->m_isArray == true)
        {
            // printError(13, t->m_lineNumber, 0, rightNode->nodeAttributes.name, NULL, NULL, 0);
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Array index is the unindexed array '" + rightNode->nodeAttributes.name + "'.");
        }
        if(rightNode != nullptr)
        {
            node->m_childernNodes[1]->m_parmType = rightNode->m_parmType;
        }
   }

}

//function analyzes declaration nodes
void analyzeDecl(Node* node, int& nErrors, int& nWarnings)
{
  
    if(symbolTable.depth() == 1)
    {
        node->m_isGlobal = true;
    }
    else
    {
        node->m_isGlobal = false;
    }

    Node* declared;
    
    if(node->nodeSubType.declaration != DeclarationType::VARIABLE && !symbolTable.insert(node->nodeAttributes.name, node))
    {
        declared = (Node* )symbolTable.lookup(node->nodeAttributes.name);
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Symbol '" + node->nodeAttributes.name +  "' is already declared at line " + std::to_string(declared->m_lineNumber) + ".");
        // printError(0, t->m_lineNumber, declared->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
    }

    switch(node->nodeSubType.declaration)
    {
        
        case DeclarationType::VARIABLE:
        {
            if(node->m_childernNodes[0] != nullptr)
            {

                for(int i = 0; i < MAXCHILDREN; i++)
                {
                    analyze(node->m_childernNodes[i], nErrors, nWarnings);
                }
            }          

           Node* exists;


           if(!symbolTable.insert(node->nodeAttributes.name, node))
           {
                exists = (Node*)symbolTable.lookup(node->nodeAttributes.name);
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Symbol '" + node->nodeAttributes.name +  "' is already declared at line " + std::to_string(exists->m_lineNumber) + ".");
                //printError(0, t->m_lineNumber, exists->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
           }

           if(node->m_siblingNode != nullptr)
           {

                if(node->m_isStatic && node->m_lineNumber == node->m_siblingNode->m_lineNumber)
                {
                    node->m_siblingNode->m_isStatic = node->m_isStatic;
                }
            }

           if(node->m_childernNodes[0] != nullptr)
           {
               if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER || node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::CALL)
               {
                //    printError(32, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' is not a constant expression.");
               }

               else if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::OP)
               {

                   if(node->m_childernNodes[0] != nullptr && node->m_childernNodes[0]->m_childernNodes[1] == nullptr)
                   {

                       if(node->m_childernNodes[0]->nodeAttributes.name == "-" && !node->m_isArray)
                       {
                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' is not a constant expression.");
                        //printError(32, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                       }
                   }

                   else if(node->m_childernNodes[0]->m_childernNodes[0] != nullptr && node->m_childernNodes[0]->m_childernNodes[1] != nullptr)
                   {
                       analyzeNestedOperators(node, node->m_childernNodes[0]);
                   }
               }

               if(node->m_parmType != node->m_childernNodes[0]->m_parmType)
               {

                    if(node->m_parmType == ParmType::CHAR && node->m_childernNodes[0]->m_parmType == ParmType::CHARINT)
                    {
                        ; // do nothing
                    }

                    else if(node->m_parmType == ParmType::INTEGER && node->m_childernNodes[0]->m_parmType == ParmType::CHARINT)
                    {
                        char charInsert[] = "char";
                        // Initializer for variable '%s' of type %s is of type %s
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' of type " + ConvertParmToString(node->m_parmType) + " is of type char.");
                        //printError(33, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(t->expType), charInsert, 0);
                    }

                    else if(node->m_childernNodes[0]->m_parmType == ParmType::VOID && node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER)
                    {
                       //do nothing 
                    }

                    else
                    {
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' of type " + ConvertParmToString(node->m_parmType) + " is of type " + ConvertParmToString(node->m_childernNodes[0]->m_parmType) + ".");
                        //printError(33, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(t->expType), ExpTypetwo(t->child[0]->expType), 0);
                    }
               }

               if(node->m_isArray && !node->m_childernNodes[0]->m_isArray)
               {
                // Initializer for variable '%s' requires both operands be arrays or not but variable is an array and rhs is not an array.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' requires both operands be arrays or not but variable is an array and rhs is not an array.");
                //    printError(35, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
               }

               if(!node->m_isArray && node->m_childernNodes[0]->m_isArray)
               {
                //Initializer for variable '%s' requires both operands be arrays or not but variable is not an array and rhs is an array.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' requires both operands be arrays or not but variable is not an array and rhs is an array.");
                //    printError(34, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
               }

               node->m_isInitialized = true;
               node->m_isDeclared = true;        
           }
           else
           {
               node->m_isDeclared = true;
           }

        }
        break;

        case DeclarationType::FUNCTION:
                                    {
                                        curFunc = node;
                                        Flag = false;

                                        symbolTable.enter(node->nodeAttributes.name);

                                        scopeDepth = false;
                                        functionReturnType = node->m_parmType;
                                        functionName = node->nodeAttributes.name;
                                        functionLine = node->m_lineNumber;
                                        
                                        //analyze childern nodes
                                        for(int i = 0; i < MAXCHILDREN; i++)
                                        {
                                            analyze(node->m_childernNodes[i], nErrors, nWarnings);
                                        }

                                        if(Flag == false && node->m_parmType != ParmType::VOID)
                                        {
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Expecting to return type " + ConvertParmToString(node->m_parmType) + " but function '" + node->nodeAttributes.name + "' has no return statement.");
                                            //printError(19, node->m_lineNumber, 0, ExpTypetwo(functionReturnType), node->nodeAttributes.name, NULL, 0);
                                        }

                                        symbolTable.applyToAll(analyzeWarnings);
                                        symbolTable.leave();
                                        curFunc = nullptr;
                                    }
                                    break;

        case DeclarationType::PARAMETER:
                                    {
                                        for(int i = 0; i < MAXCHILDREN; i++)
                                        {
                                            
                                            analyze(node->m_childernNodes[i], nErrors, nWarnings);
                                            
                                            if(node->m_childernNodes[0] != nullptr)
                                            {
                                                node->m_childernNodes[0]->m_isInitialized = true;
                                            }
                                        }
                                        node->m_isInitialized = true;
                                    }
                                    break;
    }
}


void analyzeVar(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeFunc(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeParam(Node* node, int& nErrors, int& nWarnings)
{

}
//Function analyzes statement nodes

void analyzeStmt(Node* node, int& nErrors, int& nWarnings)
{

    switch(node->nodeSubType.statement)
    {
        case StatementType::IF:
        {
            loop = true;
            symbolTable.enter(node->nodeAttributes.name);
            loopDepth++;
            scopeDepth = false;
            
            for(int i = 0; i < MAXCHILDREN; i++)
            {
                if(node->m_childernNodes[0])
                {
                    analyze(node->m_childernNodes[i], nErrors, nWarnings);
                }
            }


            if(node->m_childernNodes[0]->m_parmType != ParmType::BOOL && node->m_childernNodes[0]->nodeSubType.expression != ExpressionType::OP && !node->m_childernNodes[0]->m_isDeclError)
            {
                // char ifStmt[] = "if";
                //Expecting Boolean test condition in %s statement but got type %s.
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Expecting Boolean test condition in if statement but got type " + ConvertParmToString(node->m_childernNodes[0]->m_parmType) + ".");
                // printError(27, t->m_lineNumber, 0, ifStmt, ExpTypetwo(t->m_childernNodes[0]->expType), NULL, 0 );
            }

            if(node->m_childernNodes[0]->m_isArray)
            {
                // char ifStmt[] = "if";
                //Cannot use array as test condition in %s statement.
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot use array as test condition in if statement.");
                // printError(23, t->m_lineNumber, 0, ifStmt, NULL, NULL, 0);
            }
            
            loopDepth--;

            symbolTable.applyToAll(analyzeWarnings);

            if(loopDepth == 1)
            {
                loop = false;
            }
            symbolTable.leave();
            scopeDepth = true;
        }
        break;

        case StatementType::FOR:
        {
            loop = true;
            inFor = true;
            loopDepth++;
            symbolTable.enter(node->nodeAttributes.name);
            scopeDepth = false;
            
            for(int i = 0; i < MAXCHILDREN; i++)
            {
                if(node->m_childernNodes[i])
                {
                    analyze(node->m_childernNodes[i], nErrors, nWarnings);
                    node->m_childernNodes[0]->m_isInitialized = true;
                    node->m_childernNodes[1]->m_isInitialized = true;
                }
            }

            loopDepth--;

            if(loopDepth == 1)
            {
                loop = false;
            }

                inFor = false;
                symbolTable.applyToAll(analyzeWarnings);
                symbolTable.leave();
                scopeDepth = true;
        }
        break;

        case StatementType::WHILE:
        {

            loop = true;
            symbolTable.enter(node->nodeAttributes.name);
            loopDepth ++;
            scopeDepth = false;

            for(int i = 0; i < MAXCHILDREN; i++)
            {
                if(node->m_childernNodes[i])
                {
                    analyze(node->m_childernNodes[i], nErrors, nWarnings);

                    if(i < 1)
                    {
                        if(node->m_childernNodes[0]->m_parmType != ParmType::BOOL && node->m_childernNodes[0]->nodeSubType.expression != ExpressionType::OP && !node->m_childernNodes[0]->m_isDeclError)
                        {
                            // char whileStmt[] = "while";
                            //Expecting Boolean test condition in %s statement but got type %s.
                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Expecting Boolean test condition in while statement but got type " + ConvertParmToString(node->m_childernNodes[0]->m_parmType) + ".");
                            // printError(27, t->m_lineNumber, 0, whileStmt, ExpTypetwo(t->m_childernNodes[0]->expType), NULL, 0 );
                        }

                        if(node->m_childernNodes[0]->m_isArray)
                        {
                            // char whileStmt[] = "while";
                            //Cannot use array as test condition in %s statement.
                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot use array as test condition in while statement.");
                            // printError(23, t->m_lineNumber, 0, whileStmt, NULL, NULL, 0);
                        }
                    }
                }
            }

            loopDepth--;

            symbolTable.applyToAll(analyzeWarnings);

            if(loopDepth == 1)
            {
                loop = false;
            }

            symbolTable.leave();
            
            scopeDepth = true;
        }
        break;

        case StatementType::RETURN:
        {
            Flag = true;
            returnm_lineNumber = node->m_lineNumber;

            analyze(node->m_childernNodes[0], nErrors, nWarnings);

            if(node->m_childernNodes[0] != nullptr)
            {

                actualReturnType = node->m_childernNodes[0]->m_parmType;

                if(curFunc == nullptr)
                {
                    break;
                }

                else if(node->m_childernNodes[0]->m_isArray)
                {
                    //Cannot return an array.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot return an array.");
                    // printError(10, t->m_lineNumber, 0, NULL, NULL, NULL, 0);
                }

                else if(node->m_childernNodes[0]->m_childernNodes[0] != nullptr)
                {
                    if(node->m_childernNodes[0]->m_childernNodes[0]->m_isArray)
                    {

                        if(node->m_childernNodes[0]->nodeAttributes.name == "[")
                        {
                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot return an array.");
                            // printError(10, t->m_lineNumber, 0, NULL, NULL, NULL, 0);
                        }
                    }
                }
            
                if(functionReturnType == ParmType::VOID)
                {
                    //Function '%s' at line %d is expecting no return value, but return has a value.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting no return value, but return has a value.");
                    // printError(29, returnm_lineNumber, functionLine, functionName, NULL, NULL, 0);
                }

                else if(functionReturnType != actualReturnType && actualReturnType != ParmType::VOID && functionReturnType != ParmType::VOID)
                {

                    if(!(functionReturnType == ParmType::CHAR && actualReturnType == ParmType::CHARINT))
                    {
                        //Function '%s' at line %d is expecting to return type %s but returns type %s.
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting to return type " + ConvertParmToString(functionReturnType) + " but returns type " + ConvertParmToString(actualReturnType) + ".");
                        // printError(31, returnm_lineNumber, functionLine, functionName, ExpTypetwo(functionReturnType), ExpTypetwo(actualReturnType), 0);
                    }
                }

                else if(functionReturnType != actualReturnType && functionReturnType != ParmType::VOID && node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::CALL)
                {
                    
                    if(!(functionReturnType == ParmType::CHAR && actualReturnType == ParmType::CHARINT))
                    {
                        //Function '%s' at line %d is expecting to return type %s but returns type %s.
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting to return type " + ConvertParmToString(functionReturnType) + " but returns type " + ConvertParmToString(actualReturnType) + ".");
                        // printError(31, returnm_lineNumber, functionLine, functionName, ExpTypetwo(functionReturnType), ExpTypetwo(actualReturnType), 0);
                    }
                }
            }

            else if(node->m_childernNodes[0] == nullptr)
            {

                if(functionReturnType != ParmType::VOID)
                {
                    //Function '%s' at line %d is expecting to return type %s but return has no value.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting to return type " + ConvertParmToString(functionReturnType) + " but return has no value.");
                    // printError(30, returnm_lineNumber, functionLine, functionName, ExpTypetwo(functionReturnType), NULL, 0);
                }
            }

        }
        break;

        case StatementType::BREAK:
        {
            if(!loop)
            {
                //Cannot have a break statement outside of loop.
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot have a break statement outside of loop.");
                // printError(22, node->m_lineNumber, 0, NULL, NULL, NULL, 0);
            }

        }
        break;


        case StatementType::RANGE:
        {
            rangePos;
            range = true;

            for(int i = 0; i < MAXCHILDREN; i++)
            {
                if(node->m_childernNodes[i])
                {
                    rangePos++;

                        if(node->m_childernNodes[i]->m_childernNodes[0] != nullptr && node->m_childernNodes[i]->m_childernNodes[0]->m_isArray)
                        {
                            node->m_childernNodes[i]->m_childernNodes[0]->m_isIndexed = true;
                        }

                        else if(rangePos == 1)
                        {
                            if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER)
                            {
                                Node* valFound = (Node *)symbolTable.lookup(node->m_childernNodes[0]->nodeAttributes.name);
                                if(valFound == nullptr)
                                {
                                    //Symbol '%s' is not declared.
                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Symbol '" + node->m_childernNodes[0]->nodeAttributes.name + "' is not declared.");
                                    // printError(1, t->m_lineNumber, 0, node->child[0]->nodeAttributes.name, NULL, NULL, 0); 
                                    node->m_isDeclError = true;
                                }
                                else
                                {
                                    valFound->m_isUsed = true;
                                }
                            }
                        }

                    analyze(node->m_childernNodes[i], nErrors, nWarnings);

                }
            }

            range = false;
            rangePos = 0;
        }
        break;

        case StatementType::COMPOUND:
        {
            bool keepCurScope = scopeDepth;

            if(keepCurScope)
            {
                
                symbolTable.enter("compound");
            }
            else
            {
                scopeDepth = true;
            }

            for(int i = 0; i < MAXCHILDREN; i++)
            {
                analyze(node->m_childernNodes[i], nErrors, nWarnings);
            }

            if(keepCurScope)
            {
                symbolTable.applyToAll(analyzeWarnings);
                symbolTable.leave();
            }
        }
        break;
    }
}


void analyzeNullStmt(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeIf(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeWhile(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeFor(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeCompound(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeReturn(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeBreak(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeRange(Node* node, int& nErrors, int& nWarnings)
{

}

//function analyzes expression nodes. 
void analyzeExp(Node* node, int& nErrors, int& nWarnings)
{
 
    bool leftStr, rightStr, isBinary, leftArr, rightArr, leftIndx, rightIndx, leftInit, leftDecl, rightInit, rightDecl, throwError;
    leftStr = rightStr = isBinary = leftArr = rightArr = leftIndx = rightIndx = leftInit = leftDecl = rightInit = rightDecl = throwError = false;

    ParmType leftSide, rightSide, returnType, leftExpected, rightExpected, childReturnType;
    leftSide = rightSide = returnType = leftExpected = rightExpected = childReturnType = ParmType::UNDEFINED;

    bool rightErr, leftErr, unaryErrors;
    rightErr = leftErr = unaryErrors = false;

    Node* valFound = nullptr;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;

    switch(node->nodeSubType.expression) 
    {
        case ExpressionType::ASSIGN:
        case ExpressionType::OP:

            if(node->nodeAttributes.name != "<=")
            {

                if(node->m_childernNodes[0] != NULL)
                {
                    
                    if(node->m_childernNodes[0]->m_childernNodes[0]!= nullptr  && node->m_childernNodes[0]->nodeAttributes.name != "[")
                    {
                        node->m_childernNodes[0]->m_childernNodes[0]->m_isInitialized = true;

                        if(node->m_childernNodes[0]->m_childernNodes[1] != nullptr)
                        {
                            node->m_childernNodes[0]->m_childernNodes[1]->m_isInitialized = true;

                            if(node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[0] != nullptr && node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[1] != nullptr)
                            {

                                if(node->m_childernNodes[0]->m_childernNodes[1]->nodeSubType.expression == ExpressionType::OP)
                                {
                                    node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[0]->m_isInitialized = true;
                                    node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[1]->m_isInitialized = true;
                                }
                            }
                        }

                        else if(node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[0] != nullptr)
                        {
                            node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[0]->m_isInitialized = true;
                        }

                    }

                    else if(node->m_childernNodes[1] != nullptr && node->m_childernNodes[1]->m_parmType == ParmType::VOID)
                    {

                        if(node->m_childernNodes[1]->nodeAttributes.name != "<=")
                        {
                            node->m_childernNodes[0]->m_isInitialized = true;
                        }

                        if(node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::CALL)
                        {
                            node->m_childernNodes[0]->m_isInitialized = true;
                        }

                        else if(node->m_childernNodes[1]->nodeAttributes.name != "[")
                        {

                            // char* lhs = strdup(node->m_childernNodes[0]->nodeAttributes.name);
                            std::string lhs = node->m_childernNodes[0]->nodeAttributes.name;
                            std::string rhs = node->m_childernNodes[1]->nodeAttributes.name;

                            if(lhs == rhs)
                            {
                                node->m_childernNodes[0]->m_isInitialized = true;
                            }

                        }
                        else if(node->m_childernNodes[0] != nullptr && node->m_childernNodes[1] != nullptr)
                        {
    
                            if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER && !node->m_childernNodes[0]->m_isInitialized)
                            {
        
                                if(node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::IDENTIFIER)
                                {

                                    // char* lhs = strdup(node->m_childernNodes[0]->nodeAttributes.name);
                                    std::string lhs = node->m_childernNodes[0]->nodeAttributes.name;
                                    std::string rhs = node->m_childernNodes[1]->nodeAttributes.name;

                                    if(lhs == rhs)
                                    {
                                        node->m_childernNodes[0]->m_isInitialized = true;
                                    }
                                }

                                else if(node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::ASSIGN)
                                {
                                    analyzeNestedAssign(node->m_childernNodes[1]);
                                    node->m_childernNodes[0]->m_isInitialized = true;
                                }
                            }
                        }

                        else
                        {
                            //do nothing
                        }
                    }
                   
                    else 
                    {

                        if(node->m_childernNodes[1] != nullptr && node->m_childernNodes[1]->m_childernNodes[0] != nullptr)
                        {
    
                            if(node->m_childernNodes[1]->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER)
                            {

                                // char *c0 = strdup(t->child[0]->nodeAttributes.name);
                                // char *c10 = strdup(t->child[1]->child[0]->nodeAttributes.name);
                                std::string child_0 = node->m_childernNodes[0]->nodeAttributes.name;
                                std::string child_0_1 = node->m_childernNodes[1]->m_childernNodes[0]->nodeAttributes.name;

                                if(child_0 == child_0_1)
                                {
                                    node->m_childernNodes[0]->m_isInitialized = true;
             
                                }
                            }

                            else
                            {
                                node->m_childernNodes[0]->m_isInitialized = true;
                            }
                            

                        }

                        else
                        {
                            node->m_childernNodes[0]->m_isInitialized = true;
                        }
                    }
                }

            }

            if(node->nodeAttributes.name == "<=")
            {
                if(node->m_childernNodes[0] != nullptr)
                {
                    node->m_childernNodes[0]->m_isUsed = true;
                    
                }
                if(node->m_childernNodes[1] != nullptr)
                {
                    node->m_childernNodes[1]->m_isUsed = true;
                }
            }

            if(node->nodeAttributes.name != "*")
            {
                sizeOfArrayFlg = true;
            }

            for(int i= 0; i < MAXCHILDREN; i++)
            {
                analyze(node->m_childernNodes[i], nErrors, nWarnings);
            }

            sizeOfArrayFlg = false;

            if(node->m_childernNodes[0] != nullptr)
            {
                leftNode = node->m_childernNodes[0];
                leftSide = leftNode->m_parmType;
                leftArr = leftNode->m_isArray;

                if(leftNode->child[0] != NULL)
                {
                    leftArr = false; 
                    leftIndx = true; 
                }
                if(leftNode->nodekind == ExpK)
                {
                    if(leftNode->nodeSubType.exp == CallK)
                    {
                        leftArr = false;
                    }
                    if(leftNode->nodeSubType.exp == ConstantK)
                    {
                        leftStr = true;
                    }
                }
            }

            if(t->child[1] != NULL){
                rightNode = t->child[1];
                rightSide = rightNode->expType;
                rightArr = rightNode->isArray;
                

                if(rightNode->child[0] != NULL){
                    rightArr = false; 
                    rightIndx = true; 
                }
                if(rightNode->nodekind == ExpK){
                    if(rightNode->nodeSubType.exp == CallK)
                    {
                        rightArr = false;
                    }
                    if(rightNode->nodeSubType.exp == ConstantK)
                    {
                        rightStr = true;
                    }
                }
                isBinary = true;
            }

            getExpTypes(t->nodeAttributes.name, isBinary, unaryErrors, leftExpected, rightExpected, returnType);

            if(leftSide == Void && !(leftNode->nodekind == ExpK && leftNode->nodeSubType.exp == CallK)){
                leftErr = true;
            }
            if(rightSide == Void && !(rightNode->nodekind == ExpK && rightNode->nodeSubType.exp == CallK))
            {
                rightErr = true;
            }

            if(!isBinary && !leftErr){
 
                if(leftSide != leftExpected && leftExpected != UndefinedType)
                {

                    if(!strcmp(t->nodeAttributes.name, "-")){
                        char uMinus[] = "chsign";
                        // printError(9, t->m_lineNumber, 0, uMinus, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                    }

                    else{
                        // printError(9, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                    }
                }

                else if(!strcmp(t->nodeAttributes.name, "not") && leftSide != leftExpected)
                {

                    // printError(9, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                }

                else if(!strcmp(t->nodeAttributes.name, "*") && (!leftArr && leftSide != UndefinedType))
                {
                    char uSizeof[] = "sizeof";
                    // printError(8, t->m_lineNumber, 0, uSizeof, NULL, NULL, 0);
                } 

                if(leftArr)
                {
                    if(strcmp(t->nodeAttributes.name, "*") != 0)
                    {

                        if(!strcmp(t->nodeAttributes.name, "-"))
                        {
                            char uMinus[] = "chsign";
                            // printError(7, t->m_lineNumber, 0, uMinus, NULL, NULL, 0);
                        }
                        else{
                            // printError(7, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                        }
                    }
                }
            }
                else{
                    if(!unaryErrors){

                        if(!strcmp(t->nodeAttributes.name, "[")){
                            errorsArray(t);
                        }
                
                        else if(leftSide != rightSide && !leftErr && !rightErr){

                            if(!strcmp(ExpTypetwo(leftSide), "int") && !strcmp(ExpTypetwo(rightSide), "CharInt")){
                                char diffCharInt[] = "char";
                                //  printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), diffCharInt, 0);
                            }
                            else if(!strcmp(ExpTypetwo(leftSide), "char") && !strcmp(ExpTypetwo(rightSide), "CharInt")){
                                ; //do nothing
                            }
  
                            else if(!strcmp(t->nodeAttributes.name, "<=") && t->child[1]->nodeSubType.exp == OpK){
 
                                getReturnType(t->child[1]->nodeAttributes.name, isBinary, childReturnType);
                               
                                if(childReturnType != t->child[0]->expType){
                                    // printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), ExpTypetwo(childReturnType), 0);
                                }

                                else if(t->child[1]->child[1] != NULL && t->child[1]->child[1]->nodeSubType.exp == CallK){
                                    // printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), ExpTypetwo(childReturnType), 0);
                                }
                            }
                            else{

                                if(t->child[0]->nodeSubType.exp != CallK){

                                //  printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), ExpTypetwo(rightSide), 0);
                                }
                                else{}
                            }
                        }
                    }


                    if(!(leftExpected == UndefinedType || rightExpected == UndefinedType)){
                        
                        if(leftExpected == CharInt || rightExpected == CharInt){

                            ;
                        }

                        else if(leftSide == rightSide && leftNode->nodeSubType.exp == CallK && rightNode->nodeSubType.exp == CallK){

                             TreeNode* lhs = (TreeNode*)symbolTable.lookup(t->child[0]->nodeAttributes.name);
                             TreeNode* rhs = (TreeNode*)symbolTable.lookup(t->child[1]->nodeAttributes.name);

                             if(lhs != NULL && rhs != NULL){

                                 if(lhs->nodeSubType.decl == FuncK && rhs->nodeSubType.decl == FuncK && !lhs->isIO && !rhs->isIO){
                                     if(t->child[0]->expType == Void && t->child[1]->expType == Void){
                                    //  printError(3, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                    //  printError(4, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                     }
                                     
                                 }

                             }
                        }
                        else{

                            if(leftSide != leftExpected && !leftErr){
                                // printError(3, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                            }

                            if(rightSide != rightExpected && !rightErr && rightSide != UndefinedType){

                                if(rightSide == Void && t->child[1]->nodeSubType.exp == CallK && returnType != Boolean){
                                    // printError(4, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                }
                                else if(rightSide != Void){
                                    // printError(4, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                }
                            }
                        }
                    }

                    if(leftArr || rightArr){

                        if(strcmp(t->nodeAttributes.name, "<=") && leftExpected != UndefinedType){
                            if(!strcmp(t->nodeAttributes.name, "<") || !strcmp(t->nodeAttributes.name, ">") || !strcmp(t->nodeAttributes.name, "=") || !strcmp(t->nodeAttributes.name, "!>") || !strcmp(t->nodeAttributes.name, "!<") || !strcmp(t->nodeAttributes.name, "><")){
                         
                                 if(leftArr && !rightArr){
                                // printError(5, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                }

                                else if(!leftArr && rightArr){
                                // printError(6, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                }
                            }

                            else{
                            // printError(7, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                            }
                        }
                        
                        else{
                            if(!strcmp(t->nodeAttributes.name, "[")){
                                ;
                            }

                            else if((leftArr && !rightArr) || (!leftArr && rightArr)){

                                if(leftArr && !rightArr){
                                // printError(5, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                }

                                else if(!leftArr && rightArr){
                                    // printError(6, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                }
                            }
                        }
                    }
                }

            if(returnType != UndefinedType){
                t->expType = returnType;
            }
            else{
                t->expType = leftSide;
            }
            break;

        case ConstantK:
            for(int i = 0; i < MAXCHILDREN; i++){
                check(t->child[i], nErrors, nWarnings);
            }
    
            if(range){
                   if(inFor){


                    if(t->expType != Integer)
                    {
                        char intExpect[] = "int";
                        // printError(26, t->m_lineNumber, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                    }
                   }
               }
            break;

        case IdK:
            valFound = (TreeNode*)symbolTable.lookup(t->nodeAttributes.name);

            if(valFound == NULL){

                if(range && rangePos == 1){
                    t->isDeclared = true;
                }

                else{
                    // printError(1, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0); 
                        t->declErr = true;    
                }           
            }

            else if(range){

                if(inFor){

                    t->expType = valFound->expType;
                    t->isArray = valFound->isArray;

                    if(t->expType != Integer && rangePos >= 1)
                    {
                        if(!sizeOfArrayFlg){

                            if(!strcmp(t->nodeAttributes.name, "main")){
                                // printError(12, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);  
                            }
                            else{
                                char intExpect[] = "int";
                                // printError(26, t->m_lineNumber, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                            }
                        }

                    }

                    if(rangePos >= 1 && !valFound->isInit){
                        if(valFound->isDeclared == true){

                            if(!valFound->isInit && !valFound->warningReported && !valFound->isStatic && !valFound->isGlobal){

                                if(!t->isInit){
                                    valFound->warningReported = true;
                                    valFound->wasUsed = true;
                                    // printError(18, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                }
                                
                                else{
                                    valFound->isInit = true;
                                }
                            }
                    
                        }
                    }

                    else if(rangePos > 1 && valFound->isInit){
                        valFound->wasUsed = true;
                    }

                    if(valFound->isArray && !sizeOfArrayFlg && !t->isIndexed){
                        // printError(24, t->m_lineNumber, 0, NULL, NULL, NULL, rangePos);
                    }

                    t->isIndexed = false;

                }

                t->isInit = true;
            }

            else{

                 if(valFound->isDeclared == true){
                
                 if(!valFound->isInit && !valFound->warningReported && !valFound->isStatic && !valFound->isGlobal){
                     if(!t->isInit){
                        valFound->warningReported = true;
                        // printError(18, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                     }
                     else{
                         valFound->isInit = true;
                     }
                 }
                 }

                if(valFound->nodeSubType.decl == FuncK){
                    // printError(12, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                    valFound->wasUsed = true;
                    break;
                }
                else{
                    t->expType = valFound->expType;
                    t->isArray = valFound->isArray;
                    t->isGlobal = valFound->isGlobal;
                    t->isStatic = valFound->isStatic;

                    if(!range && valFound->nodeSubType.decl != FuncK){
                    valFound->wasUsed = true;
                    }
                }

                if(t->child[0] != NULL){
                    check(t->child[0], nErrors, nWarnings);
                    if(t->child[0]->expType == Void && !(t->child[0]->nodekind == ExpK && t->child[0]->nodeSubType.exp == CallK)){

                        break;
                    }
                    if(!t->isArray){

                        break;
                    }
                    else{

                        if(t->child[0]->expType != Integer){
                            // printError(14, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(t->child[0]->expType), NULL, 0);
                        }
 
                        if(t->child[0]->isArray && t->child[0]->child[0] == NULL){
                            // printError(13, t->m_lineNumber, 0, t->child[0]->nodeAttributes.name, NULL, NULL, 0);
                        }
                    }
                }
            }
            break;

        case CallK:
            int paramCount = 1;
            TreeNode* funcFound;

            if(t->nodeSubType.exp == CallK){
                funcFound = (TreeNode*)symbolTable.lookup(t->nodeAttributes.name);
                if(funcFound == NULL){
                    // printError(1, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);  
                        t->declErr = true; 
                }
                else{
                   
                }
            }

             for(int i = 0; i < MAXCHILDREN; i++){
                check(t->child[i], nErrors, nWarnings);
                }

            if(funcFound != NULL){
                t->expType = funcFound->expType;
                t->isArray = funcFound->isArray;
                t->isGlobal = funcFound->isGlobal;
                t->isStatic = funcFound->isStatic;
                funcFound->wasUsed = true;


                if(funcFound->nodeSubType.decl != FuncK){
                    // printError(11, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                }
                

                else if(range){

                    if(inFor){

                        if(t->expType != Integer)
                        {

                            if(!strcmp(t->nodeAttributes.name, "main")){
                                // printError(12, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);                               
                            }
                            else{
                                char intExpect[] = "int";
                                // printError(26, t->m_lineNumber, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                            }
                        }
                    }
                }

                else{

                    if(funcFound->child[0] != NULL && t->child[0] != NULL){
                       parameterErrors(funcFound, t, funcFound->child[0], t->child[0], paramCount);
                    }

                    else if(funcFound->child[0] == NULL && t->child[0] != NULL){
                        // printError(38, t->m_lineNumber, funcFound->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
                    }

                    else if(funcFound->child[0] != NULL && t->child[0] == NULL){
                        // printError(37, t->m_lineNumber, funcFound->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
                    }
                }
            }
      
            break;        
    }

}

void analyzeOp(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeConst(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeId(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeAssign(Node* node, int& nErrors, int& nWarnings)
{

}


void analyzeInit(Node* node, int& nErrors, int& nWarnings)
{

}



//function gets all expected types. 
void getExpTypes(std::string op, bool isBinary, bool &unaryErrors, ParmType &left, ParmType &right, ParmType &rightT)
{

    std::string unaryOps[6] = {"not", "*", "?", "-", "--", "++"};

    std::string binaryOps[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", "!<", "!>", "==", "!=", "=", "and", "or"};

    unaryErrors = false;

    if(!isBinary)
    {

        for(int i = 0; i < 6; i++)
        {

            if(op == unaryOps[i])
            {

                if(i == 0)
                {
                    left = right = rightT = ParmType::BOOL;
                }

                if(i == 1)
                {
                    left = right = ParmType::UNDEFINED;
                    rightT = ParmType::INTEGER;
                }

                if(i >= 2)
                {
                    left = right = rightT = ParmType::INTEGER;
                }
            }
        }
    }
    else
    {

        for(int i = 0; i < 18; i++)
        {

            if(op == binaryOps[i])
            {

                if(i >= 0 && i <= 8)
                {
                    left = right = rightT = ParmType::INTEGER;
                    unaryErrors = true;
                }
  
                if(i >= 9 && i <= 12)
                {
                    left = right = ParmType::CHARINT;; 
                    rightT = ParmType::BOOL;
                }

                if(i >= 13 && i <=14)
                {
                    left = right = ParmType::UNDEFINED;
                    rightT = ParmType::BOOL;
                }

                if(i == 15)
                {
                    left = right = ParmType::UNDEFINED;
                    rightT = ParmType::BOOL;
                }

                if(i >= 16)
                {
                    left = right = rightT = ParmType::BOOL;
                    unaryErrors = true;
                }

            }
        }
    }

}


std::string ConvertParmToString(ParmType type)
{
    switch(type)
    {
       
        case ParmType::VOID:
        {
            return "void";
        }
        break;

        case ParmType::INTEGER:
        {
            return "int";
        }
        break;

        case ParmType::BOOL:
        {
            return "bool";
        }
        break;

        case ParmType::CHAR:
        {
            return "char";
        }
        break;

        case ParmType::CHARINT:
        {
            return "CharInt";
        }
        break;

        case ParmType::EQUAL:
        {
            return "Equal";
        }

        case ParmType::UNDEFINED:
        {
            return "undefined type";
        }
        break; 

        default:
        {
            return "ParmType not found\n";
        }
        break; 
    }
}


void getReturnType(std::string op, bool isBinary, ParmType &rightT)
{

    std::string unaryOps[6] = {"not", "*", "?", "-", "--", "++"};

    std::string binaryOps[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", "!<", "!>", "==", "!=", "=", "and", "or"};

    if(!isBinary)
    {

        for(int i = 0; i < 6; i++)
        {

            if(op == unaryOps[i])
            {

                if(i == 0)
                {
                    rightT = ParmType::BOOL;
                }
                
                if(i == 1)
                {
                    
                    rightT = ParmType::INTEGER;
                }

                if(i >= 2)
                {
                    rightT = ParmType::INTEGER;
                }
            }
        }
    }
    else
    {

        for(int i = 0; i < 18; i++)
        {

            if(op == binaryOps[i])
            {

                if(i >= 0 && i <= 8)
                {
                    rightT = ParmType::INTEGER;
                }

                if(i >= 9 && i <= 12)
                {
                    rightT = ParmType::BOOL;
                }

                if(i >= 13 && i <=14)
                {
                    rightT = ParmType::BOOL;
                }

                if(i == 15)
                {
                    rightT = ParmType::BOOL;
                }

                if(i >= 16)
                {
                    rightT = ParmType::BOOL;
                }

            }
        }
    }

}


void analyzeNestedOperators(Node* node, Node* child)
{

    if(child->m_childernNodes[0] != nullptr && child->m_childernNodes[1] != nullptr)
    {

        if(child->m_childernNodes[0]->nodeSubType.expression == ExpressionType::OP)
        {

            analyzeNestedOperators(node, child->m_childernNodes[0]);
        }

        if(child->m_childernNodes[1]->nodeSubType.expression == ExpressionType::OP)
        {
            analyzeNestedOperators(node, child->m_childernNodes[1]);
        }

        else if(child->m_childernNodes[0]->nodeSubType.expression == ExpressionType::IDENTIFIER || child->m_childernNodes[1]->nodeSubType.expression == ExpressionType::IDENTIFIER)
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Initializer for variable " + node->nodeAttributes.name + "is not a constant expression.");
            //printError(32, node->m_lineNumber, 0, node->nodenodeAttributesibutes.name, nullptr, nullptr, 0);
        }
    }

    else if(child->m_childernNodes[0] != nullptr && child->m_childernNodes[1] == nullptr)
    {
  
        if(child->nodeAttributes.name == "not")
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Initializer for variable " + node->nodeAttributes.name + "is not a constant expression.");
            //printError(32, node->m_lineNumber, 0, node->nodenodeAttributesibutes.name, nullptr, nullptr, 0);
        }
    }
}

void analyzeNestedAssign(Node* child)
{
    if(child->m_childernNodes[0] != nullptr)
    {
        child->m_childernNodes[0]->m_isInitialized = true;
    }
}
//Node *funcFound, Node *t, TreeNode *ffParm, TreeNode *tParm, int paramCount
//Node *funcFound, Node* node, Node* funcParm, Node* nodeParm, int paramCount
void parameterErrors(Node* funcFound, Node* node, Node* funcParm, Node* nodeParm, int paramCount)
{
    

    if(funcParm->m_siblingNode == nullptr && nodeParm->m_siblingNode != nullptr)
    {
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Too many parameters passed for function '" + funcFound->nodeAttributes.name + "' declared on line " + std::to_string(funcFound->m_lineNumber) + ".");
        //printError(38, t->m_lineNumber, funcFound->m_lineNumber, node->nodeAttributes.name, nullptr, NULL, 0);
    }

    else if(funcParm->m_siblingNode != nullptr && nodeParm->m_siblingNode == nullptr)
    {
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Too few parameters passed for function '" + funcFound->nodeAttributes.name + "' declared on line " + std::to_string(funcFound->m_lineNumber) + ".");
        //printError(37, t->m_lineNumber, funcFound->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
    }
  
    if(nodeParm->m_parmType != ParmType::UNDEFINED)
    {
        
        if(funcParm->m_parmType != nodeParm->m_parmType && !nodeParm->m_isDeclError && !funcFound->m_isIO)
        {
            //msg << "Expecting type " << Data::typeToString(funcParmType) << " in parameter " << parmCount << " of call to '" << func->getName() << "' declared on line " << func->getLineNum() <<" but got type " << Data::typeToString(callParmType) << ".";
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting type " + funcFound->nodeAttributes.name + " in parameter " +  std::to_string(paramCount) + ConvertParmToString(funcParm->m_parmType) + " of call to '" + ConvertParmToString(nodeParm->m_parmType) + "' declared on line" + std::to_string(node->m_lineNumber) + "but got type" + ConvertParmToString(nodeParm->m_parmType) + ".");
            //printError(25, t->m_lineNumber, funcFound->m_lineNumber, funcFound->nodeAttributes.name, ExpTypetwo(funcParm->expType), ExpTypetwo(nodeParm->expType), paramCount);

            if(!funcParm->m_isArray && nodeParm->m_isArray)
            {
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Not expecting array in parameter " + std::to_string(paramCount) + " of call to '" + ConvertParmToString(funcParm->m_parmType) + "' declared on line" + std::to_string(node->m_lineNumber) + ".");
                //printError(36, t->m_lineNumber, funcFound->m_lineNumber, funcFound->nodeAttributes.name, NULL, NULL, paramCount);
            }
 
            else if(funcParm->m_isArray && !nodeParm->m_isArray)
            {
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting array in parameter " + std::to_string(paramCount) + " of call to '" + ConvertParmToString(funcParm->m_parmType) + "' declared on line" + std::to_string(node->m_lineNumber) + ".");
                //printError(28, t->m_lineNumber, funcFound->m_lineNumber, funcFound->nodeAttributes.name, NULL, NULL, paramCount);
            }
        }
   
        else if(!funcParm->m_isArray && nodeParm->m_isArray)
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Not expecting array in parameter " + std::to_string(paramCount) + " of call to '" + ConvertParmToString(funcParm->m_parmType) + "' declared on line" + std::to_string(node->m_lineNumber) + ".");
            //printError(36, t->m_lineNumber, funcFound->m_lineNumber, funcFound->nodeAttributes.name, NULL, NULL, paramCount);
        }
       
        else if(funcParm->m_isArray && !nodeParm->m_isArray)
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting array in parameter " + std::to_string(paramCount) + " of call to '" + ConvertParmToString(funcParm->m_parmType) + "' declared on line" + std::to_string(node->m_lineNumber) + ".");
            //printError(28, t->m_lineNumber, funcFound->m_lineNumber, funcFound->nodeAttributes.name, NULL, NULL, paramCount);
        }
       
    }

    paramCount++;

    if(funcParm->m_siblingNode != nullptr && nodeParm->m_siblingNode != nullptr)
    {
        parameterErrors(funcFound, node, funcParm->m_siblingNode, nodeParm->m_siblingNode, paramCount);
    }

}
