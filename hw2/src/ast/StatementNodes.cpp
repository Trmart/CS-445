#include "Node.hpp"
#include "StatementNodes.hpp"

StatementNode::StatementNode(const int tokenLineNumber, const StatementNode::Type statementType) : Node(tokenLineNumber, Node::Type::Statement), m_statementType(statementType)
{

}

StatementNode::Type StatementNode::getTypeOfStatement() const
{
    return m_statementType;
}

BreakNode::BreakNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Break)
{

}

std::string BreakNode::printTokenString() const
{
    return "Break";
}


CompoundNode::CompoundNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Compound)
{

}

std::string CompoundNode::printTokenString() const
{
    return "Compound";
}

ForNode::ForNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::For)
{

}

std::string ForNode::printTokenString() const
{
    return "For";
}

IfNode::IfNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::If)
{

}

std::string IfNode::printTokenString() const
{
    return "If";
}

RangeNode::RangeNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Range)
{

}

std::string RangeNode::printTokenString() const
{
    return "Range";
}

ReturnNode::ReturnNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Return)
{

}

std::string ReturnNode::printTokenString() const
{
    return "Return";
}

WhileNode::WhileNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::While)
{

}

std::string WhileNode::printTokenString() const
{
    return "While";
}