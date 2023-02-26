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
#include "NodeData.hpp"

//Break, Coumpound, For, If, Range, Return, Statment, While


//**********************************************************
// ************ StatementNode Class ************************
//**********************************************************
class StatementNode : public Node
{
    public :
        enum class Type { BREAK, COMPOUND, FOR, IF, RETURN, RANGE, WHILE};

        // ****************** Constructor ******************************

        StatementNode(const int tokenLineNumber, const StatementNode::Type statementType);


        // ****************** Getters ******************************
        StatementNode::Type getStatementNodeType() const;

    private:
        const StatementNode::Type m_statementType;
};

//******************************************************
// ************ BreakNode Class ************************
//******************************************************

class Break : public StatementNode
{
    public :
        Break(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ CompoundNode Class ************************
//*********************************************************
class Compound : public StatementNode
{
    public :

        Compound(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ ForNode Class *****************************
//*********************************************************
class For : public StatementNode
{
    public :

        For(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*********************************************************
// ************ IfNode Class ******************************
//*********************************************************
class If : public StatementNode
{
    public :

        If(const int tokenLineNumber);

        std::string printTokenString() const override;
};


//******************************************************
// ************ RangeNode Class ************************
//******************************************************
class Range : public StatementNode
{
    public :

        Range(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//*******************************************************
// ************ ReturnNode Class ************************
//*********************************************************
class Return: public StatementNode
{
    public :

        Return(const int tokenLineNumber);

        std::string printTokenString() const override;
};

//******************************************************
// ************ WhileNode Class ************************
//******************************************************
class While : public StatementNode
{
    public :

        While(const int tokenLineNumber);

        std::string printTokenString() const override;
};

#endif