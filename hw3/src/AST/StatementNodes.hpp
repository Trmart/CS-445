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
        const StatementNode::Type getStatementNodeType() const;

    protected:
        const StatementNode::Type m_statementType;
};

//******************************************************
// ************ BreakNode Class ************************
//******************************************************

class Break : public Node
{
    public :
        Break(const int tokenLineNumber);

        std::string printTokenString() const;
};

//*********************************************************
// ************ CompoundNode Class ************************
//*********************************************************
class Compound : public Node
{
    public :

        Compound(const int tokenLineNumber);

        std::string printTokenString() const;
};

//*********************************************************
// ************ ForNode Class *****************************
//*********************************************************
class For : public Node
{
    public :

        For(const int tokenLineNumber);

        std::string printTokenString() const;
};

//*********************************************************
// ************ IfNode Class ******************************
//*********************************************************
class If : public Node
{
    public :

        If(const int tokenLineNumber);

        std::string printTokenString() const;
};


//******************************************************
// ************ RangeNode Class ************************
//******************************************************
class Range : public Node
{
    public :

        Range(const int tokenLineNumber);

        std::string printTokenString() const;
};

//*******************************************************
// ************ ReturnNode Class ************************
//*********************************************************
class Return: public Node
{
    public :

        Return(const int tokenLineNumber);

        std::string printTokenString() const;
};

//******************************************************
// ************ WhileNode Class ************************
//******************************************************
class While : public Node
{
    public :

        While(const int tokenLineNumber);

        std::string printTokenString() const;
};

#endif