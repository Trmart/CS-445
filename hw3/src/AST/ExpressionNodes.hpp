/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: ExprssionNodes.hpp
DESC: ExpressionNodes Subclass. Inherits from Node Base Class. 

*/

#ifndef EXPRESSIONNODES_HPP
#define EXPRESSIONNODES_HPP


#include "Node.hpp"
#include "NodeData.hpp"

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
        ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType, NodeData* nodeData);


        // ****************** Printing ******************************
        virtual std::string printTokenStringWithType() const override;


        // ****************** Setters ******************************
        void setNodeData(NodeData* nodeData);

        // ****************** Getters ******************************
        NodeData* getNodeData() const;
        ExpressionNode::Type getExpressionNodeType() const;
    private:
        const ExpressionNode::Type m_expressionType;

    protected:
        NodeData* m_nodeData;
};

//******************************************************
// ************ AssignmentNode Class *******************
//******************************************************
class Asgn : public ExpressionNode
{
    public:

        enum class Type
        {
            ASGN,
            ADDASS,
            SUBASS,
            MULASS,
            DIVASS
        };
        
        Asgn(const int tokenLineNumber, const Asgn::Type assignmentType);

        std::string printTokenString() const override;

        // ****************** Getters *****************************
        std::string getSymbol() const;
        Asgn::Type getAssignmentType() const;

    private:

        //Assignment Type
        const Type m_assignmentType;
};


//**********************************************************
// ************ BinaryNode Class ***************************
//**********************************************************
class Binary : public ExpressionNode
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
            INDEX
        };


        //BinaryNode Constructor
        Binary(const int tokenLineNumber, const Binary::Type assignmentType);

        //Print Token Output String
        std::string printTokenString() const override;


        // ****************** Getters ******************************
        Binary::Type getBinaryType() const;
        std::string getSymbol() const;

    private:
    
        //Binary Type
        const Binary::Type m_binaryType;
};


//**********************************************************
// ************ CallNode Class *****************************
//**********************************************************
class Call : public ExpressionNode
{
    public:

        //CallNode Constructor
        Call(const int tokenLineNumber, std::string functionName);

        //Print Token Output String
        std::string printTokenString() const override; 

        // ****************** Getters ******************************
        std::string getFunctionCallName() const;

    private:

        //Function Name
        const std::string m_functionName;
};


//**********************************************************
// ************ ConstantNode Class *************************
//**********************************************************
class Const : public ExpressionNode
{
    public :

        //Constant Type Enum
        enum class Type
        {
            INT,
            CHAR,
            BOOL,
            STRING
        };

        //ConstantNode Constructor
        Const(const int tokenLineNumber, Const::Type constantType, const std::string constantValue);

        //Print Token Output String
        std::string printTokenString() const override;
        std::string printTokenStringWithType() const override;

        // ****************** Getters ******************************
        bool getIsCharLengthGreaterThanOne() const;

    private:
    
        //Constant Type
        const Const::Type m_constantType;

        //TokenFormatter
        TokenFormatter m_tokenFormatter;

        //char length warning flag
        bool m_isCharLengthGreaterThanOne = false;

        //Constant Values
        int m_intValue;
        char m_charValue;
        bool m_boolValue;
        std::string m_stringValue; 


};


//**********************************************************
// ************ IdentifierNode Class ************************
//**********************************************************
class Id : public ExpressionNode
{
    public:
        
        //IdentifierNode Constructor
        Id(const int tokenLineNumber, std:: string identifierName, bool isArray=false);

        // ****************** Printers ******************************
        
        std::string printTokenString() const override;
        std::string printTokenStringWithType() const override;

        // ****************** Getters ******************************
        std::string getIdentifierName() const;
        bool getIsArray() const;
    
    private:

        //flag to hold whether or not the identifier is an array
        const bool m_isArray;

        const std::string m_identifierName;

};


//**********************************************************
// ************ UnaryNode Class ****************************
//**********************************************************
class Unary : public ExpressionNode
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
        Unary(const int tokenLineNumber, const Unary::Type unaryType);

        //Print Token Output String
        std::string printTokenString() const override;

        // ****************** Getters ******************************
        Unary::Type getUnaryType() const;
        std::string getSymbol() const;

    private:

        //Unary Type
       const Unary::Type m_unaryType;
};


//**********************************************************
// ************ UnaryAssignmentNode Class ******************
//**********************************************************
class UnaryAsgn : public ExpressionNode
{
    public:

        //UnaryAssignment Type Enum
        enum class Type
        {
            INC, 
            DEC
        };

        //UnaryAssignmentNode Constructor
        UnaryAsgn(const int tokenLineNumber, const UnaryAsgn::Type unaryAssignmentType);

        //Print Token Output String
        std::string printTokenString() const override;

        // ****************** Getters ******************************
        UnaryAsgn::Type getUnaryAssignmentType() const;
        std::string getSymbol() const;


    private:

        //UnaryAssignment Type
        const UnaryAsgn::Type m_unaryAssignmentType;
};




#endif