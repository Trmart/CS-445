/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: StatementNodes.hpp
DESC: StatementsNodes Subclass. Inherits from Node Base Class. 

*/

#ifndef STATEMENTNODES_HPP
#define STATEMENTNODES_HPP

#include "Node.hpp"
//Break, Coumpound, For, If, Range, Return, Statment, While


//**********************************************************
// ************ StatementNode Class ************************
//**********************************************************
// class StatementNode : public Node
// {
//     public :
//         enum class Type { Break, Compound, For, If, Return, While, Range };
//         StatementNode(); 
//         StatementNode(const int tokenLineNumber);

//         StatementNode::Type getTypeOfStatement() const; 
    
    
//     protected :

//         // const StatementNode::Type m_statementType;
// };

//******************************************************
// ************ BreakNode Class ************************
//******************************************************

class BreakNode : public Node
{
    public :
        BreakNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ CompoundNode Class ************************
//*********************************************************
class CompoundNode : public Node
{
    public :

        CompoundNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ ForNode Class *****************************
//*********************************************************
class ForNode : public Node
{
    public :

        ForNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ IfNode Class ******************************
//*********************************************************
class IfNode : public Node
{
    public :

        IfNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};


//******************************************************
// ************ RangeNode Class ************************
//******************************************************
class RangeNode : public Node
{
    public :

        RangeNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*******************************************************
// ************ ReturnNode Class ************************
//*********************************************************
class ReturnNode : public Node
{
    public :

        ReturnNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//******************************************************
// ************ WhileNode Class ************************
//******************************************************
class WhileNode : public Node
{
    public :

        WhileNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

#endif