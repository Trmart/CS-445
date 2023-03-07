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

SymbolTable returnSymbolTable();
void check(Node *t, int& nErrors, int& nWarnings);
void semanticAnalysis(Node *t, int& errors, int& warnings);
void Warninit(std::string, void*);
void errorsArray(Node *t);
void checkDecl(Node *t, int& nErrors, int& nWarnings);
void checkStmt(Node *t, int& nErrors, int& nWarnings);
void checkExp(Node *t, int& nErrors, int& nWarnings);
void getExpTypes(const char* string, bool isBinary, bool &unaryErrors, Node::ExpressionType &left, Node::ExpressionType &right, Node::ExpressionType &rightT);
char* ExpTypetwo(Node::ExpressionType type);
void printError(int errCode, int linenum, int explaineno, char* s1, char* s2, char* s3, int i);
void parameterErrors(Node *funcFound, Node *t, Node *ffParm, Node *tParm, int paramCount);
void checkNestAssK(Node *c1);
void getReturnType(const char* string, bool isBinary, Node::ExpressionType &childReturnType);
void checkNestOpsInit(Node *t, Node* child);

#endif