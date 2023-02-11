#include "StatementNodes.hpp"

//********************************************************************************
// ************ StatementNode Class Member Functions *****************************
//********************************************************************************

StatementNode::StatementNode(const int tokenLineNumber, const StatementNode::Type statementType) : Node(tokenLineNumber, Node::Type::Statement), m_statementType(statementType)
{

}

StatementNode::Type StatementNode::getTypeOfStatement() const
{
    return m_statementType;
}

//********************************************************************************
// ************ BreakNode Class Member Functions *********************************
//********************************************************************************

BreakNode::BreakNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Break)
{

}

std::string BreakNode::printTokenString() const
{
    return "Break";
}


//********************************************************************************
// ************ CompoundNode Class Member Functions *******************************
//********************************************************************************

CompoundNode::CompoundNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Compound)
{

}

std::string CompoundNode::printTokenString() const
{
    return "Compound";
}

//********************************************************************************
// ************ ForNode Class Member Functions ************************************
//********************************************************************************

ForNode::ForNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::For)
{

}

std::string ForNode::printTokenString() const
{
    return "For";
}

//********************************************************************************
// ************ IfNode Class Member Functions *************************************
//********************************************************************************

IfNode::IfNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::If)
{

}

std::string IfNode::printTokenString() const
{
    return "If";
}

//********************************************************************************
// ************ RangeNode Class Member Functions *********************************
//********************************************************************************

RangeNode::RangeNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Range)
{

}

std::string RangeNode::printTokenString() const
{
    return "Range";
}

//********************************************************************************
// ************ ReturnNode Class Member Functions *******************************
//********************************************************************************

ReturnNode::ReturnNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Return)
{

}

std::string ReturnNode::printTokenString() const
{
    return "Return";
}

//********************************************************************************
// ************ WhileNode Class Member Functions *********************************
//********************************************************************************

WhileNode::WhileNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::While)
{

}

std::string WhileNode::printTokenString() const
{
    return "While";
}