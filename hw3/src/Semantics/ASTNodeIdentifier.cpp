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
    return (node != nullptr && node->getNodeType() == NodeType::Declaration);
}

bool isFunctionNode(const Node* node)
{
    if (!isDeclarationNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Function);
}

bool isParameterNode(const Node* node)
{
    if (!isDeclarationNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Parameter);
}

bool isVariableNode(const Node* node)
{
    if (!isDeclarationNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Variable);
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
    
    return (node != nullptr && node->getNodeType() == NodeType::Assignment);
}

bool isBinaryNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Binary);
}

bool isCallNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Call);
}

bool isConstantNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Constant);
}

bool isExpressionNode(const Node* node)
{
    return node->getNodeType() == NodeType::Expression;
}

bool isIdentifierNode(const Node* node)
{
    if(!isExpressionNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Identifier);
}

bool isUnaryAssignmentNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::UnaryAssignment);
}

bool isUnaryNode(const Node* node)
{
    if (!isExpressionNode(node))
    {
        return false;
    }
    
    return (node != nullptr && node->getNodeType() == NodeType::Unary);
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
    return (node != nullptr && node->getNodeType() == NodeType::Break);
}

bool isCompoundNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (node != nullptr && node->getNodeType() == NodeType::Compound);
}

bool isContinueNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (node != nullptr && node->getNodeType() == NodeType::Continue);
}

bool isForNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (node != nullptr && node->getNodeType() == NodeType::For);
}

bool isIfNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (node != nullptr && node->getNodeType() == NodeType::If);
}

bool isReturnNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (node != nullptr && node->getNodeType() == NodeType::Return);
}

bool isStatementNode(const Node* node)
{
    return node->getNodeType() == NodeType::Statement;
}

bool isWhileNode(const Node* node)
{
    if(!isStatementNode(node))
    {
        return false;
    }
    return (node != nullptr && node->getNodeType() == NodeType::While);
}
