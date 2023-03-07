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

#ifndef SEMANTIC 
#define SEMANTIC

#include "AST.h"
#include "symbolTable.hpp"
#include "scanType.h"

SymbolTable returnSymbolTable();
void check(TreeNode *t, int& nErrors, int& nWarnings);
void semanticAnalysis(TreeNode *t, int& errors, int& warnings);
void Warninit(std::string, void*);
void errorsArray(TreeNode *t);
void checkDecl(TreeNode *t, int& nErrors, int& nWarnings);
void checkStmt(TreeNode *t, int& nErrors, int& nWarnings);
void checkExp(TreeNode *t, int& nErrors, int& nWarnings);
void getExpTypes(const char* string, bool isBinary, bool &unaryErrors, ExpType &left, ExpType &right, ExpType &rightT);
char* ExpTypetwo(ExpType type);
void printError(int errCode, int linenum, int explaineno, char* s1, char* s2, char* s3, int i);
void parameterErrors(TreeNode *funcFound, TreeNode *t, TreeNode *ffParm, TreeNode *tParm, int paramCount);
void checkNestAssK(TreeNode *c1);
void getReturnType(const char* string, bool isBinary, ExpType &childReturnType);
void checkNestOpsInit(TreeNode *t, TreeNode* child);

#endif