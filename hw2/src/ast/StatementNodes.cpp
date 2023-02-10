#include "StatementNodes.hpp"


StatementNode::StatementNode(const int tokenLineNumber, const StatementNode::Type statementType)
{

}

StatementNode::Type getTypeOfStatement() const
{

}


class BreakNode : public StatementNode
{
    public :
        BreakNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};



class CompoundNode : public StatementNode
{

    public :

        CompoundNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};

class ForNode : public StatementNode
{
    public :

        ForNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};



class IfNode : public StatementNode
{
    public :

        IfNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};




class RangeNode : public StatementNode
{
    public :

        RangeNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};


class ReturnNode : public StatementNode
{
    public :

        ReturnNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};


class WhileNode : public StatementNode
{
    public :

        WhileNode(const int tokenLineNumber);

        std::string printTokenString() const override;
};