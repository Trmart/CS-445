/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: Node.cpp
DESC: Node base class definitions for AST nodes. Statements, Expressions, and Declarations will inherit from this class.

*/

#include "Node.hpp"
#include "scanType.hpp"


// ************ Node Class Constructors ************************

//Base Constructor
Node :: Node(int tokenLineNumber)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;
}

//Int Constructor
Node :: Node(int tokenLineNumber, int numValue)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

}

//Char Constructor
Node :: Node(int tokenLineNumber, char charValue)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

}

//Bool Constructor
Node :: Node(int tokenLineNumber, bool boolValue)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

}

//String Constructor
Node :: Node(int tokenLineNumber, std::string stringValue)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

}


// ******************** Node Base Class Destructor *********************
~Node :: Node()
{

}


// ******************* Node Print Functions *****************************

//Print Token Output String
virtual std::string Node ::printTokenString() const
{

}

//Print AST Nodes
virtual void Node :: printASTNode(int indent) const
{

}

//Print The Whole AST
void Node :: printAST() const
{

}

//Print the Formatting Output Tabs for the Correct AST Output 
void Node :: printOutputTabs(const int numTabs) const
{

}

// ****************** Node adding functions ******************************

//add child node to AST
void Node :: addChildNode(Node* node)
{

}

//add sibling node to AST 
void Node :: addSiblingNode(Node* node)
{

}
