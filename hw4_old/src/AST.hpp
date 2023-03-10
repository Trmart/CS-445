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
#include <stdlib.h>
#include <string>

#define MAXCHILDREN 3



//Node Types
enum NodeType
{
    T_DECLARATION, 
    T_STATEMENT, 
    T_EXPRESSION
}; 

//Declaration Types
enum DeclarationType
{
    T_VARIABLE, 
    T_FUNCTION, 
    T_PARAMETER
};

// Statement Types
enum StatementType
{
    T_NULLSTMT, 
    T_IF, 
    T_WHILE, 
    T_FOR, 
    T_COMPOUND, 
    T_RETURN, 
    T_BREAK, 
    T_RANGE
};

//Expression Types (ExpKind)
enum ExpressionType 
{
    T_OP, 
    T_CONSTANT, 
    T_IDENTIFIER, 
    T_ASSIGN, 
    T_INIT, 
    T_CALL
};

//ParmType is used for function return type checking 
enum ParmType 
{
    T_VOID, 
    T_INTEGER, 
    T_BOOL, 
    T_CHAR, 
    T_CHARINT, 
    T_EQUAL, 
    T_UNDEFINED
};

//What type of scope is the variable in? (decided during typing)
enum VariableType
{
    T_NONE, T_LOCAL, T_GLOBAL, T_PARM, T_LOCAL_STATIC
};

//Operator Types 
//these are the token numbers for the operators same as in flex
typedef int OpKind;

struct Node
{

    union
    {
        DeclarationType declaration; 
        StatementType statement; 
        ExpressionType expression; 
    }nodeSubType;

    union
    {
        int intVal; 
        char charVal; 
        std::string stringVal; 
        bool boolVal; 
        OpKind op; 
        std::string name; 
    }nodeAttributes;
    
    //expression type
    ParmType m_parmType;      
    
    //sibling node
    Node* m_siblingNode;
    
    //child nodes
    Node* m_childernNodes[MAXCHILDREN];

    //Node Type
    NodeType m_nodeType;

    //Token Data
    TokenData* m_tokenData; 
    
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
    //line number of the node
    int m_lineNumber; 
    


    //error flags
    bool m_isDeclError;
    
    bool m_isUsedError;
    
    bool m_isIndexed;
    
    bool m_isIO; 

}; 


//Node Utility Functions
Node* addSiblingNode(Node* sibling, Node* newSibling);
void setSiblingsType(Node* node, ParmType parmType);
Node* newDeclNode(DeclarationType type, TokenData* token);
Node* newStmtNode(StatementType type, TokenData* token);
Node* newExpNode(ExpressionType type, TokenData* token); 
Node* newDeclNodeIO(DeclarationType type);


//printers
void printAST(Node *tree, int numSiblings, bool isShowingType);
void printOutputTabs(const int numtabs);
void printParameterType(ParmType parmType);

#endif