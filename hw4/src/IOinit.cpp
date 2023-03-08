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

#include <stdio.h>
#include <string>
#include <iostream>

extern SymbolTable symbolTable;

void setupIO()
{

    //vars for IO nodes and dummy parameters
    Node* newIONode; 
    Node* dummyParam;

    //each node to set up
    /*
    void output(int)
    void outputb(bool)
    void outputc(char)
    int input()
    bool inputb()
    char inputc()
    void outnl()
    */

   //set up each section of new nodes as arrays
   std::string IONameArr[] = {"output", "outputb", "outputc", "input", "inputb", "inputc", "outnl"};

   ParmType IOexpType[] = {ParmType::VOID, ParmType::VOID, ParmType::VOID, ParmType::INTEGER, ParmType::BOOL, ParmType::CHAR, ParmType::VOID};
   ParmType IOParamExpType[] = {ParmType::INTEGER, ParmType::BOOL, ParmType::CHAR, ParmType::VOID, ParmType::VOID, ParmType::VOID, ParmType::VOID};

   //set up nodes

   for(int i = 0; i < 7; i++)
   {

       newIONode = newDeclNodeIO(); 
       newIONode->nodeAttributes.name= IONameArr[i];
       newIONode->m_lineNumber = -1;
       newIONode->m_parmType = IOexpType[i];

       //avoid warnings
       newIONode->m_isDeclared = true;
       newIONode->m_isInitialized = true;
       newIONode->m_isUsed = true;
       newIONode->m_isIO = true;

       //insert into symbolTable
       symbolTable.insert(newIONode->nodeAttributes.name, (Node *) newIONode);


       //set up parameters if not void
       if(IOParamExpType[i] != VOID)
       {
           dummyParam = newDeclNodeIO(PARAMETER);
           dummyParam->nodeAttributes.name = strdup("dummy");
           dummyParam->m_lineNumber = -1;
           dummyParam->m_parmType - IOParamExpType[i];
           newIONode->m_childernNodes[0] = dummyParam;
       }
       else
       {
           newIONode->m_childernNodes[0] = nullptr;
       }
   }
   

}

