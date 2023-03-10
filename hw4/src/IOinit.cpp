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

#include "IOinit.h"


extern SymbolTable symbolTable;

void setupIO(){

    //vars for IO nodes and dummy parameters
    TreeNode* newIONode; 
    TreeNode* dummyParam;

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

   ExpType IOexpType[] = {Void, Void, Void, Integer, Boolean, Char, Void};
   ExpType IOParamExpType[] = {Integer, Boolean, Char, Void, Void, Void, Void};

   //set up nodes

   for(int i = 0; i < 7; i++){

       newIONode = newDeclNodeIO(FuncK);
       newIONode->attr.name = strdup(IONameArr[i].c_str());
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

