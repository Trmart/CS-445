/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW5
Dr. Wilder
DUE: 4/2/2023

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


    struct treeNode* child[MAXCHILDREN]; //array of children        
    struct treeNode* sibling; //sibling node pointer                   


    int lineno; //line number of token in source code                                
    
    NodeKind nodekind;  //decl, stmt, exp                        
    
    TokenData *thisTokenData; //token data for this node
    
    ExpType expType; //type of expression
    
    bool isArray; //is this an array
    
    bool isStatic; //is this static
    
    bool isGlobal; //is this global
    
    bool isInit; //is the identifier already initialized
    
    bool warningReported; //has a warning been reported for this node
    
    bool wasUsed; //was the identifier used
    
    bool isDeclared; //was the identifier declared
    
    bool declErr; //was there an error in the declaration
    
    bool wasUsedErr; //was there an error in the use
    
    bool isIndexed; //is this an indexed variable, for arrays
    
    bool isIO; //is this an IO function

    //memory information
    int memorySize; //size of memory for -M option
    int memoryOffset; //offset of memory for -M option
    VarKind memoryType; //type of memory for -M option
    int arraySize; //size of array for -M option  

} TreeNode;


//Node creation functions
TreeNode* addSibling(TreeNode* node, TreeNode* sibling);
TreeNode* newDeclNode(DeclKind kind, TokenData* token);
TreeNode* newStmtNode(StmtKind kind, TokenData* token);
TreeNode* newExpNode(ExpKind kind, TokenData* token); 
TreeNode* newDeclNodeIO(DeclKind kind);

//print functions
void printAST(TreeNode* ast, int numsiblings, bool isShowingTypes);
void printTabs(int numTabs);
void printExp(ExpType type);
void printStmtNode(TreeNode* tree, bool isShowingTypes);
void printDeclNode(TreeNode* tree, bool isShowingTypes);
void printExpNode(TreeNode* tree, bool isShowingTypes);
void printConstantNode(TreeNode* tree, bool isShowingTypes);
void printOpNode(TreeNode* tree, bool isShowingTypes);
void printMemoryTypes(VarKind var); 


//setters 
void setType(TreeNode* node, ExpType type);


#endif /* _AST_H_ */

