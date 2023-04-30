/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW7
Dr. Wilder
DUE: 5/5/2023

FILE: codeGeneration.h
DESC:  Code generation functions
*/

#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include "AST.h"
#include "symbolTable.h"

// generate code and emit init and start
void generateCode(TreeNode* node, char* inputFile);
void emitAbout(char* inputFile);
void emitIO(TreeNode* node);
void emitInput(TreeNode* node);
void emitInit(TreeNode* node);
void emitStart(TreeNode* node);

// emit decl functions
void emitDecl(TreeNode* node);
void emitFunc(TreeNode* node);
void emitVar(TreeNode* node);
void emitParam(TreeNode* node);

// emit exp functions
void emitExp(TreeNode* node);
void emitAssign(TreeNode* node, TreeNode* lhs, TreeNode* rhs);
void emitOp(TreeNode* node, TreeNode* lhs, TreeNode* rhs);
void emitCall(TreeNode* node, TreeNode* callLookUp);
void emitConstant(TreeNode* node);
void emitId(TreeNode* node);

// emit stmt functions
void emitStmt(TreeNode* node);
void emitIf(TreeNode* node, int elseLoc);
void emitWhile(TreeNode* node, int whileLoc, int tmpBloc, int whileSkp, int ldaLoc);
void emitReturn(TreeNode* node);
void emitBreak(TreeNode* node);
void emitFor(TreeNode* node, int forOff, int forLoc, int forSkp);
void emitRange(TreeNode* node);
void emitCompound(TreeNode* node);

// emit type functions
void emitGlobAndStats(TreeNode* node);


#endif  //CODEGENERATION_H