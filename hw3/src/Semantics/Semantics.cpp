/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: Semantics.hpp
DESC: Semantics Class Definitions.  For semantic analysis of AST

*/

#include "Semantics.hpp"



// Constructor
Semantics::Semantics(SymbolTable* symbolTable) : m_symbolTable{symbolTable}
{

}

// Semantic Analysis
void Semantics::analyze(Node* node)
{
    analyzeAST(node);

    // Check for main function
    if(!m_validMainExists)
    {
        EmitDiagnostics::Error::emitUndefinedMainError();
    }
}




//********************Analyzers**********************
void Semantics::analyzeAST(Node *node)
{

}

//*********************Declaration Nodes**********************
void Semantics::analyzeDeclarationNode(const DeclarationNode* declaration)
{

}


void Semantics::analyzeFunctionNode(const Func* func)
{

}


void Semantics::analyzeParmNode(const Parm* parm)
{

}


void Semantics::analyzeVariableNode(Var* var)
{

}

//*********************Expression Nodes**********************

void Semantics::analyzeAsgn(const Asgn* asgn)
{

}


void Semantics::analyzeBinaryNode(const Binary* binary) const
{

}


void Semantics::analyzeCallNode(const Call* call) const
{

}


void Semantics::analyzeExpressionNode(ExpressionNode* expression)
{

}


void Semantics::analyzeIdentifierNode(const Id* id) const
{

}


void Semantics::analyzeUnaryNode(const Unary* unary) const
{

}


void Semantics::analyzeUnaryAsgn(const UnaryAsgn* unaryAsgn) const
{

}

//*********************Statement Nodes**********************

void Semantics::analyzeCompoundNode(const Compound* compound) const
{

}


void Semantics::analyzeForNode() const
{

}


void Semantics::analyzeReturnNode(const Return* returnNode) const
{

}


void Semantics::analyzeStatementNode(const StatementNode* statement) const
{

}


//********************Symbol Checkers**********************

void Semantics::checkIndex(const Binary* binary) const
{

}


void Semantics::checkOperandsOfSameType(ExpressionNode* expression) const
{

}


void Semantics::checkOperandsOfType(ExpressionNode* expression, const NodeData::Type type) const
{

}


void Semantics::checkUnaryOperands(const Unary* unary) const
{

}


void Semantics::checkUnaryAsgnOperands(const UnaryAsgn* unaryAsgn) const
{

}


//********************Helper Functions**********************

bool Semantics::isMainFunc(const Func* func) const
{

}


bool Semantics::isDeclared(const Id* id) const
{

}


bool Semantics::hasIndexAncestor(const ExpressionNode* expression) const
{

}


bool Semantics::hasAsgnAncestor(const ExpressionNode* expression) const
{

}


bool Semantics::expOperandsExist(const ExpressionNode* expression) const
{

}


bool Semantics::lhsExists(const ExpressionNode* expression) const
{

}


std::string Semantics::getExpSym(const ExpressionNode* expression) const
{

}


NodeData* Semantics::setAndGetExpData(const ExpressionNode* expression) const
{

}



//********************Symbol Table Functions**********************


void Semantics::leaveScope()
{

}


bool Semantics::addToSymTable(const DeclarationNode* declaration, const bool global=false)
{

}


DeclarationNode* Semantics::getFromSymTable(const std::string name) const
{

}