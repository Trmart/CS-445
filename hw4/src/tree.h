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

#ifndef _SYNTAXTREE_H_
#define _SYNTAXTREE_H_

#include "scanType.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAXCHILDREN 3

//Kinds of operators
//these are the token numbers for the operators same as in flex
typedef int OpKind;

//Kinds of statements
typedef enum {DeclK, StmtK, ExpK} NodeKind;

//Subkinds of Declarations
typedef enum {VarK, FuncK, ParamK} DeclKind;

// Subkinds of Statements
typedef enum {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK} StmtKind;

//Subkinds of Expressions
typedef enum {OpK, ConstantK, IdK, AssignK, InitK, CallK} ExpKind;

//ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
typedef enum {Void, Integer, Boolean, Char, CharInt, Equal, UndefinedType} ExpType;

//What kind of scoping is used? (decided during typing)
typedef enum {None, Local, Global, Parameter, LocalStatic} VarKind;

typedef struct treeNode{
    // connectivity in the tree
    struct treeNode *child[MAXCHILDREN];        // children of the node
    struct treeNode *sibling;                   // siblings for the node

    //what kind of node
    int lineno;                                 // lineno relevant to this node
    NodeKind nodekind;                          // type of this node
    TokenData *thisTokenData;

    union                                       //subtype of type
    {
        DeclKind decl;                          // used when DeclK
        StmtKind stmt;                          // used when StmtK
        ExpKind exp;                            // used when ExpK
    } subkind;

    union                                       // relevant data to type -> attr
    {
        OpKind op;                              // type of token (same as in bison)
        int value;                              // used when an integer constant or boolean
        unsigned char cvalue;                   // used when a character
        char *string;                           // used when a string constant
        char *name;                             // used when IdK
    } attr;

    ExpType expType;                            // used when ExpK for type checking
    bool isArray;                               // is this an array
    bool isStatic;                              // is staticly allocated?
    bool isGlobal;                              //is global
    bool isInit;                                //is ID initialized
    bool warningReported;                       //is warning reported
    bool wasUsed;                               // was variable used?
    bool isDeclared;                            // is variable declared.
    bool declErr;
    bool wasUsedErr; //track if wasUsedErr was already printed for t
    bool isIndexed; // track if an array is currently being indexed
    bool isIO;      //set to avoid IO parameter errors
} TreeNode;


TreeNode *addSibling(TreeNode *t, TreeNode *s);
void setType(TreeNode *t, ExpType type);
TreeNode *newDeclNode(DeclKind kind, TokenData* token);
TreeNode *newStmtNode(StmtKind kind, TokenData* token);
TreeNode *newExpNode(ExpKind kind, TokenData* token); 
void printTree(TreeNode *tree, int nsiblings, bool alltype);
void printWhiteSpace(int WS);
void printExp(ExpType tree);
TreeNode *newDeclNodeIO(DeclKind kind);

#endif

