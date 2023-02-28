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



Semantics::Semantics(SymbolTable* symbolTable) : m_symbolTable{symbolTable}
{

}

// Semantic Analysis
void Semantics::semanticAnalysis(Node* node)
{
    //call the unction to analyze the AST
    analyzeAST(node);


    //check if valid main exists and emit error if not
    if(!m_validMainExists)
    {
        EmitDiagnostics::Error::emitUndefinedMainError();
    }
}




//********************Analyzers**********************
void Semantics::analyzeAST(Node *node)
{
    //check if node is nullptr
    if(node == nullptr)
    {
        throw std::runtime_error("ERROR. Semantics::analyzeAST() -  Cannot Analyze Node; nullptr passed");
    }

    //switch on node type
    switch (node->getNodeType())
    {
        case Node::Type::DECLARATION:
                                {
                                    DeclarationNode* declaration = (DeclarationNode*)node;
                                    analyzeDeclarationNodeSemantics(declaration);
                                }
                                break;

        case Node::Type::EXPRESSION:
                                {
                                    ExpressionNode* expression = (ExpressionNode*)node;
                                    analyzeExpressionNodeSemantics(expression);
                                }
                                break; 
        
        case Node::Type::STATEMENT:
                                {
                                    StatementNode* statement = (StatementNode*)node;
                                    analyzeStatementNodeSemantics(statement);
                                }
                                break;
        case Node::Type::NONE:
                        {
                            throw std::runtime_error("ERROR. Semantics::analyzeAST() - NONE Node Type");
                        }
                        break;
        default:
            {
                throw std::runtime_error("ERROR. Semantics::analyzeAST() - Invalid Node Type");
            }
            break;
    }
}

//*********************Declaration Nodes**********************


void Semantics::analyzeDeclarationNodeSemantics(const DeclarationNode* declaration)
{

}


void Semantics::analyzeFunctionNodeSemantics(const Func* function)
{

}


void Semantics::analyzeParmNodeSemantics(const Parm* parameter)
{

}


void Semantics::analyzeVariableNodeSemantics(Var* variable)
{

}

//*********************Expression Nodes**********************


void Semantics::analyzeAssignmentNodeSemantics(const Asgn* assignment)
{

}


void Semantics::analyzeBinaryNodeSemantics(const Binary* binary) const
{

}


void Semantics::analyzeCallNodeSemantics(const Call* call) const
{

}


void Semantics::analyzeExpressionNodeSemantics(ExpressionNode* expression)
{

}


void Semantics::analyzeIdentifierNodeSemantics(const Id* identifier) const
{

}


void Semantics::analyzeUnaryNodeSemantics(const Unary* unary) const
{

}


void Semantics::analyzeUnaryAsssignmentNodeSemantics(const UnaryAsgn* unaryAssignment) const
{

}

//*********************Statement Nodes**********************


void Semantics::analyzeCompoundNodeSemantics(const Compound* compound) const
{

}


void Semantics::analyzeForNodeSemantics() const
{

}


void Semantics::analyzeReturnNodeSemantics(const Return* returnNode) const
{

}


void Semantics::analyzeStatementNodeSemantics(const StatementNode* statement) const
{

}


//********************Symbol Checkers**********************


void Semantics::checkIndex(const Binary* binary) const
{

}


void Semantics::checkSameTypeOperands(ExpressionNode* expression) const
{

}


void Semantics::checkOperands(ExpressionNode* expression, const NodeData::Type type) const
{

}


void Semantics::checkUnaryOperands(const Unary* unary) const
{

}


void Semantics::checkUnaryAssignmentOperands(const UnaryAsgn* unaryAssignment) const
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


bool Semantics::hasAssignmentAncestor(const ExpressionNode* expression) const
{

}


bool Semantics::expressionOperandsExist(const ExpressionNode* expression) const
{

}


bool Semantics::leftHandSideExists(const ExpressionNode* expression) const
{

}


std::string Semantics::getExpressionSymbol(const ExpressionNode* expression) const
{

}


NodeData* Semantics::setAndGetExpressionNodeData(const ExpressionNode* expression) const
{

}



//********************Symbol Table Functions**********************


void Semantics::leaveScope()
{

}


bool Semantics::addToSymbolTable(const DeclarationNode* declaration, const bool global=false)
{

}


DeclarationNode* Semantics::getFromSymbolTable(const std::string name) const
{

}