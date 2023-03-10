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

#include "IOinit.hpp"
#include "symbolTable.hpp"
#include "AST.hpp"
#include "scanType.hpp"
#include "Semantics.hpp"
#include <string>

extern SymbolTable symbolTable;

void setupIO()
{


    Node* IONode; 
    Node* ParamNode;


   std::string IONameArr[] = {"output", "outputb", "outputc", "input", "inputb", "inputc", "outnl"};

   ParmType expTypeIO[] = {ParmType::VOID, ParmType::VOID, ParmType::VOID, ParmType::INTEGER, ParmType::BOOL, ParmType::CHAR, ParmType::VOID};
   ParmType parmTypeIO[] = {ParmType::INTEGER, ParmType::BOOL, ParmType::CHAR, ParmType::VOID, ParmType::VOID, ParmType::VOID, ParmType::VOID};



   for(int i = 0; i < 7; i++)
   {

       IONode = newDeclNodeIO(FUNCTION);
       IONode->nodeAttributes.name = IONameArr[i];
       IONode->m_lineNumber = -1;
       IONode->m_parmType = expTypeIO[i];


       IONode->m_isDeclared = true;
       IONode->m_isInitialized = true;
       IONode->m_isUsed = true;
       IONode->m_isIO = true;

       symbolTable.insert(IONode->nodeAttributes.name, (Node *) IONode);


       if(parmTypeIO[i] != VOID)
       {
           ParamNode = newDeclNodeIO(DeclarationType:: PARAMETER);
           ParamNode->nodeAttributes.name = "dummy";
           ParamNode->m_lineNumber = -1;
           ParamNode->m_parmType - parmTypeIO[i];
           IONode->m_childernNodes[0] = ParamNode;
       }
       else
       {
           IONode->m_childernNodes[0] = nullptr;
       }
   }
   

}

