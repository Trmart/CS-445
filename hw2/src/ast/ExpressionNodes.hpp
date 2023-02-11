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
// ************ ExpressionNode Classes ************************
//**********************************************************
class ExpressionNode : public Node
{
    public :

        enum class Type
        {
            Assign,
            Binary,
            Call,
            Constant,
            Identifier,
            Unary, 
            UnaryAssignment
        };
        ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType);
    protected :
};

//******************************************************
// ************ AssignmentNode Class *******************
//******************************************************
class AssignmentNode : public Node
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
class BinaryNode : public Node
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
class CallNode : public Node
{
    public :

    protected :
};


//**********************************************************
// ************ ConstantNode Class *************************
//**********************************************************
class ConstantNode : public Node
{
    public :

    protected :
};


//**********************************************************
// ************ IdentifierNode Class ************************
//**********************************************************
class IdentifierNode : public Node
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
class UnaryNode : public Node
{
    public :

    protected :
};


//**********************************************************
// ************ UnaryAssignmentNode Class ******************
//**********************************************************
class UnaryAssignmentNode : public Node
{
    public :

    protected :
};




#endif