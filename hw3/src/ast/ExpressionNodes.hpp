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
    public:

        enum class Type
        {
            Assignment,
            Binary,
            Call,
            Constant,
            Identifier,
            Unary,
            UnaryAssignment,
            None
        };

        //Constructor
        ExpressionNode(int tokenLineNumber, const Type nodeType); 

        ExpressionNode::Type getTypeOfExpressionNode() const; 

    protected:
        ExpressionNode::Type m_expressionNodeType;
};


//******************************************************
// ************ AssignmentNode Class *******************
//******************************************************
class AssignmentNode : public ExpressionNode
{
    public :

        enum class Type
        {
            Asgn,
            AddAss,
            SubAss,
            MulAss,
            DivAss,
            None
        };
        AssignmentNode(int tokenLineNumber, const Node::Type nodeType) : ExpressionNode(tokenLineNumber, nodeType)
        {
            //initialize sibling node to nullptr
            m_siblingNode = nullptr; 
        }
    protected :
};


//**********************************************************
// ************ BinaryNode Class ***************************
//**********************************************************
class BinaryNode : public ExpressionNode
{
    public :
        BinaryNode(int tokenLineNumber, const Node::Type nodeType) : ExpressionNode(tokenLineNumber, nodeType)
        {
            //initialize sibling node to nullptr
            m_siblingNode = nullptr; 
        }
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
        IdentifierNode(int tokenLineNumber, std:: string identifierName, bool isArray)
        {

        }
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