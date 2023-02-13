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
// class ExpressionNode : public Node
// {
//     public:

//         //Expression Type Enum
//         enum class Type
//         {
//             ASSIGN,
//             BINARY,
//             CALL,
//             CONSTANT,
//             IDENTIFIER,
//             UNARY, 
//             UNARYASSIGN,
//         };

//         //Constructor
//         ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType);
    
//         std::string printTokenString() const;
    
//     protected:
        
//         //Expression Type
//         const ExpressionNode::Type m_expressionType;
// };

//******************************************************
// ************ AssignmentNode Class *******************
//******************************************************
class Asgn : public Node
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
        Asgn(const int tokenLineNumber, const Type assignmentType);

        std::string printTokenString() const;
    protected:

        //Assignment Type
        const Type m_assignmentType;
};


//**********************************************************
// ************ BinaryNode Class ***************************
//**********************************************************
class Binary : public Node
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
        Binary(const int tokenLineNumber, const Type assignmentType);

        //Print Token Output String
        std::string printTokenString() const;

    protected:
    
        //Binary Type
        Type m_binaryType;
};


//**********************************************************
// ************ CallNode Class *****************************
//**********************************************************
class Call : public Node
{
    public:

        //CallNode Constructor
        Call(const int tokenLineNumber, std::string functionName);

        //Print Token Output String
        std::string printTokenString() const;
};


//**********************************************************
// ************ ConstantNode Class *************************
//**********************************************************
class Const : public Node
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
        Const(const int tokenLineNumber, Type constantType, const std::string constantValue);

        //Print Token Output String
        std::string printTokenString() const;

    protected:
    
        //Constant Type
        Type m_constantType;

        //TokenFormatter
        TokenFormatter m_tokenFormatter;
};


//**********************************************************
// ************ IdentifierNode Class ************************
//**********************************************************
class Id : public Node
{
    public:
        
        //IdentifierNode Constructor
        Id(const int tokenLineNumber, std:: string identifierName, bool isArray = false);

        //Print Token Output String
        std::string printTokenString() const;
    
    protected:

        //flag to hold whether or not the identifier is an array
        bool m_isArray;

};


//**********************************************************
// ************ UnaryNode Class ****************************
//**********************************************************
class Unary : public Node
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
        Unary(const int tokenLineNumber, const Type unaryType);

        //Print Token Output String
        std::string printTokenString() const;

    protected:

        //Unary Type
        Type m_unaryType;
};


//**********************************************************
// ************ UnaryAssignmentNode Class ******************
//**********************************************************
class UnaryAsgn : public Node
{
    public:

        //UnaryAssignment Type Enum
        enum class Type
        {
            INC, 
            DEC
        };

        //UnaryAssignmentNode Constructor
        UnaryAsgn(const int tokenLineNumber, const Type unaryAssignmentType);

        //Print Token Output String
        std::string printTokenString() const;


    protected:

        //UnaryAssignment Type
        Type m_unaryAssignmentType;
};




#endif