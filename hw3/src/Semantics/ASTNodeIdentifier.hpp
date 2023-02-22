/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/13/2023

FILE: ASTNodeIdentifier.hpp
DESC: Declares Functions to identify AST nodes

*/

#ifndef ASTNODEIDENTIFIER_HPP
#define ASTNODEIDENTIFIER_HPP

#include"../AST/AST.hpp"


//******************************************************
// ************ Declaration Nodes **********************
//******************************************************

bool isDeclarationNode(const Node* node); //returns true if node is a declaration node
bool isFunctionNode(const Node* node); //returns true if node is a function node
bool isParameterNode(const Node* node); //returns true if node is a parameter node
bool isVariableNode(const Node* node); //returns true if node is a variable node



//******************************************************
// ************ Expression Nodes **********************
//******************************************************

bool isAssignmentNode(const Node* node); //returns true if node is an assignment node
bool isBinaryNode(const Node* node); //returns true if node is a binary node
bool isCallNode(const Node* node); //returns true if node is a call node
bool isConstantNode(const Node* node); //returns true if node is a constant node
bool isExpressionNode(const Node* node); //returns true if node is an expression node
bool isIdentifierNode(const Node* node); //returns true if node is an identifier node
bool isUnaryAssignmentNode(const Node* node); //returns true if node is a unary assignment node
bool isUnaryNode(const Node* node); //returns true if node is a unary node



//******************************************************
// ************ Statement Nodes **********************
//******************************************************

bool isBreakNode(const Node* node); //returns true if node is a break node
bool isCompoundNode(const Node* node); //returns true if node is a compound node
bool isContinueNode(const Node* node); //returns true if node is a continue node
bool isForNode(const Node* node); //returns true if node is a for node
bool isIfNode(const Node* node); //returns true if node is an if node
bool isReturnNode(const Node* node); //returns true if node is a return node
bool isStatementNode(const Node* node); //returns true if node is a statement node
bool isWhileNode(const Node* node); //returns true if node is a while node




#endif // ASTNODEIDENTIFIER_HPP