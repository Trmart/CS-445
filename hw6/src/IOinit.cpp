/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW6
Dr. Wilder
DUE: 4/16/2023

FILE: IOinit.cpp
DESC: Functions to setup IO functions
*/

#include "IOinit.h"


extern SymbolTable symbolTable;

void initializeIO()
{


    TreeNode* IONode; 
    TreeNode* dummyParam;

    std::string IONameArr[] = {"output", "outputb", "outputc", "input", "inputb", "inputc", "outnl"};

    ExpType IOexpType[] = {Void, Void, Void, Integer, Boolean, Char, Void};
    ExpType IOParamType[] = {Integer, Boolean, Char, Void, Void, Void, Void};


    for(int i = 0; i < 7; i++)
    {
        IONode = newDeclNodeIO(FuncK);
        IONode->attr.name = strdup(IONameArr[i].c_str());
        IONode->lineno = -1;
        IONode->expType = IOexpType[i];

        //avoid warnings
        IONode->isDeclared = true;
        IONode->isInit = true;
        IONode->wasUsed = true;
        IONode->isIO = true;

        //insert into symbolTable
        symbolTable.insert(IONode->attr.name, (TreeNode*) IONode);


        //set up parameters if not void
        if(IOParamType[i] != Void)
        {
            dummyParam = newDeclNodeIO(ParamK);
            dummyParam->attr.name = strdup("dummy");
            dummyParam->lineno = -1;
            dummyParam->expType - IOParamType[i];
            IONode->child[0] = dummyParam;
        }
        else
        {
            IONode->child[0] = nullptr;
        }
    }
}

