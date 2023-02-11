#include "StatementNodes.hpp"

//********************************************************************************
// ************ StatementNode Class Member Functions *****************************
//********************************************************************************


//StatementNode Constructor
StatementNode::StatementNode(const int tokenLineNumber, const StatementNode::Type statementType) : Node(tokenLineNumber, Node::Type::Statement), m_statementType(statementType)
{

}


//StatementNode Print Token String
StatementNode::Type StatementNode::getTypeOfStatement() const
{
    return m_statementType;
}

//********************************************************************************
// ************ BreakNode Class Member Functions *********************************
//********************************************************************************

//BreakNode Constructor
BreakNode::BreakNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Break)
{

}


//BreakNode Print Token String
std::string BreakNode::printTokenString() const
{
    return "Break";
}


//********************************************************************************
// ************ CompoundNode Class Member Functions *******************************
//********************************************************************************

//CompoundNode Constructor
CompoundNode::CompoundNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Compound)
{

}

//CompoundNode Print Token String
std::string CompoundNode::printTokenString() const
{
    return "Compound";
}

//********************************************************************************
// ************ ForNode Class Member Functions ************************************
//********************************************************************************


//ForNode Constructor
ForNode::ForNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::For)
{

}


//ForNode Print Token String
std::string ForNode::printTokenString() const
{
    return "For";
}

//********************************************************************************
// ************ IfNode Class Member Functions *************************************
//********************************************************************************


//IfNode Constructor
IfNode::IfNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::If)
{

}


//IfNode Print Token String
std::string IfNode::printTokenString() const
{
    return "If";
}

//********************************************************************************
// ************ RangeNode Class Member Functions *********************************
//********************************************************************************


//RangeNode Constructor
RangeNode::RangeNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Range)
{

}


//RangeNode Print Token String
std::string RangeNode::printTokenString() const
{
    return "Range";
}

//********************************************************************************
// ************ ReturnNode Class Member Functions *******************************
//********************************************************************************


//ReturnNode Constructor
ReturnNode::ReturnNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::Return)
{

}


//ReturnNode Print Token String
std::string ReturnNode::printTokenString() const
{
    return "Return";
}

//********************************************************************************
// ************ WhileNode Class Member Functions *********************************
//********************************************************************************


//WhileNode Constructor
WhileNode::WhileNode(const int tokenLineNumber) : StatementNode(tokenLineNumber, StatementNode::Type::While)
{

}

//WhileNode Print Token String
std::string WhileNode::printTokenString() const
{
    return "While";
}