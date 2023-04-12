/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW6
Dr. Wilder
DUE: 4/16/2023

FILE: semantic.cpp
DESC: Semantic analysis functions
*/


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "semantic.h"


#define MAXCHILDREN 3

using namespace std;

struct symErrors 
{
    int lineno;
    char* errorMsg;
};

vector<symErrors> errBuffer;


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
int returnlineno;
int functionLine;

char* functionName;

int localOffset = 0;
int globalOffset = 0;

TreeNode* curFunc = nullptr;

ExpType functionReturnType;
ExpType actualReturnType;
SymbolTable symbolTable;

//function returns symbol table
SymbolTable getSymbolTable() 
{
    return symbolTable;
}

//function prints error messages. 
void printErrorBuffer()
{
    for(int i = 0; i < errBuffer.size(); i++)
    {
        printf("%s", errBuffer[i].errorMsg);
    }
}

//Function checks each node. 
void analyze(TreeNode* node, int& nErrors, int& nWarnings)
{

    if(node == nullptr)
    {
        return;
    }

    switch(node->nodekind)
    {
        case DeclK:
                {
                    analyzeDecl(node, nErrors, nWarnings);
                }
                break;

        case StmtK:
                {
                    analyzeStmt(node, nErrors, nWarnings);
                }
                break;

        case ExpK:
                {
                    analyzeExp(node, nErrors, nWarnings);
                }
                break;
        default:
            {
                printf("Error: Unknown node kind\n");
            }
            break;  
    }

    if(node->sibling != nullptr)
    {
        analyze(node->sibling, nErrors, nWarnings);
    }
}

