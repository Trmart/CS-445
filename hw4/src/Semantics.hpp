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


//getters
void getReturnType(const std::string str, bool isBinary, ExpressionType &childReturnType);
SymbolTable getSymbolTable();
void getExpTypes(const std::string str, bool isBinary, bool &unaryErrors, ExpressionType &left, ExpressionType &right, ExpressionType &rightT);


//helper functions
void analyzeWarnings(std::string, void*);
std::string ConvertParmToString(ParmType type);
void parameterErrors(Node *funcFound, Node* node, Node* funcParm, Node* nodeParm, int paramCount);


//printers
void printArrayErrors(Node* node); 
//void printError(int errCode, int linenum, int explaineno, char* s1, char* s2, char* s3, int i);

#endif