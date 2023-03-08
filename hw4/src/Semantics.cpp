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
int returnlineno;
int functionLine;

char *functionName;

Node* curFunc = nullptr;

ParmType functionReturnType;
ParmType actualReturnType;
SymbolTable symbolTable;

//function retrives symbol table
SymbolTable getSymbolTable() 
{
    return symbolTable;
}

//Function checks each node. 
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

        case StmtK:
            checkStmt(t, nErrors, nWarnings);
            break;

        case ExpK:
            checkExp(t, nErrors, nWarnings);
            break;
    }

    if(t->sibling != NULL){
        check(t->sibling, nErrors, nWarnings);
    }
}

//function analizes semantics first by checking for keyword "main"
void semanticAnalysis(TreeNode *t, int& errors, int& warnings){

    check(t, nErrors, nWarnings);

    symbolTable.applyToAll(Warninit);
    symbolTable.applyToAllGlobal(Warninit);

 
    TreeNode *mainCheck = (TreeNode*)symbolTable.lookup("main");
    if(mainCheck == NULL){
        printError(16, 0, 0, NULL, NULL, NULL, 0);
    }
    else if(mainCheck != NULL){
        if(mainCheck->nodekind == DeclK && mainCheck->subkind.decl != FuncK){

                printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
        else if(mainCheck->child[0] != NULL && mainCheck->child[0]->subkind.decl == ParamK){
            printError(16, 0, 0, NULL, NULL, NULL, 0);
        }
    }

    PrintErrorss();
    errors = nErrors;
    warnings = nWarnings;
}

//function checks to see if warnings were used.
void Warninit(std::string symbol, void* t){

    TreeNode* checkUsed;

    checkUsed = (TreeNode *)symbolTable.lookup(symbol.c_str());     

    if(!checkUsed->wasUsed && !checkUsed->isGlobal){

        if(checkUsed->subkind.decl == ParamK && !checkUsed->wasUsedErr && strcmp(checkUsed->attr.name, "main")){
            checkUsed->wasUsedErr = true;
            printError(21, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }

        else if(checkUsed->subkind.decl == FuncK && !checkUsed->wasUsedErr && strcmp(checkUsed->attr.name, "main")){
            checkUsed->wasUsedErr = true;
            printError(20, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }

        else{
            checkUsed->wasUsedErr = true;
            printError(17, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }
    }

    else if(!checkUsed->wasUsed && checkUsed->isGlobal && checkUsed->subkind.decl == FuncK){
        
        if(strcmp(checkUsed->attr.name, "main") && !checkUsed->wasUsedErr){
            checkUsed->wasUsedErr = true;

            printError(20, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
        }
    }

    else if(!checkUsed->wasUsed && checkUsed->isGlobal && !checkUsed->wasUsedErr){
         checkUsed->wasUsedErr = true;
         printError(17, checkUsed->lineno, 0, checkUsed->attr.name, NULL, NULL, 0);
    }
}

//function prints errors for arrays.
void errorsArray(TreeNode *t)
{

   TreeNode *leftNode = NULL;
   TreeNode *rightNode = NULL;

   leftNode = t->child[0];
   rightNode = t->child[1];


   if(t->child[0]->subkind.exp == IdK)
   {

      leftNode = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name);
      
      if(leftNode != NULL)
      {
         t->child[0]->expType = leftNode->expType;
         t->expType = leftNode->expType;
      }


      if(leftNode == NULL || !leftNode->isArray)
      {
         printError(15, t->lineno, 0, t->child[0]->attr.name, NULL, NULL, 0);
      }
   }
   else
   {
      printError(15, t->lineno, 0, t->child[0]->attr.name, NULL, NULL, 0);
   }
   if(t->child[1] != NULL)
   {
      if(t->child[1]->expType != Integer && t->child[1]->expType != UndefinedType)
      {

          if(t->child[1]->subkind.decl == ParamK && t->child[1]->subkind.exp != CallK && t->child[1]->expType == Void){
        
          }
          else{
            printError(14, t->lineno, 0, t->child[0]->attr.name, ExpTypetwo(t->child[1]->expType), NULL, 0);
          }
          
      }
   }
   if(t->child[1] != NULL && t->child[1]->subkind.exp == IdK)
   {
      
      if(rightNode != NULL && rightNode->isArray == true)
      {
         printError(13, t->lineno, 0, rightNode->attr.name, NULL, NULL, 0); //
      }
      if(rightNode != NULL)
      {
         t->child[1]->expType = rightNode->expType;
      }
   }

}

//function checks declaration nodes
void checkDecl(TreeNode *t, int& nErrors, int& nWarnings){
  
    if(symbolTable.depth() == 1){
        t->isGlobal = true;
    }
    else{
        t->isGlobal = false;
    }

    TreeNode *declared;
    if(t->subkind.decl != VarK && !symbolTable.insert(t->attr.name, t)){
        declared = (TreeNode*)symbolTable.lookup(t->attr.name);
        printError(0, t->lineno, declared->lineno, t->attr.name, NULL, NULL, 0);
    }

    switch(t->subkind.decl){
        
        case VarK:

            if(t->child[0] != NULL){

                for(int i = 0; i < MAXCHILDREN; i++){
                    check(t->child[i], nErrors, nWarnings);
                }
            }          

           TreeNode* exists;
           if(!symbolTable.insert(t->attr.name, t)){
               exists = (TreeNode*)symbolTable.lookup(t->attr.name);
               printError(0, t->lineno, exists->lineno, t->attr.name, NULL, NULL, 0);
           }

           if(t->sibling != NULL){

                if(t->isStatic && t->lineno == t->sibling->lineno){
                    t->sibling->isStatic = t->isStatic;
                }
            }

           if(t->child[0] != NULL){

               if(t->child[0]->subkind.exp == IdK || t->child[0]->subkind.exp == CallK){
                   printError(32, t->lineno, 0, t->attr.name, NULL, NULL, 0);
               }

               else if(t->child[0]->subkind.exp == OpK){

                   if(t->child[0] != NULL && t->child[0]->child[1] == NULL){

                       if(strcmp(t->child[0]->attr.name, "-") && !t->isArray){
                        printError(32, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                       }
                   }

                   else if(t->child[0]->child[0] != NULL && t->child[0]->child[1] != NULL){
                       checkNestOpsInit(t, t->child[0]);
                   }
               }

               if(t->expType != t->child[0]->expType){

                    if(t->expType == Char && t->child[0]->expType == CharInt){
                        ; // do nothing
                    }

                    else if(t->expType == Integer && t->child[0]->expType == CharInt){
                        char charInsert[] = "char";
                        printError(33, t->lineno, 0, t->attr.name, ExpTypetwo(t->expType), charInsert, 0);
                    }

                    else if(t->child[0]->expType == Void && t->child[0]->subkind.exp == IdK){
                       //do nothing 
                    }

                    else{
                        printError(33, t->lineno, 0, t->attr.name, ExpTypetwo(t->expType), ExpTypetwo(t->child[0]->expType), 0);
                    }
               }

               if(t->isArray && !t->child[0]->isArray){
                   printError(35, t->lineno, 0, t->attr.name, NULL, NULL, 0);
               }

               if(!t->isArray && t->child[0]->isArray){
                   printError(34, t->lineno, 0, t->attr.name, NULL, NULL, 0);
               }

               t->isInit = true;
               t->isDeclared = true;        
           }
           else{
               t->isDeclared = true;
           }

           break;

        case FuncK:

            curFunc = t;
            Flag = false;

            symbolTable.enter(t->attr.name);

            scopeDepth = false;
            functionReturnType = t->expType;
            functionName = t->attr.name;
            functionLine = t->lineno;
            
            for(int i = 0; i < MAXCHILDREN; i++){
                check(t->child[i], nErrors, nWarnings);
            }

            if(Flag == false && t->expType != Void){
                printError(19, t->lineno, 0, ExpTypetwo(functionReturnType), t->attr.name, NULL, 0);
            }

            symbolTable.applyToAll(Warninit);
            symbolTable.leave();
            curFunc = NULL;

            break;

        case ParamK:

            for(int i = 0; i < MAXCHILDREN; i++){
                
                check(t->child[i], nErrors, nWarnings);
                if(t->child[0] != NULL){
                    t->child[0]->isInit = true;
                }
            }
            t->isInit = true;
            break;
    }
}

//Function checks statement nodes
void checkStmt(TreeNode *t, int& nErrors, int& nWarnings){

    switch(t->subkind.stmt){
        case IfK:
            loop = true;
            symbolTable.enter(t->attr.name);
            loopDepth++;
            scopeDepth = false;
            for(int i = 0; i < MAXCHILDREN; i++){
                if(t->child[0]){
                    check(t->child[i], nErrors, nWarnings);
                }
            }


            if(t->child[0]->expType != Boolean && t->child[0]->subkind.exp != OpK && !t->child[0]->declErr){
                char ifStmt[] = "if";
                printError(27, t->lineno, 0, ifStmt, ExpTypetwo(t->child[0]->expType), NULL, 0 );
            }

            if(t->child[0]->isArray){
                char ifStmt[] = "if";
                printError(23, t->lineno, 0, ifStmt, NULL, NULL, 0);
            }
            
            loopDepth--;

            symbolTable.applyToAll(Warninit);

            if(loopDepth == 1){
                loop = false;
            }
            symbolTable.leave();
            scopeDepth = true;
            break;

        case ForK:
            loop = true;
            inFor = true;
            loopDepth++;
            symbolTable.enter(t->attr.name);
            scopeDepth = false;
            
            for(int i = 0; i < MAXCHILDREN; i++){
                if(t->child[i]){

                check(t->child[i], nErrors, nWarnings);
                t->child[0]->isInit = true;
                t->child[1]->isInit = true;
                }
            }

            loopDepth--;

            if(loopDepth == 1){
                loop = false;
            }

                inFor = false;
                symbolTable.applyToAll(Warninit);
                symbolTable.leave();
                scopeDepth = true;

            break;

        case WhileK:
            loop = true;
            symbolTable.enter(t->attr.name);
            loopDepth ++;
            scopeDepth = false;

            for(int i = 0; i < MAXCHILDREN; i++){
                if(t->child[i]){
                check(t->child[i], nErrors, nWarnings);

                if(i < 1){
                    if(t->child[0]->expType != Boolean && t->child[0]->subkind.exp != OpK && !t->child[0]->declErr){
                        char whileStmt[] = "while";
                        printError(27, t->lineno, 0, whileStmt, ExpTypetwo(t->child[0]->expType), NULL, 0 );
                    }

                    if(t->child[0]->isArray){
                        char whileStmt[] = "while";
                        printError(23, t->lineno, 0, whileStmt, NULL, NULL, 0);
                    }
            }
                }
            }

            loopDepth--;

            symbolTable.applyToAll(Warninit);

            if(loopDepth == 1){
                loop = false;
            }
            symbolTable.leave();
            scopeDepth = true;
            break;

        case ReturnK:

                Flag = true;
                returnlineno = t->lineno;

            check(t->child[0], nErrors, nWarnings);

            if(t->child[0] != NULL){

                actualReturnType = t->child[0]->expType;

                if(curFunc == NULL){
                    break;
                }

                else if(t->child[0]->isArray){
                    printError(10, t->lineno, 0, NULL, NULL, NULL, 0);
                }

                else if(t->child[0]->child[0] != NULL){
                    if(t->child[0]->child[0]->isArray){

                        if(strcmp(t->child[0]->attr.name, "[")){
                            printError(10, t->lineno, 0, NULL, NULL, NULL, 0);
                        }
                    }
                }
            
                if(functionReturnType == Void){
                    printError(29, returnlineno, functionLine, functionName, NULL, NULL, 0);
                }

                else if(functionReturnType != actualReturnType && actualReturnType != Void && functionReturnType != Void){

                    if(!(functionReturnType == Char && actualReturnType == CharInt)){
                        printError(31, returnlineno, functionLine, functionName, ExpTypetwo(functionReturnType), ExpTypetwo(actualReturnType), 0);
                    }
                }

                else if(functionReturnType != actualReturnType && functionReturnType != Void && t->child[0]->subkind.exp == CallK){
                    
                    if(!(functionReturnType == Char && actualReturnType == CharInt)){
                        printError(31, returnlineno, functionLine, functionName, ExpTypetwo(functionReturnType), ExpTypetwo(actualReturnType), 0);
                    }
                }
            }

            else if(t->child[0] == NULL){

                if(functionReturnType != Void){
                    printError(30, returnlineno, functionLine, functionName, ExpTypetwo(functionReturnType), NULL, 0);
                }
            }

            break;

        case BreakK:

            if(!loop){
                printError(22, t->lineno, 0, NULL, NULL, NULL, 0);
            }
            break;

        case RangeK:

            rangePos;
            range = true;

            for(int i = 0; i < MAXCHILDREN; i++){
                if(t->child[i]){
                    rangePos++;

                        if(t->child[i]->child[0] != NULL && t->child[i]->child[0]->isArray){
                            t->child[i]->child[0]->isIndexed = true;
                        }

                        else if(rangePos == 1){
                            if(t->child[0]->subkind.exp == IdK){
                                TreeNode* valFound = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name);
                                if(valFound == NULL){
                                    printError(1, t->lineno, 0, t->child[0]->attr.name, NULL, NULL, 0); 
                                    t->declErr = true;
                                }
                                else{
                                    valFound->wasUsed = true;
                                }
                            }
                        }

                    check(t->child[i], nErrors, nWarnings);

                }
            }

            range = false;
            rangePos = 0;

            break;

        case CompoundK:

            bool keepCurScope = scopeDepth;

            if(keepCurScope){
                
                symbolTable.enter("compound");
            }
            else{
                scopeDepth = true;
            }

            for(int i = 0; i < MAXCHILDREN; i++){
                check(t->child[i], nErrors, nWarnings);
            }

            if(keepCurScope){
                symbolTable.applyToAll(Warninit);
                symbolTable.leave();
            }

            break;

    }

}

//function checks expression nodes. 
void checkExp(TreeNode *t, int& nErrors, int& nWarnings){
 
    bool leftStr, rightStr, isBinary, leftArr, rightArr, leftIndx, rightIndx, leftInit, leftDecl, rightInit, rightDecl, throwError;
    leftStr = rightStr = isBinary = leftArr = rightArr = leftIndx = rightIndx = leftInit = leftDecl = rightInit = rightDecl = throwError = false;

    ExpType leftSide, rightSide, returnType, leftExpected, rightExpected, childReturnType;
    leftSide = rightSide = returnType = leftExpected = rightExpected = childReturnType = UndefinedType;

    bool rightErr, leftErr, unaryErrors;
    rightErr = leftErr = unaryErrors = false;

    TreeNode* valFound = NULL;
    TreeNode* leftNode = NULL;
    TreeNode* rightNode = NULL;

    switch(t->subkind.exp) {
        case AssignK:
        case OpK:

            if(!strcmp(t->attr.name, "<=")){

                if(t->child[0] != NULL){
                    
                    if(t->child[0]->child[0]!=NULL && !strcmp(t->child[0]->attr.name, "[")){
                        t->child[0]->child[0]->isInit = true;

                        if(t->child[0]->child[1] != NULL){
                            t->child[0]->child[1]->isInit = true;

                            if(t->child[0]->child[1]->child[0] != NULL && t->child[0]->child[1]->child[1] != NULL){

                            if(t->child[0]->child[1]->subkind.exp == OpK){
                                t->child[0]->child[1]->child[0]->isInit = true;
                                t->child[0]->child[1]->child[1]->isInit = true;
                            }
                            }
                        }

                        else if(t->child[0]->child[1]->child[0] != NULL){
                            t->child[0]->child[1]->child[0]->isInit = true;
                        }

                    }

                    else if(t->child[1] !=NULL && t->child[1]->expType == Void){

                        if(!strcmp(t->child[1]->attr.name, "<=")){
                            t->child[0]->isInit = true;
                        }

                        if(t->child[1]->subkind.exp == CallK){
                            t->child[0]->isInit = true;
                        }

                        else if(!strcmp(t->child[1]->attr.name, "[")){

                            char* lhs = strdup(t->child[0]->attr.name);
                            char* rhs = strdup(t->child[1]->child[0]->attr.name);

                            if(strcmp(lhs, rhs)){
                                t->child[0]->isInit = true;
                            }

                        }
                        else if(t->child[0]!=NULL && t->child[1]!=NULL){
    
                            if(t->child[0]->subkind.exp == IdK && !t->child[0]->isInit){
        
                                if(t->child[1]->subkind.exp == IdK){

                                    char* lhs = strdup(t->child[0]->attr.name);
                                    char* rhs = strdup(t->child[1]->attr.name);

                                    if(strcmp(lhs, rhs)){
                                        t->child[0]->isInit = true;
                                    }
                                }

                                else if(t->child[1]->subkind.exp == AssignK){
                                    checkNestAssK(t->child[1]);
                                    t->child[0]->isInit = true;
                                }
                            }
                        }

                        else{
                        //do nothing
                        }
                    }
                   
                    else {

                        if(t->child[1] != NULL && t->child[1]->child[0] != NULL){
    
                            if(t->child[1]->child[0]->subkind.exp == IdK){

                                char *c0 = strdup(t->child[0]->attr.name);
                                char *c10 = strdup(t->child[1]->child[0]->attr.name);

                                if(strcmp(c0, c10)){
                                    t->child[0]->isInit = true;
             
                                }
                            }

                            else{
                                t->child[0]->isInit = true;
                            }
                            

                        }

                        else{
                            t->child[0]->isInit = true;
                        }
                    }
                }

            }

            if(strcmp(t->attr.name, "<=")){
                if(t->child[0] != NULL){
                    t->child[0]->wasUsed = true;
                    
                }
                if(t->child[1] != NULL){
                    t->child[1]->wasUsed = true;
                }
            }

            if(!strcmp(t->attr.name, "*")){
                sizeOfArrayFlg = true;
            }

            for(int i= 0; i < MAXCHILDREN; i++){
                check(t->child[i], nErrors, nWarnings);
            }

            sizeOfArrayFlg = false;

            if(t->child[0] != NULL){
                leftNode = t->child[0];
                leftSide = leftNode->expType;
                leftArr = leftNode->isArray;

                if(leftNode->child[0] != NULL){
                    leftArr = false; 
                    leftIndx = true; 
                }
                if(leftNode->nodekind == ExpK){
                    if(leftNode->subkind.exp == CallK){
                        leftArr = false;
                    }
                    if(leftNode->subkind.exp == ConstantK){
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
                    if(rightNode->subkind.exp == CallK){
                        rightArr = false;
                    }
                    if(rightNode->subkind.exp == ConstantK){
                        rightStr = true;
                    }
                }
                isBinary = true;
            }

            getExpTypes(t->attr.name, isBinary, unaryErrors, leftExpected, rightExpected, returnType);

            if(leftSide == Void && !(leftNode->nodekind == ExpK && leftNode->subkind.exp == CallK)){
                leftErr = true;
            }
            if(rightSide == Void && !(rightNode->nodekind == ExpK && rightNode->subkind.exp == CallK)){
                rightErr = true;
            }

            if(!isBinary && !leftErr){
 
                if(leftSide != leftExpected && leftExpected != UndefinedType){

                    if(!strcmp(t->attr.name, "-")){
                        char uMinus[] = "chsign";
                        printError(9, t->lineno, 0, uMinus, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                    }

                    else{
                        printError(9, t->lineno, 0, t->attr.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                    }
                }

                else if(!strcmp(t->attr.name, "not") && leftSide != leftExpected){

                    printError(9, t->lineno, 0, t->attr.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                }

                else if(!strcmp(t->attr.name, "*") && (!leftArr && leftSide != UndefinedType)){
                    char uSizeof[] = "sizeof";
                    printError(8, t->lineno, 0, uSizeof, NULL, NULL, 0);
                } 

                if(leftArr){
                    if(strcmp(t->attr.name, "*") != 0){

                        if(!strcmp(t->attr.name, "-")){
                            char uMinus[] = "chsign";
                            printError(7, t->lineno, 0, uMinus, NULL, NULL, 0);
                        }
                        else{
                            printError(7, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                        }
                    }
                }
            }
                else{
                    if(!unaryErrors){

                        if(!strcmp(t->attr.name, "[")){
                            errorsArray(t);
                        }
                
                        else if(leftSide != rightSide && !leftErr && !rightErr){

                            if(!strcmp(ExpTypetwo(leftSide), "int") && !strcmp(ExpTypetwo(rightSide), "CharInt")){
                                char diffCharInt[] = "char";
                                 printError(2, t->lineno, 0, t->attr.name, ExpTypetwo(leftSide), diffCharInt, 0);
                            }
                            else if(!strcmp(ExpTypetwo(leftSide), "char") && !strcmp(ExpTypetwo(rightSide), "CharInt")){
                                ; //do nothing
                            }
  
                            else if(!strcmp(t->attr.name, "<=") && t->child[1]->subkind.exp == OpK){
 
                                getReturnType(t->child[1]->attr.name, isBinary, childReturnType);
                               
                                if(childReturnType != t->child[0]->expType){
                                    printError(2, t->lineno, 0, t->attr.name, ExpTypetwo(leftSide), ExpTypetwo(childReturnType), 0);
                                }

                                else if(t->child[1]->child[1] != NULL && t->child[1]->child[1]->subkind.exp == CallK){
                                    printError(2, t->lineno, 0, t->attr.name, ExpTypetwo(leftSide), ExpTypetwo(childReturnType), 0);
                                }
                            }
                            else{

                                if(t->child[0]->subkind.exp != CallK){

                                 printError(2, t->lineno, 0, t->attr.name, ExpTypetwo(leftSide), ExpTypetwo(rightSide), 0);
                                }
                                else{}
                            }
                        }
                    }


                    if(!(leftExpected == UndefinedType || rightExpected == UndefinedType)){
                        
                        if(leftExpected == CharInt || rightExpected == CharInt){

                            ;
                        }

                        else if(leftSide == rightSide && leftNode->subkind.exp == CallK && rightNode->subkind.exp == CallK){

                             TreeNode* lhs = (TreeNode*)symbolTable.lookup(t->child[0]->attr.name);
                             TreeNode* rhs = (TreeNode*)symbolTable.lookup(t->child[1]->attr.name);

                             if(lhs != NULL && rhs != NULL){

                                 if(lhs->subkind.decl == FuncK && rhs->subkind.decl == FuncK && !lhs->isIO && !rhs->isIO){
                                     if(t->child[0]->expType == Void && t->child[1]->expType == Void){
                                     printError(3, t->lineno, 0, t->attr.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                                     printError(4, t->lineno, 0, t->attr.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                     }
                                     
                                 }

                             }
                        }
                        else{

                            if(leftSide != leftExpected && !leftErr){
                                printError(3, t->lineno, 0, t->attr.name, ExpTypetwo(leftExpected), ExpTypetwo(leftSide), 0);
                            }

                            if(rightSide != rightExpected && !rightErr && rightSide != UndefinedType){

                                if(rightSide == Void && t->child[1]->subkind.exp == CallK && returnType != Boolean){
                                    printError(4, t->lineno, 0, t->attr.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                }
                                else if(rightSide != Void){
                                    printError(4, t->lineno, 0, t->attr.name, ExpTypetwo(rightExpected), ExpTypetwo(rightSide), 0);
                                }
                            }
                        }
                    }

                    if(leftArr || rightArr){

                        if(strcmp(t->attr.name, "<=") && leftExpected != UndefinedType){
                            if(!strcmp(t->attr.name, "<") || !strcmp(t->attr.name, ">") || !strcmp(t->attr.name, "=") || !strcmp(t->attr.name, "!>") || !strcmp(t->attr.name, "!<") || !strcmp(t->attr.name, "><")){
                         
                                 if(leftArr && !rightArr){
                                printError(5, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                                }

                                else if(!leftArr && rightArr){
                                printError(6, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                                }
                            }

                            else{
                            printError(7, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                            }
                        }
                        
                        else{
                            if(!strcmp(t->attr.name, "[")){
                                ;
                            }

                            else if((leftArr && !rightArr) || (!leftArr && rightArr)){

                                if(leftArr && !rightArr){
                                printError(5, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                                }

                                else if(!leftArr && rightArr){
                                    printError(6, t->lineno, 0, t->attr.name, NULL, NULL, 0);
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
                        printError(26, t->lineno, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                    }
                   }
               }
            break;

        case IdK:
            valFound = (TreeNode*)symbolTable.lookup(t->attr.name);

            if(valFound == NULL){

                if(range && rangePos == 1){
                    t->isDeclared = true;
                }

                else{
                    printError(1, t->lineno, 0, t->attr.name, NULL, NULL, 0); 
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

                            if(!strcmp(t->attr.name, "main")){
                                printError(12, t->lineno, 0, t->attr.name, NULL, NULL, 0);  
                            }
                            else{
                                char intExpect[] = "int";
                                printError(26, t->lineno, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                            }
                        }

                    }

                    if(rangePos >= 1 && !valFound->isInit){
                        if(valFound->isDeclared == true){

                            if(!valFound->isInit && !valFound->warningReported && !valFound->isStatic && !valFound->isGlobal){

                                if(!t->isInit){
                                    valFound->warningReported = true;
                                    valFound->wasUsed = true;
                                    printError(18, t->lineno, 0, t->attr.name, NULL, NULL, 0);
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
                        printError(24, t->lineno, 0, NULL, NULL, NULL, rangePos);
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
                        printError(18, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                     }
                     else{
                         valFound->isInit = true;
                     }
                 }
                 }

                if(valFound->subkind.decl == FuncK){
                    printError(12, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                    valFound->wasUsed = true;
                    break;
                }
                else{
                    t->expType = valFound->expType;
                    t->isArray = valFound->isArray;
                    t->isGlobal = valFound->isGlobal;
                    t->isStatic = valFound->isStatic;

                    if(!range && valFound->subkind.decl != FuncK){
                    valFound->wasUsed = true;
                    }
                }

                if(t->child[0] != NULL){
                    check(t->child[0], nErrors, nWarnings);
                    if(t->child[0]->expType == Void && !(t->child[0]->nodekind == ExpK && t->child[0]->subkind.exp == CallK)){

                        break;
                    }
                    if(!t->isArray){

                        break;
                    }
                    else{

                        if(t->child[0]->expType != Integer){
                            printError(14, t->lineno, 0, t->attr.name, ExpTypetwo(t->child[0]->expType), NULL, 0);
                        }
 
                        if(t->child[0]->isArray && t->child[0]->child[0] == NULL){
                            printError(13, t->lineno, 0, t->child[0]->attr.name, NULL, NULL, 0);
                        }
                    }
                }
            }
            break;

        case CallK:
            int paramCount = 1;
            TreeNode* funcFound;

            if(t->subkind.exp == CallK){
                funcFound = (TreeNode*)symbolTable.lookup(t->attr.name);
                if(funcFound == NULL){
                    printError(1, t->lineno, 0, t->attr.name, NULL, NULL, 0);  
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


                if(funcFound->subkind.decl != FuncK){
                    printError(11, t->lineno, 0, t->attr.name, NULL, NULL, 0);
                }
                

                else if(range){

                    if(inFor){

                        if(t->expType != Integer)
                        {

                            if(!strcmp(t->attr.name, "main")){
                                printError(12, t->lineno, 0, t->attr.name, NULL, NULL, 0);                               
                            }
                            else{
                                char intExpect[] = "int";
                                printError(26, t->lineno, 0, intExpect, ExpTypetwo(t->expType), NULL, rangePos);
                            }
                        }
                    }
                }

                else{

                    if(funcFound->child[0] != NULL && t->child[0] != NULL){
                       parameterErrors(funcFound, t, funcFound->child[0], t->child[0], paramCount);
                    }

                    else if(funcFound->child[0] == NULL && t->child[0] != NULL){
                        printError(38, t->lineno, funcFound->lineno, t->attr.name, NULL, NULL, 0);
                    }

                    else if(funcFound->child[0] != NULL && t->child[0] == NULL){
                        printError(37, t->lineno, funcFound->lineno, t->attr.name, NULL, NULL, 0);
                    }
                }
            }
      
            break;        
    }

}

//function gets all expected types. 
void getExpTypes(const char* strng, bool isBinary, bool &unaryErrors, ExpType &left, ExpType &right, ExpType &rightT){

    std::string unaryOps[6] = {"not", "*", "?", "-", "--", "++"};

    std::string binaryOps[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", "!<", "!>", "==", "!=", "=", "and", "or"};
    std::string op(strng);
    unaryErrors = false;

    if(!isBinary){

        for(int i = 0; i < 6; i++){

            if(op == unaryOps[i]){

                if(i == 0){
                    left = right = rightT = Boolean;
                }

                if(i == 1){
                    left = right = UndefinedType;
                    rightT = Integer;
                }

                if(i >= 2){
                    left = right = rightT = Integer;
                }
            }
        }
    }
    else{

        for(int i = 0; i < 18; i++){

            if(op == binaryOps[i]){

                if(i >= 0 && i <= 8){
                    left = right = rightT = Integer;
                    unaryErrors = true;
                }
  
                if(i >= 9 && i <= 12){
                    left = right = CharInt; 
                    rightT = Boolean;
                }

                if(i >= 13 && i <=14){
                    left = right = UndefinedType;
                    rightT = Boolean;
                }

                if(i == 15){
                    left = right = UndefinedType;
                    rightT = Boolean;
                }

                if(i >= 16){
                    left = right = rightT = Boolean;
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

void getReturnType(const char* strng, bool isBinary, ExpType &rightT){

    std::string unaryOps[6] = {"not", "*", "?", "-", "--", "++"};

    std::string binaryOps[18] = {"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", ">", "<", "!<", "!>", "==", "!=", "=", "and", "or"};
    std::string op(strng);

    if(!isBinary){

        for(int i = 0; i < 6; i++){

            if(op == unaryOps[i]){

                if(i == 0){
                    rightT = Boolean;
                }
                
                if(i == 1){
                    
                    rightT = Integer;
                }

                if(i >= 2){
                    rightT = Integer;
                }
            }
        }
    }
    else{

        for(int i = 0; i < 18; i++){

            if(op == binaryOps[i]){

                if(i >= 0 && i <= 8){
                    rightT = Integer;
                }

                if(i >= 9 && i <= 12){
                    rightT = Boolean;
                }

                if(i >= 13 && i <=14){
                    rightT = Boolean;
                }

                if(i == 15){
                    rightT = Boolean;
                }

                if(i >= 16){
                    rightT = Boolean;
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
            //printError(32, node->lineno, 0, node->nodeAttributes.name, nullptr, nullptr, 0);
        }
    }

    else if(child->m_childernNodes[0] != nullptr && child->m_childernNodes[1] == nullptr)
    {
  
        if(child->nodeAttributes.name == "not")
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Initializer for variable " + node->nodeAttributes.name + "is not a constant expression.");
            //printError(32, node->lineno, 0, node->nodeAttributes.name, nullptr, nullptr, 0);
        }
    }
}

void analyzeNestedAssign(Node* child)
{
    if(child->m_childernNodes[0] != nullptr)
    {
        child->m_childernNodes[0]->m_isInit = true;
    }
}
//Node *funcFound, Node *t, TreeNode *ffParm, TreeNode *tParm, int paramCount
//Node *funcFound, Node* node, Node* funcParm, Node* nodeParm, int paramCount
void parameterErrors(Node* funcFound, Node* node, Node* funcParm, Node* nodeParm, int paramCount)
{
    

    if(funcParm->m_siblingNode == nullptr && nodeParm->m_siblingNode != nullptr)
    {
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Too many parameters passed for function '" + funcFound->nodeAttributes.name + "' declared on line " + funcFound->m_lineNumber + ".");
        //printError(38, t->lineno, funcFound->lineno, node->attr.name, nullptr, NULL, 0);
    }

    else if(funcParm->m_siblingNode != nullptr && nodeParm->m_siblingNode == nullptr)
    {
        EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Too few parameters passed for function '" + funcFound->nodeAttributes.name + "' declared on line " + funcFound->m_lineNumber + ".");
        //printError(37, t->lineno, funcFound->lineno, t->attr.name, NULL, NULL, 0);
    }
  
    if(nodeParm->m_parmType != ParmType::UNDEFINED)
    {
        
        if(funcParm->m_parmType != nodeParm->m_parmType && !nodeParm->m_isDeclError && !funcFound->m_isIO)
        {
            //msg << "Expecting type " << Data::typeToString(funcParmType) << " in parameter " << parmCount << " of call to '" << func->getName() << "' declared on line " << func->getLineNum() <<" but got type " << Data::typeToString(callParmType) << ".";
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting type " + funcFound->nodeAttributes.name + " in parameter " + paramCount + ExpTypetwo(funcParm->m_parmType) + " of call to '" + ExpTypetwo(nodeParm->m_parmType) + "' declared on line" + node->m_lineNumber + "but got type" + ExpTypetwo(nodeParm->m_parmType) + ".");
            //printError(25, t->lineno, funcFound->lineno, funcFound->attr.name, ExpTypetwo(funcParm->expType), ExpTypetwo(nodeParm->expType), paramCount);

            if(!funcParm->m_isArray && nodeParm->m_isArray)
            {
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Not expecting array in parameter " + paramCount + " of call to '" + ExpTypetwo(funcParm->m_parmType) + "' declared on line" + node->m_lineNumber + ".");
                //printError(36, t->lineno, funcFound->lineno, funcFound->attr.name, NULL, NULL, paramCount);
            }
 
            else if(funcParm->m_isArray && !nodeParm->m_isArray)
            {
                EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting array in parameter " + paramCount + " of call to '" + ExpTypetwo(funcParm->m_parmType) + "' declared on line" + node->m_lineNumber + ".");
                //printError(28, t->lineno, funcFound->lineno, funcFound->attr.name, NULL, NULL, paramCount);
            }
        }
   
        else if(!funcParm->m_isArray && nodeParm->m_isArray)
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Not expecting array in parameter " + paramCount + " of call to '" + ExpTypetwo(funcParm->m_parmType) + "' declared on line" + node->m_lineNumber + ".");
            //printError(36, t->lineno, funcFound->lineno, funcFound->attr.name, NULL, NULL, paramCount);
        }
       
        else if(funcParm->m_isArray && !nodeParm->m_isArray)
        {
            EmitDiagnostics::Error::emitGenericError(node->m_lineNumber, "Expecting array in parameter " + paramCount + " of call to '" + ExpTypetwo(funcParm->m_parmType) + "' declared on line" + node->m_lineNumber + ".");
            //printError(28, t->lineno, funcFound->lineno, funcFound->attr.name, NULL, NULL, paramCount);
        }
       
    }

    paramCount++;

    if(funcParm->m_siblingNode != nullptr && nodeParm->m_siblingNode != nullptr)
    {
        parameterErrors(funcFound, node, funcParm->m_siblingNode, nodeParm->m_siblingNode, paramCount);
    }

}