//function analizes semantics first by checking for keyword "main"
void semanticAnalysis(TreeNode* node, int& errors, int& warnings)
{

    analyze(node, nErrors, nWarnings);

    symbolTable.applyToAll(initializeWarningMessages);
    
    symbolTable.applyToAllGlobal(initializeWarningMessages);

 
    TreeNode *mainCheck = (TreeNode*)symbolTable.lookup("main");
    
    if(mainCheck == nullptr)
    {
        printError(16, 0, 0, NULL, NULL, NULL, 0);
    }
    else if(mainCheck != nullptr)
    {
        if(mainCheck->nodekind == DeclK && mainCheck->subkind.decl != FuncK)
        {
            printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
        else if(mainCheck->child[0] != NULL && mainCheck->child[0]->subkind.decl == ParamK)
        {
            printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
    }

    printErrorBuffer();
    
    errors = nErrors;
    
    warnings = nWarnings;
}

//function checks to see if warnings were used.
void initializeWarningMessages(std::string symbol, void* t)
{

    TreeNode* checkUsed;

    checkUsed = (TreeNode *)symbolTable.lookup(symbol.c_str());     

    if(!checkUsed->wasUsed && !checkUsed->isGlobal){

        if(checkUsed->subkind.decl == ParamK && !checkUsed->wasUsedErr && strcmp(checkUsed->attr.name, "main"))
        {
            checkUsed->wasUsedErr = true;
            printError(21, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }

        else if(checkUsed->subkind.decl == FuncK && !checkUsed->wasUsedErr && strcmp(checkUsed->attr.name, "main"))
        {
            checkUsed->wasUsedErr = true;
            printError(20, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }

        else
        {
            checkUsed->wasUsedErr = true;
            printError(17, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }
    }

    else if(!checkUsed->wasUsed && checkUsed->isGlobal && checkUsed->subkind.decl == FuncK)
    {
        
        if(strcmp(checkUsed->attr.name, "main") && !checkUsed->wasUsedErr)
        {
            checkUsed->wasUsedErr = true;

            printError(20, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }
    }

    else if(!checkUsed->wasUsed && checkUsed->isGlobal && !checkUsed->wasUsedErr)
    {
        checkUsed->wasUsedErr = true;
        printError(17, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
    }
}

//function prints errors for arrays.
void printArrayErrors(TreeNode* node)
{

   TreeNode *leftNode = nullptr;
   TreeNode *rightNode = nullptr;

   leftNode = node->child[0];
   rightNode = node->child[1];


   if(node->child[0]->subkind.exp == IdK)
   {

      leftNode = (TreeNode*)symbolTable.lookup(node->child[0]->attr.name);
      
      if(leftNode != nullptr)
      {
         node->child[0]->expType = leftNode->expType;
         node->expType = leftNode->expType;
      }


      if(leftNode == nullptr || !leftNode->isArray)
      {
        printError(15, node->lineno, 0, node->child[0]->attr.name, NULL, NULL, 0);
      }
   }
   else
   {
      printError(15, node->lineno, 0, node->child[0]->attr.name, NULL, NULL, 0);
   }
   if(node->child[1] != nullptr)
   {
        if(node->child[1]->expType != Integer && node->child[1]->expType != UndefinedType)
        {

            if(node->child[1]->subkind.decl == ParamK && node->child[1]->subkind.exp != CallK && node->child[1]->expType == Void)
            {
                //do nothing
            }
            else
            {
                printError(14, node->lineno, 0, node->child[0]->attr.name, ConvertExpToString(node->child[1]->expType), nullptr, 0);
            }
            
        }
   }
   if(node->child[1] != nullptr && node->child[1]->subkind.exp == IdK)
   {
      
      if(rightNode != nullptr && rightNode->isArray == true)
      {
        printError(13, node->lineno, 0, rightNode->attr.name, NULL, NULL, 0);
      }
      if(rightNode != nullptr)
      {
        node->child[1]->expType = rightNode->expType;
      }
   }

}

//********************************************************************************
// ************ DeclarationNode Analyzers *****************************
//********************************************************************************

//function analyzes declarations
void analyzeDecl(TreeNode* node, int& nErrors, int& nWarnings)
{
  
    if(symbolTable.depth() == 1)
    {
        node->isGlobal = true;
        node->memoryType = Global;
    }
    else if(node->isStatic)
    {
        node->isGlobal = false;
        node->memoryType = LocalStatic;
    }
    else
    {
        node->isGlobal = false;
        node->memoryType = Local;
    }

    
    TreeNode* declarationNode;
    
    if(node->subkind.decl != VarK && !symbolTable.insert(node->attr.name, node))
    {
        declarationNode = (TreeNode*)symbolTable.lookup(node->attr.name);
        
        printError(0, node->lineno, declarationNode->lineno, node->attr.name, NULL, NULL, 0);
    }

    switch(node->subkind.decl)
    {
        
        case VarK:
                {
                    analyzeVar(node, nErrors, nWarnings);
                }
                break;

        case FuncK:
                {
                    analyzeFunc(node, nErrors, nWarnings);
                }
                break;

        case ParamK:
                {
                    analyzeParam(node, nErrors, nWarnings);
                }
                break;
    }
}

//analyze variable nodes
void analyzeVar(TreeNode* node, int& nErrors, int& nWarnings)
{
    if(node->child[0] != nullptr)
    {
        for(int i = 0; i < MAXCHILDREN; i++)
        {
            analyze(node->child[i], nErrors, nWarnings);
        }
    }          

    TreeNode* symbol;

    if(!symbolTable.insert(node->attr.name, node))
    {
        symbol = (TreeNode*)symbolTable.lookup(node->attr.name);
        printError(0, node->lineno, symbol->lineno, node->attr.name, NULL, NULL, 0);
    }

    if(node->sibling != nullptr)
    {

        if(node->isStatic && node->lineno == node->sibling->lineno)
        {
            node->sibling->isStatic = node->isStatic;

            if(!node->isGlobal)
            {
                node->memoryType = LocalStatic;
            }
        }
    }

    if(node->child[0] != nullptr)
    {

        if(node->child[0]->subkind.exp == IdK || node->child[0]->subkind.exp == CallK)
        {
            printError(32, node->lineno, 0, node->attr.name, NULL, NULL, 0);
        }

        else if(node->child[0]->subkind.exp == OpK)
        {

            if(node->child[0] != NULL && node->child[0]->child[1] == NULL)
            {

                if(strcmp(node->child[0]->attr.name, "-") && !node->isArray)
                {
                    printError(32, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                }
            }

            else if(node->child[0]->child[0] != NULL && node->child[0]->child[1] != NULL)
            {
                analyzeNestedOpInitialization(node, node->child[0]);
            }
        }

        if(node->expType != node->child[0]->expType)
        {

            if(node->expType == Char && node->child[0]->expType == CharInt)
            {
                // do nothing
            }

            else if(node->expType == Integer && node->child[0]->expType == CharInt)
            {
                char charInsert[] = "char";
                printError(33, node->lineno, 0, node->attr.name, ConvertExpToString(node->expType), charInsert, 0);
            }

            else if(node->child[0]->expType == Void && node->child[0]->subkind.exp == IdK)
            {
                //do nothing 
            }

            else
            {
                printError(33, node->lineno, 0, node->attr.name, ConvertExpToString(node->expType), ConvertExpToString(node->child[0]->expType), 0);
            }
        }

        if(node->isArray && !node->child[0]->isArray)
        {
            printError(35, node->lineno, 0, node->attr.name, NULL, NULL, 0);
        }

        if(!node->isArray && node->child[0]->isArray)
        {
            printError(34, node->lineno, 0, node->attr.name, NULL, NULL, 0);
        }

        node->isInit = true;
        node->isDeclared = true;        
    }
    else
    {
        node->isDeclared = true;
    }

    //memory calculations
    //start with memory size
    if(node->isArray)
    {

        node->memorySize = node->arraySize + 1;
    }
    else
    {
        node->memorySize = 1;
    }

    //calc memory offsets -- start with global and static checks
    if(node->isGlobal || node->isStatic)
    {

        //check for arrays
        if(node->isArray)
        {
            node->memoryOffset = globalOffset - 1;
        }
        else
        {
            node->memoryOffset = globalOffset;
        }

        //adjust global offset by memory size
        globalOffset -= node->memorySize;
    }

    //calculate local mem offsets
    else
    {

        //check for arrays
        if(node->isArray)
        {

            node->memoryOffset = localOffset - 1;
        }
        else
        {
            node->memoryOffset = localOffset;
        }

        //adjust local offset by memory size
        localOffset -= node->memorySize;
    }
}

//analyze function nodes
void analyzeFunc(TreeNode* node, int& nErrors, int& nWarnings)
{
    curFunc = node;
    
    localOffset = 0;
    localOffset -= 2;
    
    Flag = false;

    symbolTable.enter(node->attr.name);

    scopeDepth = false;
    
    functionReturnType = node->expType;
    
    functionName = node->attr.name;
    
    functionLine = node->lineno;
    
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        analyze(node->child[i], nErrors, nWarnings);
    }

    if(Flag == false && node->expType != Void)
    {
        printError(19, node->lineno, 0, ConvertExpToString(functionReturnType), node->attr.name, NULL, 0);
    }

    symbolTable.applyToAll(initializeWarningMessages);
    
    symbolTable.leave();
    
    curFunc = nullptr;

    node->memorySize = 0; //functions have no memory size

    TreeNode* child_0 = node->child[0];

    while (child_0 != nullptr)
    {
        node->memorySize--;
        child_0 = child_0->sibling;
    }

    node->memorySize -= 2;

    node->memoryOffset = 0;
    
}

//analyze parameter nodes
void analyzeParam(TreeNode* node, int& nErrors, int& nWarnings)
{
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        analyze(node->child[i], nErrors, nWarnings);
        
        if(node->child[0] != nullptr)
        {
            node->child[0]->isInit = true;
        }
    }

    node->isInit = true;
    
    //track memsize and offset for parameters
    node->memorySize = 1;
    node->memoryOffset = localOffset;
    node->memoryType = Parameter;
    localOffset--;
}


//********************************************************************************
// ************ StatementNode Analyzers *****************************
//********************************************************************************

//analyze statement nodes
void analyzeStmt(TreeNode* node, int& nErrors, int& nWarnings)
{
    switch(node->subkind.stmt)
    {
        case IfK:
                {
                    analyzeIf(node, nErrors, nWarnings);
                }
                break;

        case ForK:
                {
                    analyzeFor(node, nErrors, nWarnings);
                }
                break;


        case WhileK:
                {
                    analyzeWhile(node, nErrors, nWarnings);
                }
                break;

        case ReturnK:
                {
                    analyzeReturn(node, nErrors, nWarnings);
                }
                break;

        case BreakK:
                {
                    analyzeBreak(node, nErrors, nWarnings);
                }
                break;

        case RangeK:
                {
                    analyzeRange(node, nErrors, nWarnings);
                }
                break;

        case CompoundK:
                    {
                        analyzeCompound(node, nErrors, nWarnings);
                    }
                    break;

        default:
            {
                printf("Error: Unknown statement node kind\n");
            }
            break; 
    }

}

//analyze if statement
void analyzeIf(TreeNode* node, int& nErrors, int& nWarnings)
{
    loop = true;
    
    symbolTable.enter(node->attr.name);
    
    loopDepth++;
    
    scopeDepth = false;
    
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        if(node->child[0])
        {
            analyze(node->child[i], nErrors, nWarnings);
        }
    }


    if(node->child[0]->expType != Boolean && node->child[0]->subkind.exp != OpK && !node->child[0]->declErr)
    {
        char ifStmt[] = "if";
        printError(27, node->lineno, 0, ifStmt, ConvertExpToString(node->child[0]->expType), NULL, 0 );
    }

    if(node->child[0]->isArray)
    {
        char ifStmt[] = "if";
        printError(23, node->lineno, 0, ifStmt, NULL, NULL, 0);
    }
    
    loopDepth--;

    symbolTable.applyToAll(initializeWarningMessages);

    if(loopDepth == 1)
    {
        loop = false;
    }
    
    symbolTable.leave();
    
    scopeDepth = true;
}

//analyze while statement
void analyzeWhile(TreeNode* node, int& nErrors, int& nWarnings)
{
    loop = true;
    
    symbolTable.enter(node->attr.name);
    
    loopDepth ++;
    
    scopeDepth = false;

    for(int i = 0; i < MAXCHILDREN; i++)
    {
        if(node->child[i])
        {
            analyze(node->child[i], nErrors, nWarnings);

            if(i < 1)
            {
                if(node->child[0]->expType != Boolean && node->child[0]->subkind.exp != OpK && !node->child[0]->declErr)
                {
                    char whileStmt[] = "while";
                    printError(27, node->lineno, 0, whileStmt, ConvertExpToString(node->child[0]->expType), NULL, 0 );
                }

                if(node->child[0]->isArray)
                {
                    char whileStmt[] = "while";
                    printError(23, node->lineno, 0, whileStmt, NULL, NULL, 0);
                }
            }
        }
    }

    loopDepth--;

    symbolTable.applyToAll(initializeWarningMessages);

    if(loopDepth == 1)
    {
        loop = false;
    }
    
    symbolTable.leave();
    
    scopeDepth = true;
}

//analyze for statement
void analyzeFor(TreeNode* node, int& nErrors, int& nWarnings)
{
    loop = true;
    
    inFor = true;
    
    loopDepth++;
    
    symbolTable.enter(node->attr.name);
    
    scopeDepth = false;

    int forSize = localOffset;
    
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        if(node->child[i])
        {
            analyze(node->child[i], nErrors, nWarnings);
            node->child[0]->isInit = true;
            node->child[1]->isInit = true;
        }
    }

    loopDepth--;

    if(loopDepth == 1)
    {
        loop = false;
    }

    inFor = false;
    
    symbolTable.applyToAll(initializeWarningMessages);
    
    symbolTable.leave();
    
    scopeDepth = true;

    node->memorySize = localOffset;
    node->memoryType = None;
    localOffset = forSize;
}

//analyze compound statement
void analyzeCompound(TreeNode* node, int& nErrors, int& nWarnings)
{
    bool isInCurScope = scopeDepth;

    int currentSize = localOffset; 

    if(isInCurScope)
    {
        symbolTable.enter("compound");
    }
    else
    {
        scopeDepth = true;
    }

    for(int i = 0; i < MAXCHILDREN; i++)
    {
        analyze(node->child[i], nErrors, nWarnings);
    }

    if(isInCurScope)
    {
        symbolTable.applyToAll(initializeWarningMessages);
        symbolTable.leave();
    }

    node->memorySize = localOffset; 
    localOffset = currentSize;
    node->memoryType = None; 
}

//analyze return statement
void analyzeReturn(TreeNode* node, int& nErrors, int& nWarnings)
{
    Flag = true;
    returnlineno = node->lineno;

    analyze(node->child[0], nErrors, nWarnings);

    if(node->child[0] != nullptr)
    {

        actualReturnType = node->child[0]->expType;

        if(curFunc == nullptr)
        {
            return;
        }

        else if(node->child[0]->isArray)
        {
            printError(10, node->lineno, 0, NULL, NULL, NULL, 0);
        }

        else if(node->child[0]->child[0] != nullptr)
        {
            if(node->child[0]->child[0]->isArray)
            {

                if(strcmp(node->child[0]->attr.name, "["))
                {
                    printError(10, node->lineno, 0, NULL, NULL, NULL, 0);
                }
            }
        }
    
        if(functionReturnType == Void)
        {
            printError(29, returnlineno, functionLine, functionName, NULL, NULL, 0);
        }

        else if(functionReturnType != actualReturnType && actualReturnType != Void && functionReturnType != Void)
        {

            if(!(functionReturnType == Char && actualReturnType == CharInt))
            {
                printError(31, returnlineno, functionLine, functionName, ConvertExpToString(functionReturnType), ConvertExpToString(actualReturnType), 0);
            }
        }

        else if(functionReturnType != actualReturnType && functionReturnType != Void && node->child[0]->subkind.exp == CallK)
        {
            
            if(!(functionReturnType == Char && actualReturnType == CharInt))
            {
                printError(31, returnlineno, functionLine, functionName, ConvertExpToString(functionReturnType), ConvertExpToString(actualReturnType), 0);
            }
        }
    }

    else if(node->child[0] == nullptr)
    {

        if(functionReturnType != Void)
        {
            printError(30, returnlineno, functionLine, functionName, ConvertExpToString(functionReturnType), NULL, 0);
        }
    }
}

//analyze break statement
void analyzeBreak(TreeNode* node, int& nErrors, int& nWarnings)
{
    if(!loop)
    {
        printError(22, node->lineno, 0, NULL, NULL, NULL, 0);
    }
}

//analyze range statement
void analyzeRange(TreeNode* node, int& nErrors, int& nWarnings)
{
    rangePos;
    
    range = true;

    for(int i = 0; i < MAXCHILDREN; i++)
    {
        if(node->child[i])
        {
            rangePos++;

                if(node->child[i]->child[0] != nullptr && node->child[i]->child[0]->isArray)
                {
                    node->child[i]->child[0]->isIndexed = true;
                }

                else if(rangePos == 1)
                {
                    if(node->child[0]->subkind.exp == IdK)
                    {
                        TreeNode* valFound = (TreeNode*)symbolTable.lookup(node->child[0]->attr.name);
                        
                        if(valFound == nullptr)
                        {
                            printError(1, node->lineno, 0, node->child[0]->attr.name, NULL, NULL, 0); 
                            node->declErr = true;
                        }
                        else
                        {
                            valFound->wasUsed = true;
                        }
                    }
                }

            analyze(node->child[i], nErrors, nWarnings);

        }
    }

    range = false;
    rangePos = 0;
}


//********************************************************************************
// ************ ExpressionNodes Analyzers *****************************
//********************************************************************************

//analyze expression node
void analyzeExp(TreeNode *node, int& nErrors, int& nWarnings)
{

    bool rightErr, leftErr, unaryErrors;
    rightErr = leftErr = unaryErrors = false;

    TreeNode* valFound = nullptr;
    TreeNode* leftNode = nullptr;
    TreeNode* rightNode = nullptr;

    switch(node->subkind.exp) 
    {
        case AssignK:
                {
                    analyze_Op_and_Assign(node, leftNode, rightNode, nErrors, nWarnings);
                }
                break; 

        case OpK:
                {
                    analyze_Op_and_Assign(node, leftNode, rightNode, nErrors, nWarnings);
                }
                break;

        case ConstantK:
                    {
                        analyzeConst(node, nErrors, nWarnings);
                    }
                    break; 

        case IdK:
                {
                    analyzeId(node, valFound, nErrors, nWarnings);
                }
                break; 

        case CallK:
                {
                    analyzeCall(node, nErrors, nWarnings);
                }
                break;     
    }

}

//analyze Op Expression
void analyze_Op_and_Assign(TreeNode* node, TreeNode* leftNode, TreeNode* rightNode, int& nErrors, int& nWarnings)
{

    bool leftStr, rightStr, isBinary, leftArr, rightArr, leftIndx, rightIndx, leftInit, leftDecl, rightInit, rightDecl, throwError;
    leftStr = rightStr = isBinary = leftArr = rightArr = leftIndx = rightIndx = leftInit = leftDecl = rightInit = rightDecl = throwError = false;

    ExpType leftSide, rightSide, returnType, leftExpected, rightExpected, childReturnType;
    leftSide = rightSide = returnType = leftExpected = rightExpected = childReturnType = UndefinedType;

    bool rightErr, leftErr, unaryErrors;
    rightErr = leftErr = unaryErrors = false;

    if(!strcmp(node->attr.name, "<="))
    {
        if(node->child[0] != nullptr)
        {
            
            if(node->child[0]->child[0]!=nullptr && !strcmp(node->child[0]->attr.name, "["))
            {
                node->child[0]->child[0]->isInit = true;

                if(node->child[0]->child[1] != nullptr)
                {
                    node->child[0]->child[1]->isInit = true;

                    if(node->child[0]->child[1]->child[0] != nullptr && node->child[0]->child[1]->child[1] != nullptr)
                    {

                        if(node->child[0]->child[1]->subkind.exp == OpK)
                        {
                            node->child[0]->child[1]->child[0]->isInit = true;
                            node->child[0]->child[1]->child[1]->isInit = true;
                        }
                    }
                }

                else if(node->child[0]->child[1]->child[0] != nullptr)
                {
                    node->child[0]->child[1]->child[0]->isInit = true;
                }

            }

            else if(node->child[1] != nullptr && node->child[1]->expType == Void)
            {

                if(!strcmp(node->child[1]->attr.name, "<="))
                {
                    node->child[0]->isInit = true;
                }

                if(node->child[1]->subkind.exp == CallK)
                {
                    node->child[0]->isInit = true;
                }

                else if(!strcmp(node->child[1]->attr.name, "["))
                {

                    char* lhs = strdup(node->child[0]->attr.name);
                    char* rhs = strdup(node->child[1]->child[0]->attr.name);

                    if(strcmp(lhs, rhs))
                    {
                        node->child[0]->isInit = true;
                    }

                }
                else if(node->child[0]!= nullptr && node->child[1]!= nullptr)
                {

                    if(node->child[0]->subkind.exp == IdK && !node->child[0]->isInit)
                    {

                        if(node->child[1]->subkind.exp == IdK)
                        {

                            char* lhs = strdup(node->child[0]->attr.name);
                            char* rhs = strdup(node->child[1]->attr.name);

                            if(strcmp(lhs, rhs))
                            {
                                node->child[0]->isInit = true;
                            }
                        }

                        else if(node->child[1]->subkind.exp == AssignK)
                        {
                            analyzeNestedAssign(node->child[1]);
                            node->child[0]->isInit = true;
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

                if(node->child[1] != nullptr && node->child[1]->child[0] != nullptr)
                {

                    if(node->child[1]->child[0]->subkind.exp == IdK)
                    {

                        char *c0 = strdup(node->child[0]->attr.name);
                        char *c10 = strdup(node->child[1]->child[0]->attr.name);

                        if(strcmp(c0, c10))
                        {
                            node->child[0]->isInit = true;
        
                        }
                    }

                    else
                    {
                        node->child[0]->isInit = true;
                    }
                    

                }

                else
                {
                    node->child[0]->isInit = true;
                }
            }
        }

    }

    if(strcmp(node->attr.name, "<="))
    {
        if(node->child[0] != nullptr)
        {
            node->child[0]->wasUsed = true;
            
        }
        if(node->child[1] != nullptr)
        {
            node->child[1]->wasUsed = true;
        }
    }

    if(!strcmp(node->attr.name, "*"))
    {
        sizeOfArrayFlg = true;
    }

    for(int i= 0; i < MAXCHILDREN; i++)
    {
        analyze(node->child[i], nErrors, nWarnings);
    }

    sizeOfArrayFlg = false;

    if(node->child[0] != nullptr)
    {
        leftNode = node->child[0];
        leftSide = leftNode->expType;
        leftArr = leftNode->isArray;

        if(leftNode->child[0] != nullptr)
        {
            leftArr = false; 
            leftIndx = true; 
        }
        if(leftNode->nodekind == ExpK)
        {
            if(leftNode->subkind.exp == CallK)
            {
                leftArr = false;
            }
            if(leftNode->subkind.exp == ConstantK)
            {
                leftStr = true;
            }
        }
    }

    if(node->child[1] != nullptr)
    {
        rightNode = node->child[1];
        rightSide = rightNode->expType;
        rightArr = rightNode->isArray;
        

        if(rightNode->child[0] != nullptr)
        {
            rightArr = false; 
            rightIndx = true; 
        }
        if(rightNode->nodekind == ExpK)
        {
            if(rightNode->subkind.exp == CallK)
            {
                rightArr = false;
            }
            if(rightNode->subkind.exp == ConstantK)
            {
                rightStr = true;
            }
        }
        isBinary = true;
    }

    getExpTypes(node->attr.name, isBinary, unaryErrors, leftExpected, rightExpected, returnType);

    if(leftSide == Void && !(leftNode->nodekind == ExpK && leftNode->subkind.exp == CallK))
    {
        leftErr = true;
    }
    if(rightSide == Void && !(rightNode->nodekind == ExpK && rightNode->subkind.exp == CallK))
    {
        rightErr = true;
    }

    if(!isBinary && !leftErr)
    {


        if(leftSide != leftExpected && leftExpected != UndefinedType)
        {


            if(!strcmp(node->attr.name, "-"))
            {
                char uMinus[] = "chsign";
                printError(9, node->lineno, 0, uMinus, ConvertExpToString(leftExpected), ConvertExpToString(leftSide), 0);
            }

            else
            {
                printError(9, node->lineno, 0, node->attr.name, ConvertExpToString(leftExpected), ConvertExpToString(leftSide), 0);
            }
        }

        else if(!strcmp(node->attr.name, "not") && leftSide != leftExpected)
        {

            printError(9, node->lineno, 0, node->attr.name, ConvertExpToString(leftExpected), ConvertExpToString(leftSide), 0);
        }

        else if(!strcmp(node->attr.name, "*") && (!leftArr && leftSide != UndefinedType))
        {
            char uSizeof[] = "sizeof";
            printError(8, node->lineno, 0, uSizeof, NULL, NULL, 0);
        } 

        if(leftArr)
        {
            if(strcmp(node->attr.name, "*") != 0)
            {

                if(!strcmp(node->attr.name, "-"))
                {
                    char uMinus[] = "chsign";
                    printError(7, node->lineno, 0, uMinus, NULL, NULL, 0);
                }
                else
                {
                    printError(7, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                }
            }
        }
    }
    else
    {
        if(!unaryErrors)
        {

            if(!strcmp(node->attr.name, "["))
            {
                printArrayErrors(node);
            }
    
            else if(leftSide != rightSide && !leftErr && !rightErr)
            {

                if(!strcmp(ConvertExpToString(leftSide), "int") && !strcmp(ConvertExpToString(rightSide), "CharInt"))
                {
                    char diffCharInt[] = "char";
                    printError(2, node->lineno, 0, node->attr.name, ConvertExpToString(leftSide), diffCharInt, 0);
                }
                else if(!strcmp(ConvertExpToString(leftSide), "char") && !strcmp(ConvertExpToString(rightSide), "CharInt"))
                {
                    //do nothing
                }

                else if(!strcmp(node->attr.name, "<=") && node->child[1]->subkind.exp == OpK)
                {

                    getReturnType(node->child[1]->attr.name, isBinary, childReturnType);
                    
                    if(childReturnType != node->child[0]->expType)
                    {
                        printError(2, node->lineno, 0, node->attr.name, ConvertExpToString(leftSide), ConvertExpToString(childReturnType), 0);
                    }

                    else if(node->child[1]->child[1] != nullptr && node->child[1]->child[1]->subkind.exp == CallK)
                    {
                        printError(2, node->lineno, 0, node->attr.name, ConvertExpToString(leftSide), ConvertExpToString(childReturnType), 0);
                    }
                }
                else
                {

                    if(node->child[0]->subkind.exp != CallK)
                    {

                        printError(2, node->lineno, 0, node->attr.name, ConvertExpToString(leftSide), ConvertExpToString(rightSide), 0);
                    }
                    else
                    {
                        //do nothing
                    }
                }
            }
        }


        if(!(leftExpected == UndefinedType || rightExpected == UndefinedType))
        {
            
            if(leftExpected == CharInt || rightExpected == CharInt)
            {
                //do nothing
            }

            else if(leftSide == rightSide && leftNode->subkind.exp == CallK && rightNode->subkind.exp == CallK)
            {

                    TreeNode* lhs = (TreeNode*)symbolTable.lookup(node->child[0]->attr.name);
                    TreeNode* rhs = (TreeNode*)symbolTable.lookup(node->child[1]->attr.name);

                    if(lhs != nullptr && rhs != nullptr)
                    {

                        if(lhs->subkind.decl == FuncK && rhs->subkind.decl == FuncK && !lhs->isIO && !rhs->isIO)
                        {
                            if(node->child[0]->expType == Void && node->child[1]->expType == Void)
                            {
                                printError(3, node->lineno, 0, node->attr.name, ConvertExpToString(leftExpected), ConvertExpToString(leftSide), 0);
                                printError(4, node->lineno, 0, node->attr.name, ConvertExpToString(rightExpected), ConvertExpToString(rightSide), 0);
                            }
                            
                        }

                    }
            }
            else
            {

                if(leftSide != leftExpected && !leftErr)
                {
                    printError(3, node->lineno, 0, node->attr.name, ConvertExpToString(leftExpected), ConvertExpToString(leftSide), 0);
                }

                if(rightSide != rightExpected && !rightErr && rightSide != UndefinedType)
                {

                    if(rightSide == Void && node->child[1]->subkind.exp == CallK && returnType != Boolean)
                    {
                        printError(4, node->lineno, 0, node->attr.name, ConvertExpToString(rightExpected), ConvertExpToString(rightSide), 0);
                    }
                    else if(rightSide != Void)
                    {
                        printError(4, node->lineno, 0, node->attr.name, ConvertExpToString(rightExpected), ConvertExpToString(rightSide), 0);
                    }
                }
            }
        }

        if(leftArr || rightArr)
        {

            if(strcmp(node->attr.name, "<=") && leftExpected != UndefinedType)
            {
                if(!strcmp(node->attr.name, "<") || !strcmp(node->attr.name, ">") || !strcmp(node->attr.name, "=") || !strcmp(node->attr.name, "!>") || !strcmp(node->attr.name, "!<") || !strcmp(node->attr.name, "><")) //do i need ><?
                {
                
                    if(leftArr && !rightArr)
                    {
                        printError(5, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                    }

                    else if(!leftArr && rightArr)
                    {
                        printError(6, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                    }
                }

                else
                {
                    printError(7, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                }
            }
            
            else
            {
                if(!strcmp(node->attr.name, "["))
                {
                    //do nothing
                }

                else if((leftArr && !rightArr) || (!leftArr && rightArr))
                {

                    if(leftArr && !rightArr)
                    {
                        printError(5, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                    }

                    else if(!leftArr && rightArr)
                    {
                        printError(6, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                    }
                }
            }
        }
    }

    if(returnType != UndefinedType)
    {
        node->expType = returnType;
    }
    else
    {
        node->expType = leftSide;
    }
}

//analyze Const Expression
void analyzeConst(TreeNode* node, int& nErrors, int& nWarnings)
{
    for(int i = 0; i < MAXCHILDREN; i++)
    {
        analyze(node->child[i], nErrors, nWarnings);
    }

    if(range)
    {
        if(inFor)
        {
            if(node->expType != Integer)
            {
                char intExpect[] = "int";
                printError(26, node->lineno, 0, intExpect, ConvertExpToString(node->expType), NULL, rangePos);
            }
        }
    }

    if(node->expType == CharInt)
    {
        node->memoryType = Global;
        node->memoryOffset = globalOffset - 1;
        node->memorySize = node->arraySize + 1;
        globalOffset -= node->memorySize;
    }
}

//analyze Id Expression
void analyzeId(TreeNode* node, TreeNode* valFound, int& nErrors, int& nWarnings)
{
    valFound = (TreeNode*)symbolTable.lookup(node->attr.name);

    if(valFound == nullptr)
    {

        if(range && rangePos == 1)
        {
            node->isDeclared = true;
        }

        else
        {
            printError(1, node->lineno, 0, node->attr.name, NULL, NULL, 0); 
            node->declErr = true;    
        }           
    }

    else if(range)
    {

        if(inFor)
        {

            node->expType = valFound->expType;
            node->isArray = valFound->isArray;
            node->memorySize = valFound->memorySize;
            node->memoryOffset = valFound->memoryOffset;
            node->memoryType = valFound->memoryType;

            if(node->expType != Integer && rangePos >= 1)
            {
                if(!sizeOfArrayFlg)
                {

                    if(!strcmp(node->attr.name, "main"))
                    {
                        printError(12, node->lineno, 0, node->attr.name, NULL, NULL, 0);  
                    }
                    else
                    {
                        char intExpect[] = "int";
                        printError(26, node->lineno, 0, intExpect, ConvertExpToString(node->expType), NULL, rangePos);
                    }
                }

            }

            if(rangePos >= 1 && !valFound->isInit)
            {
                if(valFound->isDeclared == true)
                {

                    if(!valFound->isInit && !valFound->warningReported && !valFound->isStatic && !valFound->isGlobal)
                    {

                        if(!node->isInit)
                        {
                            valFound->warningReported = true;
                            valFound->wasUsed = true;
                            printError(18, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                        }
                        
                        else
                        {
                            valFound->isInit = true;
                        }
                    }
            
                }
            }

            else if(rangePos > 1 && valFound->isInit)
            {
                valFound->wasUsed = true;
            }

            if(valFound->isArray && !sizeOfArrayFlg && !node->isIndexed)
            {
                printError(24, node->lineno, 0, NULL, NULL, NULL, rangePos);
            }

            node->isIndexed = false;

        }

        node->isInit = true;
    }

    else
    {

        if(valFound->isDeclared == true)
        {
        
            if(!valFound->isInit && !valFound->warningReported && !valFound->isStatic && !valFound->isGlobal)
            {
                if(!node->isInit)
                {
                    valFound->warningReported = true;
                    printError(18, node->lineno, 0, node->attr.name, NULL, NULL, 0);
                }
                else
                {
                    valFound->isInit = true;
                }
            }
        }

        if(valFound->subkind.decl == FuncK)
        {
            printError(12, node->lineno, 0, node->attr.name, NULL, NULL, 0);
            valFound->wasUsed = true;
            return;
        }
        else
        {
            node->expType = valFound->expType;
            node->isArray = valFound->isArray;
            node->isGlobal = valFound->isGlobal;
            node->isStatic = valFound->isStatic;
            node->memorySize = valFound->memorySize;
            node->memoryOffset = valFound->memoryOffset;
            node->memoryType = valFound->memoryType;

            if(!range && valFound->subkind.decl != FuncK)
            {
                valFound->wasUsed = true;
            }
        }

        if(node->child[0] != nullptr)
        {
            analyze(node->child[0], nErrors, nWarnings);
            
            if(node->child[0]->expType == Void && !(node->child[0]->nodekind == ExpK && node->child[0]->subkind.exp == CallK))
            {
                return;
            }
            
            if(!node->isArray)
            {
                return;
            }
            
            else
            {

                if(node->child[0]->expType != Integer)
                {
                    printError(14, node->lineno, 0, node->attr.name, ConvertExpToString(node->child[0]->expType), NULL, 0);
                }

                if(node->child[0]->isArray && node->child[0]->child[0] == nullptr)
                {
                    printError(13, node->lineno, 0, node->child[0]->attr.name, NULL, NULL, 0);
                }
            }
        }
    }
}

//analyze Assign Expression
void analyzeCall(TreeNode* node, int& nErrors, int& nWarnings)
{
    int paramCount = 1;
    
    TreeNode* funcFound;

    if(node->subkind.exp == CallK)
    {
        funcFound = (TreeNode*)symbolTable.lookup(node->attr.name);
        
        if(funcFound == nullptr)
        {
            printError(1, node->lineno, 0, node->attr.name, NULL, NULL, 0);  
            node->declErr = true; 
        }
        else
        {
            //do nothing
        }
    }

    for(int i = 0; i < MAXCHILDREN; i++)
    {
        analyze(node->child[i], nErrors, nWarnings);
    }

    if(funcFound != nullptr)
    {
        node->expType = funcFound->expType;
        node->isArray = funcFound->isArray;
        node->isGlobal = funcFound->isGlobal;
        node->isStatic = funcFound->isStatic;
        funcFound->wasUsed = true;
        node->memorySize = funcFound->memorySize;
        node->memoryOffset = funcFound->memoryOffset;
        node->memoryType = funcFound->memoryType;


        if(funcFound->subkind.decl != FuncK)
        {
            printError(11, node->lineno, 0, node->attr.name, NULL, NULL, 0);
        }
        

        else if(range)
        {

            if(inFor)
            {

                if(node->expType != Integer)
                {

                    if(!strcmp(node->attr.name, "main"))
                    {
                        printError(12, node->lineno, 0, node->attr.name, NULL, NULL, 0);                               
                    }
                    else
                    {
                        char intExpect[] = "int";
                        printError(26, node->lineno, 0, intExpect, ConvertExpToString(node->expType), NULL, rangePos);
                    }
                }
            }
        }

        else
        {

            if(funcFound->child[0] != nullptr && node->child[0] != nullptr)
            {
                printParmErrors(funcFound, node, funcFound->child[0], node->child[0], paramCount);
            }

            else if(funcFound->child[0] == nullptr && node->child[0] != nullptr)
            {
                printError(38, node->lineno, funcFound->lineno, node->attr.name, NULL, NULL, 0);
            }

            else if(funcFound->child[0] != nullptr && node->child[0] == nullptr)
            {
                printError(37, node->lineno, funcFound->lineno, node->attr.name, NULL, NULL, 0);
            }
        }
    }
}


void getExpTypes(const char* strng, bool isBinary, bool &unaryErrors, ExpType &left, ExpType &right, ExpType &rightT)
{

    string unaryOps[6] = {"not", "*", "?", "-", "--", "++"};

    string binaryOps[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", "!<", "!>", "==", "!=", "=", "and", "or"};
    
    string op(strng);
    
    unaryErrors = false;

    if(!isBinary)
    {

        for(int i = 0; i < 6; i++)
        {

            if(op == unaryOps[i])
            {

                if(i == 0)
                {
                    left = right = rightT = Boolean;
                }

                if(i == 1)
                {
                    left = right = UndefinedType;
                    rightT = Integer;
                }

                if(i >= 2)
                {
                    left = right = rightT = Integer;
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
                    left = right = rightT = Integer;
                    unaryErrors = true;
                }
  
                if(i >= 9 && i <= 12)
                {
                    left = right = CharInt; 
                    rightT = Boolean;
                }

                if(i >= 13 && i <=14)
                {
                    left = right = UndefinedType;
                    rightT = Boolean;
                }

                if(i == 15)
                {
                    left = right = UndefinedType;
                    rightT = Boolean;
                }

                if(i >= 16)
                {
                    left = right = rightT = Boolean;
                    unaryErrors = true;
                }

            }
        }
    }

}


char* ConvertExpToString(ExpType type)
{
    switch(type)
    {
       
        case Void:
                {
                    return strdup("void");
                }

        case Integer:
                    {
                        return strdup("int");
                    }

        case Boolean:
                    {
                        return strdup("bool");
                    }
        
        case Char:
                {
                    return strdup("char");
                }
        
        case CharInt:
                    {
                        return strdup("CharInt");
                    }

        case UndefinedType:
                        {
                            return strdup("UndefinedType");
                        }
        
        default:
                {
                    return strdup("expType not found\n");
                }
    }
}


void getReturnType(const char* strng, bool isBinary, ExpType &rightT)
{

    string unaryOps[6] = {"not", "*", "?", "-", "--", "++"};

    string binaryOps[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", "!<", "!>", "==", "!=", "=", "and", "or"};
    string op(strng);

    if(!isBinary)
    {

        for(int i = 0; i < 6; i++)
        {

            if(op == unaryOps[i])
            {

                if(i == 0)
                {
                    rightT = Boolean;
                }
                
                if(i == 1)
                {
                    
                    rightT = Integer;
                }

                if(i >= 2)
                {
                    rightT = Integer;
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
                    rightT = Integer;
                }

                if(i >= 9 && i <= 12)
                {
                    rightT = Boolean;
                }

                if(i >= 13 && i <=14)
                {
                    rightT = Boolean;
                }

                if(i == 15)
                {
                    rightT = Boolean;
                }

                if(i >= 16)
                {
                    rightT = Boolean;
                }

            }
        }
    }

}


void printError(int errCode, int lineno, int reasonNum, char* s1, char* s2, char* s3, int i)
{

    if(errCode > 16 && errCode < 22)
    {
        nWarnings++;
    }
    else
    {
        nErrors++;
    }

    
    switch(errCode)
    {

        case 0: 
            sprintf(Buffer, "ERROR(%d): Symbol '%s' is already declared at line %d.\n", lineno, s1, reasonNum);
            break;

        case 1:
            sprintf(Buffer, "ERROR(%d): Symbol '%s' is not declared.\n", lineno, s1);
            break;

        case 2: 
            sprintf(Buffer, "ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", lineno, s1, s2, s3);
            break;

        case 3:
            sprintf(Buffer, "ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", lineno, s1, s2, s3);
            break;

        case 4:
            sprintf(Buffer, "ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", lineno, s1, s2, s3);
            break;

        case 5: 
            sprintf(Buffer, "ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", lineno, s1);
            break;

        case 6:
            sprintf(Buffer, "ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", lineno, s1);
            break;

        case 7: 
            sprintf(Buffer, "ERROR(%d): The operation '%s' does not work with arrays.\n", lineno, s1);
            break;

        case 8: 
            sprintf(Buffer, "ERROR(%d): The operation '%s' only works with arrays.\n", lineno, s1);
            break;

        case 9:
            sprintf(Buffer, "ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", lineno, s1, s2, s3);
            break;

        case 10: 
            sprintf(Buffer, "ERROR(%d): Cannot return an array.\n", lineno);
            break;

        case 11: 
            sprintf(Buffer, "ERROR(%d): '%s' is a simple variable and cannot be called.\n", lineno, s1);
            break;

        case 12:
            sprintf(Buffer, "ERROR(%d): Cannot use function '%s' as a variable.\n", lineno, s1);
            break;

        case 13:
            sprintf(Buffer, "ERROR(%d): Array index is the unindexed array '%s'.\n", lineno, s1);
            break;

        case 14: 
            sprintf(Buffer, "ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n", lineno, s1, s2);
            break;

        case 15: 
            sprintf(Buffer, "ERROR(%d): Cannot index nonarray '%s'.\n", lineno, s1);
            break;

        case 16: 
            sprintf(Buffer, "ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
            break;

        case 17: 
            sprintf(Buffer, "WARNING(%d): The variable '%s' seems not to be used.\n", lineno, s1);
            break;

        case 18:
            sprintf(Buffer, "WARNING(%d): Variable '%s' may be uninitialized when used here.\n", lineno, s1);
            break;

        case 19: 
            sprintf(Buffer, "WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", lineno, s1, s2);
            break;

        case 20:
            sprintf(Buffer, "WARNING(%d): The function '%s' seems not to be used.\n", lineno, s1);
            break;

        case 21:
            sprintf(Buffer, "WARNING(%d): The parameter '%s' seems not to be used.\n", lineno, s1);
            break;

        case 22: 
            sprintf(Buffer, "ERROR(%d): Cannot have a break statement outside of loop.\n", lineno);
            break;

        case 23:
            sprintf(Buffer, "ERROR(%d): Cannot use array as test condition in %s statement.\n", lineno, s1);
            break;

        case 24:
            sprintf(Buffer, "ERROR(%d): Cannot use array in position %d in range of for statement.\n", lineno, i);
            break;

        case 25:
            sprintf(Buffer, "ERROR(%d): Expecting type %s in parameter %d of call to '%s' declared on line %d but got type %s.\n", lineno, s2, i, s1, reasonNum, s3);
            break;

        case 26:
            sprintf(Buffer, "ERROR(%d): Expecting type %s in position %d in range of for statement but got type %s.\n", lineno, s1, i, s2);
            break;

        case 27:
            sprintf(Buffer, "ERROR(%d): Expecting Boolean test condition in %s statement but got type %s.\n", lineno, s1, s2);
            break;

        case 28:
            sprintf(Buffer, "ERROR(%d): Expecting array in parameter %d of call to '%s' declared on line %d.\n", lineno, i, s1, reasonNum);
            break;

        case 29:
            sprintf(Buffer, "ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n", lineno, s1, reasonNum);
            break;

        case 30:
            sprintf(Buffer, "ERROR(%d): Function '%s' at line %d is expecting to return type %s but return has no value.\n", lineno, s1, reasonNum, s2);
            break;

        case 31:
            sprintf(Buffer, "ERROR(%d): Function '%s' at line %d is expecting to return type %s but returns type %s.\n", lineno, s1, reasonNum, s2, s3);
            break;

        case 32:
            sprintf(Buffer, "ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", lineno, s1);
            break;

        case 33:
            sprintf(Buffer, "ERROR(%d): Initializer for variable '%s' of type %s is of type %s\n", lineno, s1, s2, s3);
            break;

        case 34:
            sprintf(Buffer, "ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is not an array and rhs is an array.\n", lineno, s1);
            break;

        case 35:
            sprintf(Buffer, "ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is an array and rhs is not an array.\n", lineno, s1);
            break;
        
        case 36:
            sprintf(Buffer, "ERROR(%d): Not expecting array in parameter %d of call to '%s' declared on line %d.\n", lineno, i, s1, reasonNum);
            break;

        case 37:
            sprintf(Buffer, "ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n", lineno, s1, reasonNum);
            break;

        case 38:
            sprintf(Buffer, "ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n", lineno, s1, reasonNum);
    }

    symErrors all;
    all.lineno = lineno;
    all.errorMsg = strdup(Buffer);
    errBuffer.push_back(all);
}


void analyzeNestedOpInitialization(TreeNode* node, TreeNode* child)
{

    if(child->child[0] != nullptr && child->child[1] != nullptr)
    {

        if(child->child[0]->subkind.exp == OpK)
        {

            analyzeNestedOpInitialization(node, child->child[0]);
        }

        if(child->child[1]->subkind.exp == OpK)
        {
            analyzeNestedOpInitialization(node, child->child[1]);
        }

        else if(child->child[0]->subkind.exp == IdK || child->child[1]->subkind.exp == IdK)
        {
            printError(32, node->lineno, 0, node->attr.name, NULL, NULL, 0);
        }
    }

    else if(child->child[0] != nullptr && child->child[1] == nullptr)
    {
  
        if(strcmp(child->attr.name, "not"))
        {
            printError(32, node->lineno, 0, node->attr.name, NULL, NULL, 0);
        }
    }
}


void analyzeNestedAssign(TreeNode* rightChild)
{

    if(rightChild->child[0] != nullptr)
    {
        rightChild->child[0]->isInit = true;
    }
}
 

void printParmErrors(TreeNode* functionNode, TreeNode* node, TreeNode* functionNodeParm, TreeNode* nodeParm, int numParms)
{
    

    if(functionNodeParm->sibling == nullptr && nodeParm->sibling != nullptr)
    {
        printError(38, node->lineno, functionNode->lineno, node->attr.name, NULL, NULL, 0);
    }

    else if(functionNodeParm->sibling != nullptr && nodeParm->sibling == nullptr)
    {
        printError(37, node->lineno, functionNode->lineno, node->attr.name, NULL, NULL, 0);
    }
  
    if(nodeParm->expType != UndefinedType)
    {
        
        if(functionNodeParm->expType != nodeParm->expType && !nodeParm->declErr && !functionNode->isIO)
        {
      
            printError(25, node->lineno, functionNode->lineno, functionNode->attr.name, ConvertExpToString(functionNodeParm->expType), ConvertExpToString(nodeParm->expType), numParms);

            if(!functionNodeParm->isArray && nodeParm->isArray)
            {
                printError(36, node->lineno, functionNode->lineno, functionNode->attr.name, NULL, NULL, numParms);
            }
 
            else if(functionNodeParm->isArray && !nodeParm->isArray)
            {
                printError(28, node->lineno, functionNode->lineno, functionNode->attr.name, NULL, NULL, numParms);
            }
        }
   
        else if(!functionNodeParm->isArray && nodeParm->isArray)
        {
            printError(36, node->lineno, functionNode->lineno, functionNode->attr.name, NULL, NULL, numParms);
        }
       
        else if(functionNodeParm->isArray && !nodeParm->isArray)
        {
            printError(28, node->lineno, functionNode->lineno, functionNode->attr.name, NULL, NULL, numParms);
        }
       
    }

    numParms++;

    if(functionNodeParm->sibling != nullptr && nodeParm->sibling != nullptr)
    {
        printParmErrors(functionNode, node, functionNodeParm->sibling, nodeParm->sibling, numParms);
    }

}
