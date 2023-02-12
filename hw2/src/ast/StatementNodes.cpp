#include "StatementNodes.hpp"

//********************************************************************************
// ************ StatementNode Class Member Functions *****************************
//********************************************************************************


//StatementNode Constructor
// StatementNode::StatementNode(const int tokenLineNumber)
// {

// }


//StatementNode Print Token String
// StatementNode::Type StatementNode::getTypeOfStatement() const
// {
//     return m_statementType;
// }

//********************************************************************************
// ************ BreakNode Class Member Functions *********************************
//********************************************************************************

//BreakNode Constructor
BreakNode::BreakNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
CompoundNode::CompoundNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
ForNode::ForNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
IfNode::IfNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
RangeNode::RangeNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
ReturnNode::ReturnNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
WhileNode::WhileNode(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
{

}

//WhileNode Print Token String
std::string WhileNode::printTokenString() const
{
    return "While";
}