/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: ExprssionNodes.cpp
DESC: ExpressionNodes Subclass Member Definitions. 

*/
#include "ExpressionNodes.hpp"

//********************************************************************************
// ************ ExpressionNode Class Member Functions *********************************
//********************************************************************************
ExpressionNode :: ExpressionNode(int tokenLineNumber, const Node::Type nodeType) : Node(tokenLineNumber, nodeType)
{
    //initialize sibling node to nullptr
    m_siblingNode = nullptr; 
}
