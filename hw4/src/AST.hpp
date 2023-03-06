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

#ifndef AST_H
#define AST_H

#include "scanType.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <vector>

#define MAXCHILDREN 3


class Node
{
    public: 
        //Operator Types 
        //these are the token numbers for the operators same as in flex
        typedef int OpKind;

        //Node Types
        enum NodeType
        {
            DECLARATION, 
            STATEMENT, 
            EXPRESSION
        }; 

        //Declaration Types
        enum DeclarationType
        {
            VARIABLE, 
            FUNCTION, 
            PARAMETER
        };

        // Statement Types
        enum StatementType
        {
            NULLTYPE, 
            IF, 
            WHILE, 
            FOR, 
            COMPOUND, 
            RETURN, 
            BREAK, 
            RANGE
        };

        //Expression Types
        enum ExpressionType
        {
            OP, 
            CONSTANT, 
            IDENTIFIER, 
            ASSIGN, 
            INIT, 
            CALL
        };

        //ReturnType is used for function return type checking 
        enum ReturnType
        {
            VOID, 
            INTEGER, 
            BOOL, 
            CHAR, 
            CHARINT, 
            EQUAL, 
            UNDEFINED
        };

        //What type of scope is the variable in? (decided during typing)
        enum VariableType
        {
            None, Local, Global, Parameter, LocalStatic
        };

        union nodeData
        {
            DeclarationType declaration; 
            StatementType statement; 
            ExpressionType expression; 
        };

        union nodeAttributes
        {
            int intVal; 
            char charVal; 
            std::string stringVal; 
            bool boolVal; 
            OpKind op; 
            std::string name; 
        };
        

        //Node Functions
        void addSiblingNode(Node* sibling, Node* newSibling);
        void setType(Node *t, ExpType type);
        Node* newDeclNode(DeclarationType type, TokenData* token);
        Node* newStmtNode(StmtKind type, TokenData* token);
        Node* newExpNode(ExpressionType type, TokenData* token); 
        Node *newDeclNodeIO(DeclarationType kind);
        
        
        //printers
        void printAST(Node *tree, int numSiblings, bool alltype);
        void printOutputTabs(const int numtabs);
        void printExpression(ExpressionType expType);

        //getters
        ExpressionType getExpType() const {return m_expType;}
        NodeType getNodeType() const {return m_nodeType;}
        Node* getSiblingNode() const {return m_siblingNode;}
        int getLineNum() const {return m_lineNumber;}
        bool getIsArray()   const {return m_isArray;}
        bool getIsStatic() const {return m_isStatic;}
        bool getIsGlobal() const {return m_isGlobal;}
        bool getIsInit() const {return m_isInitialized;}
        bool getWarningReported() const {return m_isWarningReported;}
        bool getWasUsed() const {return m_isUsed;}
        bool getIsDeclared() const {return m_isDeclared;}
        bool getDeclErr() const {return m_isDeclError;}
        bool getWasUsedErr() const {return m_isUsedError;}
        bool getIsIndexed() const {return m_isIndexed;}
        bool getIsIO() const {return m_isIO;}

        //setters
        void setExpType(ExpressionType type);
        void setNodeType(NodeType type);
        void setLineNum(int lineNum);
        void setIsArray(bool isArray);
        void setIsStatic(bool isStat);
        void setIsGlobal(bool isGlobal);
        void setIsInit(bool isInit);
        void setWarningReported(bool isReported);
        void setWasUsed(bool isUsed);
        void setIsDeclared(bool isDeclared);
        void setDeclErr(bool isError);
        void setWasUsedErr(bool isError);
        void setIsIndexed(bool isIndexed);
        void setIsIO(bool isIO);
    
    protected: 
        
        //expression type
        ExpressionType m_expType;      
        
        //sibling node
        Node* m_siblingNode;
        
        //child nodes
        std::vector<Node*> m_childernNodes[MAXCHILDREN];

        //Node Type
        NodeType m_nodeType;
        
        // is this an array
        bool m_isArray;
        // is the variable static
        bool m_isStatic;
        // is the variable global
        bool m_isGlobal;
        // is the variable initialized
        bool m_isInitialized;
        // is a warning reported
        bool m_isWarningReported;
        // was the variable used after initialization
        bool m_isUsed;
        //is the variable declared
        bool m_isDeclared;

        int lineNumber; //line number of the node
        


        //error flags
        bool m_isDeclError;
        
        bool m_isUsedError;
        
        bool m_isIndexed;
        
        bool m_isIO; 

}

// //Kinds of operators
// //these are the token numbers for the operators same as in flex
// typedef int OpKind;

// //Kinds of statements
// typedef enum {DeclK, StmtK, ExpK} NodeKind;

// //Subkinds of Declarations
// typedef enum {VarK, FuncK, ParamK} DeclKind;

// // Subkinds of Statements
// typedef enum {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK} StmtKind;

// //Subkinds of Expressions
// typedef enum {OpK, ConstantK, IdK, AssignK, InitK, CallK} ExpKind;

// //ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
// typedef enum {Void, Integer, Boolean, Char, CharInt, Equal, UndefinedType} ExpType;

// //What kind of scoping is used? (decided during typing)
// typedef enum {None, Local, Global, Parameter, LocalStatic} VarKind;

// typedef struct treeNode
// {
//     // connectivity in the tree
//     struct treeNode *child[MAXCHILDREN];        // children of the node
//     struct treeNode *sibling;                   // siblings for the node

//     //what kind of node
//     int lineno;                                 // lineno relevant to this node
//     NodeKind nodekind;                          // type of this node
//     TokenData *thisTokenData;

//     union                                       //subtype of type
//     {
//         DeclKind decl;                          // used when DeclK
//         StmtKind stmt;                          // used when StmtK
//         ExpKind exp;                            // used when ExpK
//     } subkind;

//     union                                       // relevant data to type -> attr
//     {
//         OpKind op;                              // type of token (same as in bison)
//         int value;                              // used when an integer constant or boolean
//         unsigned char cvalue;                   // used when a character
//         char *string;                           // used when a string constant
//         char *name;                             // used when IdK
//     } attr;

//     ExpType expType;                            // used when ExpK for type checking
//     bool isArray;                               // is this an array
//     bool isStatic;                              // is staticly allocated?
//     bool isGlobal;                              //is global
//     bool isInit;                                //is ID initialized
//     bool warningReported;                       //is warning reported
//     bool wasUsed;                               // was variable used?
//     bool isDeclared;                            // is variable declared.
//     bool declErr;
//     bool wasUsedErr; //track if wasUsedErr was already printed for t
//     bool isIndexed; // track if an array is currently being indexed
//     bool isIO;      //set to avoid IO parameter errors
// } TreeNode;


// TreeNode *addSibling(TreeNode *t, TreeNode *s);
// void setType(TreeNode *t, ExpType type);
// TreeNode *newDeclNode(DeclKind kind, TokenData* token);
// TreeNode *newStmtNode(StmtKind kind, TokenData* token);
// TreeNode *newExpNode(ExpKind kind, TokenData* token); 
// void printTree(TreeNode *tree, int nsiblings, bool alltype);
// void printWhiteSpace(int WS);
// void printExp(ExpType tree);
// TreeNode *newDeclNodeIO(DeclKind kind);

#endif /* AST_H */

