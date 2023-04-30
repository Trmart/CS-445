/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW7
Dr. Wilder
DUE: 5/5/2023

FILE: semantic.h
DESC:  Semantic analysis functions
*/

#ifndef SEMANTIC 
#define SEMANTIC

#include "AST.h"
#include "symbolTable.h"
#include "scanType.h"

//semantic analysis functions
void analyze(TreeNode* node, int& nErrors, int& nWarnings);
void semanticAnalysis(TreeNode* node, int& errors, int& warnings);
void analyzeNestedAssign(TreeNode* child);
void analyzeNestedOpInitialization(TreeNode* node, TreeNode* child);


//Declaration analyzers
void analyzeDecl(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeVar(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeFunc(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeParam(TreeNode* node, int& nErrors, int& nWarnings);


//Statement analyzers
void analyzeStmt(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeIf(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeWhile(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeFor(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeCompound(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeReturn(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeBreak(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeRange(TreeNode* node, int& nErrors, int& nWarnings);

//Expression analyzers
void analyzeExp(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeCall(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeConst(TreeNode* node, int& nErrors, int& nWarnings);
void analyzeId(TreeNode* node, TreeNode* valueFound, int& nErrors, int& nWarnings);
void analyze_Op_and_Assign(TreeNode* node,  TreeNode* leftNode, TreeNode* rightNode,  int& nErrors, int& nWarnings);

//getters 
SymbolTable getSymbolTable();
void getExpTypes(const char* string, bool isBinary, bool &unaryErrors, ExpType &left, ExpType &right, ExpType &rightT);
void getReturnType(const char* string, bool isBinary, ExpType &childReturnType);

//printers
void printError(int errCode, int linenum, int explaineno, char* s1, char* s2, char* s3, int i);
void printArrayErrors(TreeNode* node);
void printParmErrors(TreeNode* functionNode, TreeNode* node, TreeNode* functionNodeParm, TreeNode* nodeParm, int numParms);


//helper functions
void initializeWarningMessages(std::string, void*);
char* ConvertExpToString(ExpType type);

#endif