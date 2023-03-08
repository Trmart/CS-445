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
    NULLSTMT, 
    IF, 
    WHILE, 
    FOR, 
    COMPOUND, 
    RETURN, 
    BREAK, 
    RANGE
};

//Expression Types (ExpKind)
enum ExpressionType 
{
    OP, 
    CONSTANT, 
    IDENTIFIER, 
    ASSIGN, 
    INIT, 
    CALL
};

//ParmType is used for function return type checking 
enum ParmType 
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
    NONE, LOCAL, GLOBAL, PARAMETER, LOCAL_STATIC
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
void setSiblingsType(Node* node, ExpressionType expType);
Node* newDeclNode(DeclarationType type, TokenData* token);
Node* newStmtNode(StatementType type, TokenData* token);
Node* newExpNode(ExpressionType type, TokenData* token); 
Node* newDeclNodeIO(DeclarationType type);


//printers
void printAST(Node *tree, int numSiblings, bool isShowingType);
void printOutputTabs(const int numtabs);
void printParameterType(ParmType parmType);

#endif