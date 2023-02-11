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
    public:

        //Expression Type Enum
        enum class Type
        {
            ASSIGN,
            BINARY,
            CALL,
            CONSTANT,
            IDENTIFIER,
            UNARY, 
            UNARYASSIGN,
        };

        //Constructor
        ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType);
    
        std::string printTokenString() const;
    
    protected:
        
        //Expression Type
        const ExpressionNode::Type m_expressionType;
};

//******************************************************
// ************ AssignmentNode Class *******************
//******************************************************
class AssignmentNode : public ExpressionNode
{
    public:

        enum class Type
        {
            ASGN,
            ADDASS,
            SUBASS,
            MULASS,
            DIVASS,
            NONE
        };
        AssignmentNode(int tokenLineNumber, const Type assignmentType);

        std::string printTokenString() const;
    protected:

        //Assignment Type
        AssignmentNode::Type m_assignmentType;
};


//**********************************************************
// ************ BinaryNode Class ***************************
//**********************************************************
class BinaryNode : public ExpressionNode
{
    public:
        
        //Binary Type Enum
        enum class Type
        {
            ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            AND,
            OR,
            NOT,
            LT,
            LEQ,
            GT,
            GEQ,
            EQ,
            NEQ,
            INDEX,
            NONE
        };


        //BinaryNode Constructor
        BinaryNode(int tokenLineNumber, const Type assignmentType);

        //Print Token Output String
        std::string printTokenString() const;

    protected:
    
        //Binary Type
        BinaryNode::Type m_binaryType;
};


//**********************************************************
// ************ CallNode Class *****************************
//**********************************************************
class CallNode : public ExpressionNode
{
    public:

        //CallNode Constructor
        CallNode(int tokenLineNumber, std::string functionName);

        //Print Token Output String
        std::string printTokenString() const;
};


//**********************************************************
// ************ ConstantNode Class *************************
//**********************************************************
class ConstantNode : public ExpressionNode
{
    public :

        //Constant Type Enum
        enum class Type
        {
            INT,
            CHAR,
            BOOL,
            STRING,
            NONE
        };

        //ConstantNode Constructor
        ConstantNode(int tokenLineNumber, const std::string constantValue, Type constantType);

        //Print Token Output String
        std::string printTokenString() const;

    protected:
    
        //Constant Type
        ConstantNode::Type m_constantType;

        //TokenFormatter
        TokenFormatter m_tokenFormatter;
};


//**********************************************************
// ************ IdentifierNode Class ************************
//**********************************************************
class IdentifierNode : public ExpressionNode
{
    public:
        
        //IdentifierNode Constructor
        IdentifierNode(int tokenLineNumber, bool isArray, std:: string identifierName);

        //Print Token Output String
        std::string printTokenString() const;
    
    protected:

        //flag to hold whether or not the identifier is an array
        bool m_isArray;

};


//**********************************************************
// ************ UnaryNode Class ****************************
//**********************************************************
class UnaryNode : public ExpressionNode
{
    public:

        //Unary Type Enum
        enum class Type
        {
            QUESTION, 
            NOT, 
            SIZEOF,
            CHSIGN
        };

        //UnaryNode Constructor
        UnaryNode(int tokenLineNumber, const Type unaryType);

        //Print Token Output String
        std::string printTokenString() const;

    protected:

        //Unary Type
        UnaryNode::Type m_unaryType;
};


//**********************************************************
// ************ UnaryAssignmentNode Class ******************
//**********************************************************
class UnaryAssignmentNode : public ExpressionNode
{
    public:

        //UnaryAssignment Type Enum
        enum class Type
        {
            INC, 
            DEC
        };

        //UnaryAssignmentNode Constructor
        UnaryAssignmentNode(int tokenLineNumber, const Type unaryAssignmentType);

        //Print Token Output String
        std::string printTokenString() const;


    protected:

        //UnaryAssignment Type
        UnaryAssignmentNode::Type m_unaryAssignmentType;
};




#endif