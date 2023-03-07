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
#include <string.h>
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

   Node::ReturnType IOexpType[] = {Node::ReturnType::VOID, Node::ReturnType::VOID, Node::ReturnType::VOID, Node::ReturnType::INTEGER, Node::ReturnType::BOOL, Node::ReturnType::CHAR, Node::ReturnType::VOID};
   Node::ReturnType IOParamExpType[] = {Node::ReturnType::INTEGER, Node::ReturnType::BOOL, Node::ReturnType::CHAR, Node::ReturnType::VOID, Node::ReturnType::VOID, Node::ReturnType::VOID, Node::ReturnType::VOID};

   //set up nodes

   for(int i = 0; i < 7; i++){

       newIONode = newDeclNodeIO(Node::DeclarationType::FUNCTION);
       newIONode->nodeAttributes.name = strdup(IONameArr[i].c_str());
       newIONode->lineno = -1;
       newIONode->expType = IOexpType[i];

       //avoid warnings
       newIONode->isDeclared = true;
       newIONode->isInit = true;
       newIONode->wasUsed = true;
       newIONode->isIO = true;

       //insert into symbolTable
       symbolTable.insert(newIONode->attr.name, (TreeNode*) newIONode);


       //set up parameters if not void
       if(IOParamExpType[i] != Void){
           dummyParam = newDeclNodeIO(ParamK);
           dummyParam->attr.name = strdup("dummy");
           dummyParam->lineno = -1;
           dummyParam->expType - IOParamExpType[i];
           newIONode->child[0] = dummyParam;
       }
       else{
           newIONode->child[0] = NULL;
       }
   }
   

}

