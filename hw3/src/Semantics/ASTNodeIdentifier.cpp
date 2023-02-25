/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/13/2023

FILE: ASTNodeIdentifier.cpp
DESC: Declares Functions to identify AST nodes

*/

#include "ASTNodeIdentifier.hpp"

//******************************************************
// ************ Declaration Nodes **********************
//******************************************************

bool isDeclarationNode(const Node* node)
{
    return (node != nullptr && node->getNodeType() == Node::Type::DECLARATION);
}

bool isFunctionNode(const Node* node)
{
    if (!isDeclarationNode(node))
    {
        return false;
    }
    
    return (((DeclarationNode*)node)->getDeclarationNodeType() == DeclarationNode::Type::FUNCTION);
}

bool isParameterNode(const Node* node)
{
    if (!isDeclarationNode(node))
    {
        return false;
    }
    
    return (((DeclarationNode*)node)->getDeclarationNodeType() == DeclarationNode::Type::PARAMETER);
}

bool isVariableNode(const Node* node)
{
    if (!isDeclarationNode(node))
    {
        return false;
    }
    
    return (((DeclarationNode*)node)->getDeclarationNodeType() == DeclarationNode::Type::VARIABLE);
}


//******************************************************
// ************ Expression Nodes ***********************
//******************************************************


bool isAssignmentNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::ASSIGN);
}

bool isBinaryNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::BINARY);
}

bool isCallNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::CALL);
}

bool isConstantNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::CONSTANT);
}

bool isExpressionNode(const Node* node)
{
    return (node != nullptr && node->getNodeType() == Node::Type::EXPRESSION);
}

bool isIdentifierNode(const Node* node)
{
    if(!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::IDENTIFIER);
}

bool isUnaryAssignmentNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::UNARYASSIGN);
}

bool isUnaryNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (((ExpressionNode*)node)->getExpressionNodeType() == ExpressionNode::Type::UNARY);
}



//******************************************************
// ************ Statement Nodes ************************
//******************************************************

bool isBreakNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (((StatementNode*)node)->getStatementNodeType() == StatementNode::Type::BREAK);
}

bool isCompoundNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (((StatementNode*)node)->getStatementNodeType() == StatementNode::Type::COMPOUND);
}



bool isForNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (((StatementNode*)node)->getStatementNodeType() == StatementNode::Type::FOR);
}

bool isIfNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (((StatementNode*)node)->getStatementNodeType() == StatementNode::Type::IF);
}

bool isReturnNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (((StatementNode*)node)->getStatementNodeType() == StatementNode::Type::RETURN);
}

bool isStatementNode(const Node* node)
{
    return (node != nullptr && node->getNodeType() == Node::Type::STATEMENT);
}

bool isWhileNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (((StatementNode*)node)->getStatementNodeType() == StatementNode::Type::WHILE);
}
