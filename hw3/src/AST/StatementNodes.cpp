#include "StatementNodes.hpp"

//********************************************************************************
// ************ StatementNode Class Member Functions *****************************
//********************************************************************************

// ****************** Constructor ******************************

StatementNode::StatementNode(const int tokenLineNumber, const StatementNode::Type statementType): Node :: Node(tokenLineNumber, Node :: Type :: STATEMENT), m_statementType(statementType)
{

}


// ****************** Getters ******************************
const StatementNode::Type StatementNode::getStatementNodeType() const
{
    return m_statementType;
}

//********************************************************************************
// ************ BreakNode Class Member Functions *********************************
//********************************************************************************

//BreakNode Constructor
Break::Break(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: BREAK)
{

}


//BreakNode Print Token String
std::string Break::printTokenString() const
{
    return "Break";
}


//********************************************************************************
// ************ CompoundNode Class Member Functions *******************************
//********************************************************************************

//CompoundNode Constructor
Compound::Compound(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: COMPOUND)
{

}

//CompoundNode Print Token String
std::string Compound::printTokenString() const
{
    return "Compound";
}

//********************************************************************************
// ************ ForNode Class Member Functions ************************************
//********************************************************************************


//ForNode Constructor
For::For(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: FOR)
{

}


//ForNode Print Token String
std::string For::printTokenString() const
{
    return "For";
}

//********************************************************************************
// ************ IfNode Class Member Functions *************************************
//********************************************************************************


//IfNode Constructor
If::If(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: IF)
{

}


//IfNode Print Token String
std::string If::printTokenString() const
{
    return "If";
}

//********************************************************************************
// ************ RangeNode Class Member Functions *********************************
//********************************************************************************


//RangeNode Constructor
Range::Range(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: RANGE)
{

}


//RangeNode Print Token String
std::string Range::printTokenString() const
{
    return "Range";
}

//********************************************************************************
// ************ ReturnNode Class Member Functions *******************************
//********************************************************************************


//ReturnNode Constructor
Return::Return(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: RETURN)
{

}


//ReturnNode Print Token String
std::string Return::printTokenString() const
{
    return "Return";
}

//********************************************************************************
// ************ WhileNode Class Member Functions *********************************
//********************************************************************************


//WhileNode Constructor
While::While(const int tokenLineNumber) : StatementNode :: StatementNode(tokenLineNumber, StatementNode :: Type :: WHILE)
{

}

//WhileNode Print Token String
std::string While::printTokenString() const
{
    return "While";
}