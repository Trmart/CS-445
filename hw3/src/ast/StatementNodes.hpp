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
class StatementNode : public Node
{
    public :
        enum class Type { Break, Compound, For, If, Return, While, Range };

        StatementNode(const int tokenLineNumber, const StatementNode::Type statementType);

        StatementNode::Type getTypeOfStatement() const; 
    
    
    protected :

        const StatementNode::Type m_statementType;
};

//******************************************************
// ************ BreakNode Class ************************
//******************************************************

class BreakNode : public StatementNode
{
    public :
        BreakNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ CompoundNode Class ************************
//*********************************************************
class CompoundNode : public StatementNode
{
    public :

        CompoundNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ ForNode Class *****************************
//*********************************************************
class ForNode : public StatementNode
{
    public :

        ForNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ IfNode Class ******************************
//*********************************************************
class IfNode : public StatementNode
{
    public :

        IfNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};


//******************************************************
// ************ RangeNode Class ************************
//******************************************************
class RangeNode : public StatementNode
{
    public :

        RangeNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*******************************************************
// ************ ReturnNode Class ************************
//*********************************************************
class ReturnNode : public StatementNode
{
    public :

        ReturnNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//******************************************************
// ************ WhileNode Class ************************
//******************************************************
class WhileNode : public StatementNode
{
    public :

        WhileNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

#endif