/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: ExprssionNodes.hpp
DESC: ExpressionNodes Subclass. Inherits from Node Base Class. 

*/

#ifndef EXPRESSIONNODES_HPP
#define EXPRESSIONNODES_HPP


#include "Node.hpp"
//Assignment, Binary, Call, Constant, Identifier, Unary, UnaryAssignment

//**********************************************************
// ************ ExpressionNode Class ************************
//**********************************************************
class ExpressionNode : public Node
{
    public :

    protected :
};


//******************************************************
// ************ AssignmentNode Class *******************
//******************************************************
class AssignmentNode : public ExpressionNode
{
    public :

    protected :
};


//**********************************************************
// ************ BinaryNode Class ***************************
//**********************************************************
class BinaryNode : public ExpressionNode
{
    public :

    protected :
};


//**********************************************************
// ************ CallNode Class *****************************
//**********************************************************
class CallNode : public ExpressionNode
{
    public :

    protected :
};


//**********************************************************
// ************ ConstantNode Class *************************
//**********************************************************
class ConstantNode : public ExpressionNode
{
    public :

    protected :
};


//**********************************************************
// ************ IdentifierNode Class ************************
//**********************************************************
class IdentifierNode : public ExpressionNode
{
    public :

    protected :
};


//**********************************************************
// ************ UnaryNode Class ****************************
//**********************************************************
class UnaryNode : public ExpressionNode
{
    public :

    protected :
};


//**********************************************************
// ************ UnaryAssignmentNode Class ******************
//**********************************************************
class UnaryAssignmentNode : public ExpressionNode
{
    public :

    protected :
};




#endif