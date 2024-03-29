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
Break::Break(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
Compound::Compound(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
For::For(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
If::If(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
Range::Range(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
Return::Return(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
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
While::While(const int tokenLineNumber) : Node :: Node(tokenLineNumber)
{

}

//WhileNode Print Token String
std::string While::printTokenString() const
{
    return "While";
}