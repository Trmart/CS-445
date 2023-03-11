/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: AST.h
DESC: Abstract Syntax Tree
*/

#ifndef _AST_H_
#define _AST_H_

#include "scanType.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAXCHILDREN 3


typedef int OpKind;


typedef enum 
{   
    DeclK, 
    StmtK, 
    ExpK

}NodeKind;


typedef enum 
{
    VarK, 
    FuncK, 
    ParamK
}DeclKind;


typedef enum 
{
    NullK, 
    IfK, 
    WhileK, 
    ForK, 
    CompoundK, 
    ReturnK, 
    BreakK, 
    RangeK
}StmtKind;


typedef enum 
{
    OpK, 
    ConstantK, 
    IdK, 
    AssignK, 
    InitK, 
    CallK
}ExpKind;


typedef enum 
{
    Void, 
    Integer, 
    Boolean, 
    Char, 
    CharInt, 
    UndefinedType
} ExpType;


typedef enum 
{
    None, 
    Local, 
    Global, 
    Parameter, 
    LocalStatic
} VarKind;

typedef struct treeNode
{

    union 
    {
        DeclKind decl;
        StmtKind stmt;
        ExpKind exp; 
    } subkind;

    union                                      
    {
        OpKind op;                              
        int value;                             
        unsigned char cvalue;
        char *string;
        char *name;
    } attr;


    struct treeNode* child[MAXCHILDREN];        
    struct treeNode* sibling;                   


    int lineno;                                 
    
    NodeKind nodekind;                          
    
    TokenData *thisTokenData;
    
    ExpType expType;
    
    bool isArray;
    
    bool isStatic;
    
    bool isGlobal;
    
    bool isInit;
    
    bool warningReported;
    
    bool wasUsed;
    
    bool isDeclared;
    
    bool declErr;
    
    bool wasUsedErr;
    
    bool isIndexed;
    
    bool isIO;     

} TreeNode;

//Node creation functions
TreeNode* addSibling(TreeNode* node, TreeNode *sibling);
TreeNode* newDeclNode(DeclKind kind, TokenData* token);
TreeNode* newStmtNode(StmtKind kind, TokenData* token);
TreeNode* newExpNode(ExpKind kind, TokenData* token); 
TreeNode *newDeclNodeIO(DeclKind kind);

//print functions
void printAST(TreeNode *ast, int numsiblings, bool isShowingTypes);
void printTabs(int numTabs);
void printExp(ExpType type);

void printStmtNode(TreeNode* tree, bool isShowingTypes);
void printDeclNode(TreeNode* tree, bool isShowingTypes);
void printExpNode(TreeNode* tree, bool isShowingTypes);
void printConstantNode(TreeNode* tree, bool isShowingTypes);
void printOpNode(TreeNode* tree, bool isShowingTypes);


//setters 
void setType(TreeNode* node, ExpType type);



#endif

