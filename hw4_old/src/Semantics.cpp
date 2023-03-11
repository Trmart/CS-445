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
        case T_DECLARATION:
                    {
                        analyzeDecl(node, nErrors, nWarnings);
                    }
                    break;

        case T_STATEMENT:
                    {
                        analyzeStmt(node, nErrors, nWarnings);
                    }
                    break;

        case T_EXPRESSION:
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
        if(mainCheck->m_nodeType == NodeType::T_DECLARATION && mainCheck->nodeSubType.declaration != DeclarationType::T_FUNCTION)
        {
            EmitDiagnostics::Error::emitLinkerError("A function named 'main' with no parameters must be defined.");
            //printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
        else if(mainCheck->m_childernNodes[0] != nullptr && mainCheck->m_childernNodes[0]->nodeSubType.declaration == DeclarationType::T_PARAMETER)
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

        if(node->nodeSubType.declaration == DeclarationType::T_PARAMETER && !node->m_isUsedError && node->nodeAttributes.name == "main")
        {
            node->m_isUsedError = true;
            EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber,"The parameter '" + node->nodeAttributes.name + "' seems not to be used.");
            //printError(21, node->m_lineNumber, 0, node->nodeAttributes.name, NULL, NULL, 0);
        }

        else if(node->nodeSubType.declaration == DeclarationType::T_FUNCTION && !node->m_isUsedError && node->nodeAttributes.name == "main")
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

    else if(!node->m_isUsed && node->m_isGlobal && node->nodeSubType.declaration == DeclarationType::T_FUNCTION)
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


   if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
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
        if(node->m_childernNodes[1]->m_parmType != ParmType::T_INTEGER && node->m_childernNodes[1]->m_parmType != ParmType::T_UNDEFINED)
        {

            if(node->m_childernNodes[1]->nodeSubType.declaration == DeclarationType::T_PARAMETER && node->m_childernNodes[1]->nodeSubType.expression != ExpressionType::T_CALL && node->m_childernNodes[1]->m_parmType == ParmType::T_VOID)
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
   if(node->m_childernNodes[1] != nullptr && node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
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
    
    if(node->nodeSubType.declaration != DeclarationType::T_VARIABLE && !symbolTable.insert(node->nodeAttributes.name, node))
    {
        declared = (Node* )symbolTable.lookup(node->nodeAttributes.name);
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Symbol '" + node->nodeAttributes.name +  "' is already declared at line " + std::to_string(declared->m_lineNumber) + ".");
        // printError(0, t->m_lineNumber, declared->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
    }

    switch(node->nodeSubType.declaration)
    {
        
        case DeclarationType::T_VARIABLE:
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
               if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER || node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_CALL)
               {
                //    printError(32, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' is not a constant expression.");
               }

               else if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_OP)
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

                    if(node->m_parmType == ParmType::T_CHAR && node->m_childernNodes[0]->m_parmType == ParmType::T_CHARINT)
                    {
                        ; // do nothing
                    }

                    else if(node->m_parmType == ParmType::T_INTEGER && node->m_childernNodes[0]->m_parmType == ParmType::T_CHARINT)
                    {
                        char charInsert[] = "char";
                        // Initializer for variable '%s' of type %s is of type %s
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Initializer for variable '" + node->nodeAttributes.name + "' of type " + ConvertParmToString(node->m_parmType) + " is of type char.");
                        //printError(33, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(t->expType), charInsert, 0);
                    }

                    else if(node->m_childernNodes[0]->m_parmType == ParmType::T_VOID && node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
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

        case DeclarationType::T_FUNCTION:
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

                                        if(Flag == false && node->m_parmType != ParmType::T_VOID)
                                        {
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Expecting to return type " + ConvertParmToString(node->m_parmType) + " but function '" + node->nodeAttributes.name + "' has no return statement.");
                                            //printError(19, node->m_lineNumber, 0, ExpTypetwo(functionReturnType), node->nodeAttributes.name, NULL, 0);
                                        }

                                        symbolTable.applyToAll(analyzeWarnings);
                                        symbolTable.leave();
                                        curFunc = nullptr;
                                    }
                                    break;

        case DeclarationType::T_PARAMETER:
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


void analyzeStmt(Node* node, int& nErrors, int& nWarnings)
{

    switch(node->nodeSubType.statement)
    {
        case StatementType::T_IF:
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


            if(node->m_childernNodes[0]->m_parmType != ParmType::T_BOOL && node->m_childernNodes[0]->nodeSubType.expression != ExpressionType::T_OP && !node->m_childernNodes[0]->m_isDeclError)
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

        case StatementType::T_FOR:
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

        case StatementType::T_WHILE:
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
                        if(node->m_childernNodes[0]->m_parmType != ParmType::T_BOOL && node->m_childernNodes[0]->nodeSubType.expression != ExpressionType::T_OP && !node->m_childernNodes[0]->m_isDeclError)
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

        case StatementType::T_RETURN:
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
            
                if(functionReturnType == ParmType::T_VOID)
                {
                    //Function '%s' at line %d is expecting no return value, but return has a value.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting no return value, but return has a value.");
                    // printError(29, returnm_lineNumber, functionLine, functionName, NULL, NULL, 0);
                }

                else if(functionReturnType != actualReturnType && actualReturnType != ParmType::T_VOID && functionReturnType != ParmType::T_VOID)
                {

                    if(!(functionReturnType == ParmType::T_CHAR && actualReturnType == ParmType::T_CHARINT))
                    {
                        //Function '%s' at line %d is expecting to return type %s but returns type %s.
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting to return type " + ConvertParmToString(functionReturnType) + " but returns type " + ConvertParmToString(actualReturnType) + ".");
                        // printError(31, returnm_lineNumber, functionLine, functionName, ExpTypetwo(functionReturnType), ExpTypetwo(actualReturnType), 0);
                    }
                }

                else if(functionReturnType != actualReturnType && functionReturnType != ParmType::T_VOID && node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_CALL)
                {
                    
                    if(!(functionReturnType == ParmType::T_CHAR && actualReturnType == ParmType::T_CHARINT))
                    {
                        //Function '%s' at line %d is expecting to return type %s but returns type %s.
                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting to return type " + ConvertParmToString(functionReturnType) + " but returns type " + ConvertParmToString(actualReturnType) + ".");
                        // printError(31, returnm_lineNumber, functionLine, functionName, ExpTypetwo(functionReturnType), ExpTypetwo(actualReturnType), 0);
                    }
                }
            }

            else if(node->m_childernNodes[0] == nullptr)
            {

                if(functionReturnType != ParmType::T_VOID)
                {
                    //Function '%s' at line %d is expecting to return type %s but return has no value.
                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Function '" + curFunc->nodeAttributes.name + "' at line " + std::to_string(functionLine) + " is expecting to return type " + ConvertParmToString(functionReturnType) + " but return has no value.");
                    // printError(30, returnm_lineNumber, functionLine, functionName, ExpTypetwo(functionReturnType), NULL, 0);
                }
            }

        }
        break;

        case StatementType::T_BREAK:
        {
            if(!loop)
            {
                //Cannot have a break statement outside of loop.
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber , " Cannot have a break statement outside of loop.");
                // printError(22, node->m_lineNumber, 0, NULL, NULL, NULL, 0);
            }

        }
        break;


        case StatementType::T_RANGE:
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
                            if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
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

        case StatementType::T_COMPOUND:
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

