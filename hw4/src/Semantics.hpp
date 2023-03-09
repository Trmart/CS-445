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

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.hpp"
#include "symbolTable.hpp"
#include "scanType.hpp"
#include <iostream>
#include <string>

//analyzers
void analyze(Node* node, int& nErrors, int& nWarnings);
void semanticAnalysis(Node* node, int& errors, int& warnings);
void analyzeDecl(Node* node, int& nErrors, int& nWarnings);
void analyzeStmt(Node* node, int& nErrors, int& nWarnings);
void analyzeExp(Node* node, int& nErrors, int& nWarnings);
void analyzeNestedAssign(Node* child);
void analyzeNestedOperators(Node* node, Node* child);


//Declaration analyzers
void analyzeVar(Node* node, int& nErrors, int& nWarnings);
void analyzeFunc(Node* node, int& nErrors, int& nWarnings);
void analyzeParam(Node* node, int& nErrors, int& nWarnings);

//Statement analyzers
void analyzeNullStmt(Node* node, int& nErrors, int& nWarnings);
void analyzeIf(Node* node, int& nErrors, int& nWarnings);
void analyzeWhile(Node* node, int& nErrors, int& nWarnings);
void analyzeFor(Node* node, int& nErrors, int& nWarnings);
void analyzeCompound(Node* node, int& nErrors, int& nWarnings);
void analyzeReturn(Node* node, int& nErrors, int& nWarnings);
void analyzeBreak(Node* node, int& nErrors, int& nWarnings);
void analyzeRange(Node* node, int& nErrors, int& nWarnings);


//Expression analyzers
void analyzeOp(Node* node, int& nErrors, int& nWarnings);
void analyzeConst(Node* node, int& nErrors, int& nWarnings);
void analyzeId(Node* node, int& nErrors, int& nWarnings);
void analyzeAssign(Node* node, int& nErrors, int& nWarnings);
void analyzeInit(Node* node, int& nErrors, int& nWarnings);


//getters
void getReturnType(const std::string op, bool isBinary, ParmType &childReturnType);
SymbolTable getSymbolTable();
void getExpTypes(const std::string op, bool isBinary, bool &unaryErrors, ParmType &left, ParmType &right, ParmType &rightT);


//helper functions
void analyzeWarnings(std::string, void*);
std::string ConvertParmToString(ParmType type);
void parameterErrors(Node *funcFound, Node* node, Node* funcParm, Node* nodeParm, int paramCount);


//printers
void printArrayErrors(Node* node); 
//void printError(int errCode, int linenum, int explaineno, char* s1, char* s2, char* s3, int i);

#endif