//function analyzes expression nodes. 
void analyzeExp(Node* node, int& nErrors, int& nWarnings)
{
 
    bool leftStr, rightStr, isBinary, leftArr, rightArr, leftIndx, rightIndx, leftInit, leftDecl, rightInit, rightDecl, throwError;
    leftStr = rightStr = isBinary = leftArr = rightArr = leftIndx = rightIndx = leftInit = leftDecl = rightInit = rightDecl = throwError = false;

    ParmType leftSide, rightSide, returnType, leftExpected, rightExpected, childReturnType;
    leftSide = rightSide = returnType = leftExpected = rightExpected = childReturnType = ParmType::T_UNDEFINED;

    bool rightErr, leftErr, unaryErrors;
    rightErr = leftErr = unaryErrors = false;

    Node* valFound = nullptr;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;

    switch(node->nodeSubType.expression) 
    {
        case ExpressionType::T_ASSIGN:
        case ExpressionType::T_OP:
                    {
                        if(node->nodeAttributes.name != "<=")
                        {

                            if(node->m_childernNodes[0] != nullptr)
                            {
                                
                                if(node->m_childernNodes[0]->m_childernNodes[0]!= nullptr  && node->m_childernNodes[0]->nodeAttributes.name != "[")
                                {
                                    node->m_childernNodes[0]->m_childernNodes[0]->m_isInitialized = true;

                                    if(node->m_childernNodes[0]->m_childernNodes[1] != nullptr)
                                    {
                                        node->m_childernNodes[0]->m_childernNodes[1]->m_isInitialized = true;

                                        if(node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[0] != nullptr && node->m_childernNodes[0]->m_childernNodes[1]->m_childernNodes[1] != nullptr)
                                        {

                                            if(node->m_childernNodes[0]->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_OP)
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

                                else if(node->m_childernNodes[1] != nullptr && node->m_childernNodes[1]->m_parmType == ParmType::T_VOID)
                                {

                                    if(node->m_childernNodes[1]->nodeAttributes.name != "<=")
                                    {
                                        node->m_childernNodes[0]->m_isInitialized = true;
                                    }

                                    if(node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_CALL)
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
                
                                        if(node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER && !node->m_childernNodes[0]->m_isInitialized)
                                        {
                    
                                            if(node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
                                            {

                                                // char* lhs = strdup(node->m_childernNodes[0]->nodeAttributes.name);
                                                std::string lhs = node->m_childernNodes[0]->nodeAttributes.name;
                                                std::string rhs = node->m_childernNodes[1]->nodeAttributes.name;

                                                if(lhs == rhs)
                                                {
                                                    node->m_childernNodes[0]->m_isInitialized = true;
                                                }
                                            }

                                            else if(node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_ASSIGN)
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
                
                                        if(node->m_childernNodes[1]->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
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

                            if(leftNode->m_childernNodes[0] != nullptr)
                            {
                                leftArr = false; 
                                leftIndx = true; 
                            }
                        if(leftNode->m_nodeType == NodeType::T_EXPRESSION)
                            {
                                if(leftNode->nodeSubType.expression == ExpressionType::T_CALL)
                                {
                                    leftArr = false;
                                }
                                if(leftNode->nodeSubType.expression == ExpressionType::T_CONSTANT)
                                {
                                    leftStr = true;
                                }
                            }
                        }

                        if(node->m_childernNodes[1] != nullptr)
                        {
                            rightNode = node->m_childernNodes[1];
                            rightSide = rightNode->m_parmType;
                            rightArr = rightNode->m_isArray;
                            

                            if(rightNode->m_childernNodes[0] != nullptr)
                            {
                                rightArr = false; 
                                rightIndx = true; 
                            }
                            if(rightNode->m_nodeType == NodeType::T_EXPRESSION)
                            {
                                if(rightNode->nodeSubType.expression == ExpressionType::T_CALL)
                                {
                                    rightArr = false;
                                }
                                if(rightNode->nodeSubType.expression == ExpressionType::T_CONSTANT)
                                {
                                    rightStr = true;
                                }
                            }
                            isBinary = true;
                        }

                        getExpTypes(node->nodeAttributes.name, isBinary, unaryErrors, leftExpected, rightExpected, returnType);

                        if(leftSide == ParmType::T_VOID && !(leftNode->m_nodeType == NodeType::T_EXPRESSION && leftNode->nodeSubType.expression == ExpressionType::T_CALL))
                        {
                            leftErr = true;
                        }
                        if(rightSide == ParmType::T_VOID && !(rightNode->m_nodeType == NodeType::T_EXPRESSION && rightNode->nodeSubType.expression == ExpressionType::T_CALL))
                        {
                            rightErr = true;
                        }

                        if(!isBinary && !leftErr)
                        {
            
                            if(leftSide != leftExpected && leftExpected != ParmType::T_UNDEFINED)
                            {

                                if(node->nodeAttributes.name != "-")
                                {
                                    // char uMinus[] = "chsign";
                                    //Unary '%s' requires an operand of type %s but was given type %s.
                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Unary '" + node->nodeAttributes.name + "' requires an operand of type " + ConvertParmToString(leftExpected) + " but was given type " + ConvertParmToString(leftSide) + ".");
                                    // printError(9, t->m_lineNumber, 0, uMinus, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                }

                                else
                                {
                                    //Unary '%s' requires an operand of type %s but was given type %s.
                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Unary '" + node->nodeAttributes.name + "' requires an operand of type " + ConvertParmToString(leftExpected) + " but was given type " + ConvertParmToString(leftSide) + ".");
                                    // printError(9, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                }
                            }

                            else if(node->nodeAttributes.name != "not" && leftSide != leftExpected)
                            {
                                //Unary '%s' requires an operand of type %s but was given type %s.
                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Unary '" + node->nodeAttributes.name + "' requires an operand of type " + ConvertParmToString(leftExpected) + " but was given type " + ConvertParmToString(leftSide) + ".");
                                // printError(9, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                            }

                            else if(node->nodeAttributes.name != "*" && (!leftArr && leftSide != ParmType::T_UNDEFINED))
                            {
                                // char uSizeof[] = "sizeof";
                                //The operation '%s' only works with arrays.\n"
                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "The operation '" + node->nodeAttributes.name + "' only works with arrays.");
                                // printError(8, t->m_lineNumber, 0, uSizeof, NULL, NULL, 0);
                            } 

                            if(leftArr)
                            {
                                if(node->nodeAttributes.name == "*")
                                {

                                    if(node->nodeAttributes.name != "-")
                                    {
                                        // char uMinus[] = "chsign";
                                        //The operation '%s' does not work with arrays.
                                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "The operation '" + node->nodeAttributes.name + "' does not work with arrays.");
                                        // printError(7, t->m_lineNumber, 0, uMinus, NULL, NULL, 0);
                                    }
                                    else
                                    {
                                        //The operation '%s' does not work with arrays.
                                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "The operation '" + node->nodeAttributes.name + "' does not work with arrays.");
                                        // printError(7, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                    }
                                }
                            }
                        }
                            else
                            {
                                if(!unaryErrors)
                                {

                                    if(node->nodeAttributes.name != "[")
                                    {
                                        printArrayErrors(node);
                                    }
                            
                                    else if(leftSide != rightSide && !leftErr && !rightErr)
                                    {

                                        if(ConvertParmToString(leftSide) != "int" && ConvertParmToString(rightSide) != "CharInt")
                                        {
                                            // char diffCharInt[] = "char";
                                            //'%s' requires operands of the same type but lhs is type %s and rhs is type %s.
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of the same type but lhs is type " + ConvertParmToString(leftSide) + " and rhs is type char.");
                                            //  printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), diffCharInt, 0);
                                        }
                                        else if(ConvertParmToString(leftSide) != "char" && ConvertParmToString(rightSide) != "CharInt")
                                        {
                                            //do nothing
                                        }
            
                                        else if(node->nodeAttributes.name != "<=" && node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_OP)
                                        {
            
                                            getReturnType(node->m_childernNodes[1]->nodeAttributes.name, isBinary, childReturnType);
                                        
                                            if(childReturnType != node->m_childernNodes[0]->m_parmType)
                                            {
                                                //'%s' requires operands of the same type but lhs is type %s and rhs is type %s.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of the same type but lhs is type " + ConvertParmToString(leftSide) + " and rhs is type " + ConvertParmToString(rightSide) + ".");
                                                // printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), ExpTypetwo(childReturnType), 0);
                                            }

                                            else if(node->m_childernNodes[1]->m_childernNodes[1] != nullptr && node->m_childernNodes[1]->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_CALL)
                                            {
                                                //'%s' requires operands of the same type but lhs is type %s and rhs is type %s.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of the same type but lhs is type " + ConvertParmToString(leftSide) + " and rhs is type " + ConvertParmToString(rightSide) + ".");
                                                // printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), ExpTypetwo(childReturnType), 0);
                                            }
                                        }
                                        else
                                        {

                                            if(node->m_childernNodes[0]->nodeSubType.expression != ExpressionType::T_CALL)
                                            {
                                                //'%s' requires operands of the same type but lhs is type %s and rhs is type %s.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of the same type but lhs is type " + ConvertParmToString(leftSide) + " and rhs is type " + ConvertParmToString(rightSide) + ".");
                                                //  printError(2, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftSide), ExpTypetwo(rightSide), 0);
                                            }
                                            else
                                            {
                                                //do nothing
                                            }
                                        }
                                    }
                                }


                                if(!(leftExpected == ParmType::T_UNDEFINED || rightExpected == ParmType::T_UNDEFINED))
                                {
                                    
                                    if(leftExpected == ParmType::T_CHARINT || rightExpected == ParmType::T_CHARINT)
                                    {
                                        // do nothing
                                    }

                                    else if(leftSide == rightSide && leftNode->nodeSubType.expression == ExpressionType::T_CALL && rightNode->nodeSubType.expression == ExpressionType::T_CALL)
                                    {

                                        Node* lhs = (Node*)symbolTable.lookup(node->m_childernNodes[0]->nodeAttributes.name);
                                        Node* rhs = (Node*)symbolTable.lookup(node->m_childernNodes[1]->nodeAttributes.name);

                                        if(lhs != nullptr && rhs != nullptr)
                                        {

                                            if(lhs->nodeSubType.declaration == DeclarationType::T_FUNCTION && rhs->nodeSubType.declaration == DeclarationType::T_FUNCTION && !lhs->m_isIO && !rhs->m_isIO)
                                            {
                                                if(node->m_childernNodes[0]->m_parmType == ParmType::T_VOID && node->m_childernNodes[1]->m_parmType == ParmType::T_VOID)
                                                {
                                                    //'%s' requires operands of type %s but lhs is of type %s.
                                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of type " + ConvertParmToString(leftExpected) + " but lhs is of type " + ConvertParmToString(leftSide) + ".");
                                                    //  printError(3, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                                    //'%s' requires operands of type %s but rhs is of type %s.
                                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of type " + ConvertParmToString(rightExpected) + " but rhs is of type " + ConvertParmToString(rightSide) + ".");
                                                    //  printError(4, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                                }
                                                
                                            }

                                        }
                                    }
                                    else
                                    {

                                        if(leftSide != leftExpected && !leftErr)
                                        {
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of type " + ConvertParmToString(leftExpected) + " but lhs is of type " + ConvertParmToString(leftSide) + ".");
                                            //  printError(3, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                            // printError(3, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                        }

                                        if(rightSide != rightExpected && !rightErr && rightSide != ParmType::T_UNDEFINED)
                                        {

                                            if(rightSide == ParmType::T_UNDEFINED && node->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_CALL && returnType != ParmType::T_BOOL)
                                            {
                                                //'%s' requires operands of type %s but rhs is of type %s.
                                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of type " + ConvertParmToString(rightExpected) + " but rhs is of type " + ConvertParmToString(rightSide) + ".");
                                                // printError(4, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                            }
                                            else if(rightSide != ParmType::T_UNDEFINED)
                                            {
                                                //'%s' requires operands of type %s but rhs is of type %s.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires operands of type " + ConvertParmToString(rightExpected) + " but rhs is of type " + ConvertParmToString(rightSide) + ".");
                                                // printError(4, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                            }
                                        }
                                    }
                                }

                                if(leftArr || rightArr)
                                {

                                    if(node->nodeAttributes.name == "<=" && leftExpected != ParmType::T_UNDEFINED)
                                    {
                                        if((node->nodeAttributes.name != "<") || (node->nodeAttributes.name != ">") || (node->nodeAttributes.name != "=") || (node->nodeAttributes.name != "!>") || (node->nodeAttributes.name != "!<") || (node->nodeAttributes.name != "><"))
                                        {
                                    
                                            if(leftArr && !rightArr)
                                            {
                                                //'%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires both operands be arrays or not but lhs is an array and rhs is not an array.");
                                                // printError(5, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                            }

                                            else if(!leftArr && rightArr)
                                            {
                                                //'%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires both operands be arrays or not but lhs is not an array and rhs is an array.");
                                                // printError(6, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                            }
                                        }

                                        else
                                        {
                                            //The operation '%s' does not work with arrays.
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "The operation '" + node->nodeAttributes.name + "' does not work with arrays.");
                                            // printError(7, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                        }
                                    }
                                    
                                    else{
                                        if(node->nodeAttributes.name != "[")
                                        {
                                            //dp nothing
                                        }

                                        else if((leftArr && !rightArr) || (!leftArr && rightArr))
                                        {

                                            if(leftArr && !rightArr)
                                            {
                                                //'%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires both operands be arrays or not but lhs is an array and rhs is not an array.");
                                                // printError(5, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                            }

                                            else if(!leftArr && rightArr)
                                            {
                                                //'%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' requires both operands be arrays or not but lhs is not an array and rhs is an array.");
                                                // printError(6, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                            }
                                        }
                                    }
                                }
                            }

                        if(returnType != ParmType::T_UNDEFINED)
                        {
                            node->m_parmType = returnType;
                        }
                        else
                        {
                            node->m_parmType = leftSide;
                        }
                    }
                    break; 
        case ExpressionType::T_CONSTANT:
                                {
                                    for(int i = 0; i < MAXCHILDREN; i++)
                                    {
                                        analyze(node->m_childernNodes[i], nErrors, nWarnings);
                                    }
                            
                                    if(range)
                                    {
                                        if(inFor)
                                        {
                                            if(node->m_parmType != ParmType::T_INTEGER)
                                            {
                                                // char intExpect[] = "int";
                                                //Expecting type %s in position %d in range of for statement but got type %s.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting type int in position " + std::to_string(rangePos) + " in range of for statement but got type " + ConvertParmToString(node->m_parmType) + ".");
                                                // printError(26, t->m_lineNumber, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                                            }
                                        }
                                    }

                                }
                                break;

        case ExpressionType::T_IDENTIFIER:
                                    {
                                        valFound = (Node*)symbolTable.lookup(node->nodeAttributes.name);

                                        if(valFound == nullptr )
                                        {

                                            if(range && rangePos == 1)
                                            {
                                                node->m_isDeclared = true;
                                            }

                                            else
                                            {
                                                //Symbol '%s' is not declared.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Symbol '" + node->nodeAttributes.name + "' is not declared.");
                                                // printError(1, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0); 
                                                node->m_isDeclError = true;    
                                            }           
                                        }

                                        else if(range)
                                        {

                                            if(inFor)
                                            {

                                                node->m_parmType = valFound->m_parmType;
                                                node->m_isArray = valFound->m_isArray;

                                                if(node->m_parmType != ParmType::T_INTEGER && rangePos >= 1)
                                                {
                                                    if(!sizeOfArrayFlg)
                                                    {

                                                        if(node->nodeAttributes.name != "main")
                                                        {
                                                            //Cannot use function '%s' as a variable.
                                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Cannot use function '" + node->nodeAttributes.name + "' as a variable.");
                                                            // printError(12, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);  
                                                        }
                                                        else
                                                        {
                                                            // char intExpect[] = "int";
                                                            //Expecting type %s in position %d in range of for statement but got type %s.
                                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting type int in position " + std::to_string(rangePos) + " in range of for statement but got type " + ConvertParmToString(node->m_parmType) + ".");
                                                            // printError(26, t->m_lineNumber, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                                                        }
                                                    }

                                                }

                                                if(rangePos >= 1 && !valFound->m_isInitialized)
                                                {
                                                    if(valFound->m_isDeclared == true)
                                                    {

                                                        if(!valFound->m_isInitialized && !valFound->m_isWarningReported && !valFound->m_isStatic && !valFound->m_isGlobal)
                                                        {

                                                            if(!node->m_isInitialized)
                                                            {
                                                                valFound->m_isWarningReported = true;
                                                                valFound->m_isUsed = true;
                                                                //Variable '%s' may be uninitialized when used here.
                                                                EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber, "Variable '" + node->nodeAttributes.name + "' may be uninitialized when used here.");
                                                                // printError(18, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                                            }
                                                            
                                                            else
                                                            {
                                                                valFound->m_isInitialized = true;
                                                            }
                                                        }
                                                
                                                    }
                                                }

                                                else if(rangePos > 1 && valFound->m_isInitialized)
                                                {
                                                    valFound->m_isUsed = true;
                                                }

                                                if(valFound->m_isArray && !sizeOfArrayFlg && !node->m_isIndexed)
                                                {
                                                    //Cannot use array in position %d in range of for statement.
                                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Cannot use array in position " + std::to_string(rangePos) + " in range of for statement.");
                                                    // printError(24, t->m_lineNumber, 0, NULL, NULL, NULL, rangePos);
                                                }

                                                node->m_isIndexed = false;

                                            }

                                            node->m_isInitialized = true;
                                        }

                                        else
                                        {

                                            if(valFound->m_isDeclared == true)
                                            {
                                            
                                                if(!valFound->m_isInitialized && !valFound->m_isWarningReported && !valFound->m_isStatic && !valFound->m_isGlobal)
                                                {
                                                    if(!node->m_isInitialized)
                                                    {
                                                        valFound->m_isWarningReported = true;
                                                        //Variable '%s' may be uninitialized when used here.
                                                        EmitDiagnostics::Warning::emitGenericWarnings(node->m_lineNumber, "Variable '" + node->nodeAttributes.name + "' may be uninitialized when used here.");
                                                        // printError(18, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                                    }
                                                    else
                                                    {
                                                        valFound->m_isInitialized = true;
                                                    }
                                                }
                                            }

                                            if(valFound->nodeSubType.declaration == DeclarationType::T_FUNCTION)
                                            {
                                                //Cannot use function '%s' as a variable.
                                                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Cannot use function '" + node->nodeAttributes.name + "' as a variable.");
                                                // printError(12, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                                valFound->m_isUsed = true;
                                                break;
                                            }
                                            else
                                            {
                                                node->m_parmType = valFound->m_parmType;
                                                node->m_isArray = valFound->m_isArray;
                                                node->m_isGlobal = valFound->m_isGlobal;
                                                node->m_isStatic = valFound->m_isStatic;

                                                if(!range && valFound->nodeSubType.declaration != DeclarationType::T_FUNCTION)
                                                {
                                                    valFound->m_isUsed = true;
                                                }
                                            }

                                            if(node->m_childernNodes[0] != nullptr)
                                            {
                                                analyze(node->m_childernNodes[0], nErrors, nWarnings);

                                                if(node->m_childernNodes[0]->m_parmType == ParmType::T_VOID && !(node->m_childernNodes[0]->m_nodeType == NodeType::T_EXPRESSION && node->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_CALL))
                                                {
                                                    //do nothing and break out of logic block
                                                    break;
                                                }
                                                if(!node->m_isArray)
                                                {
                                                    //do nothing and break out of logic block
                                                    break;
                                                }
                                                else
                                                {

                                                    if(node->m_childernNodes[0]->m_parmType != ParmType::T_INTEGER)
                                                    {
                                                        //Array '%s' should be indexed by type int but got type %s.
                                                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Array '" + node->nodeAttributes.name + "' should be indexed by type " + ConvertParmToString(node->m_childernNodes[0]->m_parmType) + " but got type NULL.");
                                                        // printError(14, t->m_lineNumber, 0, t->nodeAttributes.name, ExpTypetwo(t->child[0]->expType), NULL, 0);
                                                    }
                            
                                                    if(node->m_childernNodes[0]->m_isArray && node->m_childernNodes[0]->m_childernNodes[0] == nullptr)
                                                    {
                                                        //Array index is the unindexed array '%s'.
                                                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Array index is the unindexed array '" + node->nodeAttributes.name + "'.");
                                                        // printError(13, t->m_lineNumber, 0, t->child[0]->nodeAttributes.name, NULL, NULL, 0);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    break;

        case ExpressionType::T_CALL:
                            {
                                int paramCount = 1;
                                Node* funcFound;

                                if(node->nodeSubType.expression == ExpressionType::T_CALL)
                                {
                                    funcFound = (Node* )symbolTable.lookup(node->nodeAttributes.name);
                                    
                                    if(funcFound == nullptr)
                                    {
                                        //Symbol '%s' is not declared.
                                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Symbol '" + node->nodeAttributes.name + "' is not declared.");
                                        // printError(1, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);  
                                        node->m_isDeclError = true; 
                                    }
                                    else
                                    {
                                        //do nothing
                                    }
                                }

                                for(int i = 0; i < MAXCHILDREN; i++)
                                {
                                    analyze(node->m_childernNodes[i], nErrors, nWarnings);
                                }

                                if(funcFound != nullptr)
                                {
                                    node->m_parmType = funcFound->m_parmType;
                                    node->m_isArray = funcFound->m_isArray;
                                    node->m_isGlobal = funcFound->m_isGlobal;
                                    node->m_isStatic = funcFound->m_isStatic;
                                    funcFound->m_isUsed = true;


                                    if(funcFound->nodeSubType.declaration != DeclarationType::T_FUNCTION)
                                    {
                                        //'%s' is a simple variable and cannot be called.
                                        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "'" + node->nodeAttributes.name + "' is a simple variable and cannot be called.");
                                        // printError(11, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);
                                    }
                                    

                                    else if(range)
                                    {

                                        if(inFor){

                                            if(node->m_parmType != ParmType::T_INTEGER)
                                            {

                                                if(node->nodeAttributes.name != "main")
                                                {
                                                    //Cannot use function '%s' as a variable.
                                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Cannot use function '" + node->nodeAttributes.name + "' as a variable.");
                                                    // printError(12, t->m_lineNumber, 0, t->nodeAttributes.name, NULL, NULL, 0);                               
                                                }
                                                else
                                                {
                                                    // char intExpect[] = "int";
                                                    //Expecting type %s in position %d in range of for statement but got type %s.
                                                    EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting type int in position " + std::to_string(paramCount) + " in range of for statement but got type " + ConvertParmToString(node->m_parmType) + ".");
                                                    // printError(26, t->m_lineNumber, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                                                }
                                            }
                                        }
                                    }

                                    else
                                    {

                                        if(funcFound->m_childernNodes[0] != nullptr && node->m_childernNodes[0] != nullptr)
                                        {
                                            parameterErrors(funcFound, node, funcFound->m_childernNodes[0], node->m_childernNodes[0], paramCount);
                                        }

                                        else if(funcFound->m_childernNodes[0] == nullptr && node->m_childernNodes[0] != nullptr)
                                        {
                                            //Too few parameters passed for function '%s' declared on line %d.
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Too few parameters passed for function '" + node->nodeAttributes.name + "' declared on line " + std::to_string(funcFound->m_lineNumber) + ".");
                                            // printError(38, t->m_lineNumber, funcFound->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
                                        }

                                        else if(funcFound->m_childernNodes[0] != nullptr && node->m_childernNodes[0] == nullptr)
                                        {
                                            //Too many parameters passed for function '%s' declared on line %d.
                                            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Too many parameters passed for function '" + node->nodeAttributes.name + "' declared on line " + std::to_string(funcFound->m_lineNumber) + ".");
                                            // printError(37, t->m_lineNumber, funcFound->m_lineNumber, t->nodeAttributes.name, NULL, NULL, 0);
                                        }
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
                    left = right = rightT = ParmType::T_BOOL;
                }

                if(i == 1)
                {
                    left = right = ParmType::T_UNDEFINED;
                    rightT = ParmType::T_INTEGER;
                }

                if(i >= 2)
                {
                    left = right = rightT = ParmType::T_INTEGER;
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
                    left = right = rightT = ParmType::T_INTEGER;
                    unaryErrors = true;
                }
  
                if(i >= 9 && i <= 12)
                {
                    left = right = ParmType::T_CHARINT;; 
                    rightT = ParmType::T_BOOL;
                }

                if(i >= 13 && i <=14)
                {
                    left = right = ParmType::T_UNDEFINED;
                    rightT = ParmType::T_BOOL;
                }

                if(i == 15)
                {
                    left = right = ParmType::T_UNDEFINED;
                    rightT = ParmType::T_BOOL;
                }

                if(i >= 16)
                {
                    left = right = rightT = ParmType::T_BOOL;
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
       
        case ParmType::T_VOID:
        {
            return "void";
        }
        break;

        case ParmType::T_INTEGER:
        {
            return "int";
        }
        break;

        case ParmType::T_BOOL:
        {
            return "bool";
        }
        break;

        case ParmType::T_CHAR:
        {
            return "char";
        }
        break;

        case ParmType::T_CHARINT:
        {
            return "CharInt";
        }
        break;

        case ParmType::T_EQUAL:
        {
            return "Equal";
        }

        case ParmType::T_UNDEFINED:
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
                    rightT = ParmType::T_BOOL;
                }
                
                if(i == 1)
                {
                    
                    rightT = ParmType::T_INTEGER;
                }

                if(i >= 2)
                {
                    rightT = ParmType::T_INTEGER;
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
                    rightT = ParmType::T_INTEGER;
                }

                if(i >= 9 && i <= 12)
                {
                    rightT = ParmType::T_BOOL;
                }

                if(i >= 13 && i <=14)
                {
                    rightT = ParmType::T_BOOL;
                }

                if(i == 15)
                {
                    rightT = ParmType::T_BOOL;
                }

                if(i >= 16)
                {
                    rightT = ParmType::T_BOOL;
                }

            }
        }
    }

}


void analyzeNestedOperators(Node* node, Node* child)
{

    if(child->m_childernNodes[0] != nullptr && child->m_childernNodes[1] != nullptr)
    {

        if(child->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_OP)
        {

            analyzeNestedOperators(node, child->m_childernNodes[0]);
        }

        if(child->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_OP)
        {
            analyzeNestedOperators(node, child->m_childernNodes[1]);
        }

        else if(child->m_childernNodes[0]->nodeSubType.expression == ExpressionType::T_IDENTIFIER || child->m_childernNodes[1]->nodeSubType.expression == ExpressionType::T_IDENTIFIER)
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
  
    if(nodeParm->m_parmType != ParmType::T_UNDEFINED)
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
