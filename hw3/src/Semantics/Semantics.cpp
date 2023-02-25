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
    // Check if node is valid
    if(node == nullptr || node->getIsNodeAnalyzed())
    {
        return;
    }

    // Set node as analyzed
    node->setIsNodeAnalyzed(true);

    // Check what type of node it is
    switch(node->getNodeType())
    {
        case Node::Type::DECLARATION:
                                        {
                                            DeclarationNode* declaration = (DeclarationNode*)node;
                                            analyzeDeclarationNode(declaration);
                                        }
                                        break;
        case Node::Type::EXPRESSION:
                                        {
                                            ExpressionNode* expression = (ExpressionNode*)node;
                                            analyzeExpressionNode(expression);
                                        }
                                        break;
        case Node::Type::STATEMENT:
                                        {
                                            StatementNode* statement = (StatementNode*)node;
                                            
                                            if(statement->getStatementNodeType() == StatementNode::Type::RANGE)
                                            {
                                                return; // Range statements are not analyzed
                                            }
                                            
                                            analyzeStatementNode(statement);
                                        }
                                        break;
        
        case Node::Type::NONE:
                            {
                                throw std::runtime_error("Semantics::analyzeAST: AST Node Has Type None");
                            }
                            break;
        default:
            {
                throw std::runtime_error("Semantics::analyzeAST: Invalid AST Node : Unknown Type");
            }
            break;
    }


    // Recursively analyze children
    for (Node* child : node->getChildernNodes())
    {
        analyzeAST(child);
    }

    if (isFunctionNode(node))
    {
        leaveScope();
    }
    else if (isForNode(node))
    {
        leaveScope();
    }
    else if (isCompoundNode(node))
    {
        StatementNode* statement = (StatementNode*)node;

        if(!isFunctionNode(statement->getParentNode()) && !isForNode(statement->getParentNode()))
        {
            leaveScope();
        }
    }

    //analyze sibling node
    analyzeAST(node->getSiblingNode());
}

//*********************Declaration Nodes**********************
void Semantics::analyzeDeclarationNode(const DeclarationNode* declaration)
{
    // Check if declaration is valid
    if (!isDeclarationNode(declaration))
    {
        throw std::runtime_error("Semantics::analyzeDeclarationNode: Invalid Declaration Node");
    }

    switch (declaration->getDeclarationNodeType())
    {
        case DeclarationNode::Type::FUNCTION:
                                        {
                                            Func* func = (Func*)declaration;
                                            analyzeFunctionNode(func);
                                        }
                                        break;
        case DeclarationNode::Type::VARIABLE:
                                        {
                                            Var* var = (Var*)declaration;
                                            analyzeVariableNode(var);
                                        }
                                        break;
        case DeclarationNode::Type::PARAMETER:
                                        {
                                            Parm* parm = (Parm*)declaration;
                                            analyzeParmNode(parm);
                                        }
                                        break;
                                    
        
        default:
            {
                throw std::runtime_error("Semantics::analyzeDeclarationNode: Invalid Declaration Node");
            }
            break;
    }
    
}


void Semantics::analyzeFunctionNode(const Func* func)
{
    // Check if func is valid
    if(!isFunctionNode(func))
    {
        throw std::runtime_error("Semantics::analyzeFunctionNode: Invalid Function Node");
    }

    // Add function to symbol table
    addToSymTable(func);

    // Check for main function
    if(isMainFunc(func))
    {
        m_validMainExists = true;
    }

    // Check for duplicate function
    m_symbolTable->enter("Function: " + func->getName());
}


void Semantics::analyzeParmNode(const Parm* parm)
{
    // Check if parm is valid
    if(!isParameterNode(parm))
    {
        throw std::runtime_error("Semantics::analyzeParmNode: Invalid Parm Node");
    }
    
    // Add parm to symbol table
    addToSymTable(parm);
}


void Semantics::analyzeVariableNode(Var* var)
{
    if (!isVariableNode(var))
    {
        throw std::runtime_error("Semantics::analyzeVariableNode: Invalid Variable Node");
    }
    
    if(m_symbolTable->depth() == 1 || var->getNodeData()->getIsStatic())
    {
        var->setInitialized(); 
    }
    
    addToSymTable(var);
}

//*********************Expression Nodes**********************

void Semantics::analyzeAssignmentNode(const Asgn* asgn)
{
    if (!isAssignmentNode(asgn))
    {
        throw std::runtime_error("Semantics::analyzeAssignmentNode() - Invalid Assignment Node");
    }

    // Get LHS and RHS
    std::vector<Node* > children = asgn->getChildernNodes();
    Node *lhsNode = (Node* )(children[0]);
    Node *rhsNode = (Node* )(children[1]);

    // Analyze LHS and RHS
    analyzeAST(rhsNode);

    // set and get exp data
    setAndGetExpData(asgn);

    // Check if LHS is an id
    if (isIdentifierNode(lhsNode))
    {
        // Check if LHS is a variable
        Id* lhsId = (Id* )(lhsNode);
        Var* prevDeclLhsVar = (Var* )(getFromSymTable(lhsId->getIdentifierName()));
        
        // Check if LHS is a variable
        if (isVariableNode(prevDeclLhsVar))
        {
            prevDeclLhsVar->setInitialized();
        }
    }
    else
    {
        // Check if LHS is an array
        Binary *lhsBinary = (Binary *)(children[0]);
        
        // Get array id
        Id *arrayId = (Id *)(lhsBinary->getChildernNodes()[0]);
        // Get array index
        Var *prevDeclArrayVar = (Var *)(getFromSymTable(arrayId->getIdentifierName()));
        
        // Check if LHS is an array
        if (prevDeclArrayVar != nullptr)
        {
            prevDeclArrayVar->setInitialized();
        }
    }

    switch (asgn->getAssignmentType())
    {
        case Asgn::Type::ASGN:
                            {
                                checkOperandsOfSameType((ExpressionNode* )asgn);
                            }
                            break;
        case Asgn::Type::ADDASS:
                            {
                                checkOperandsOfType((ExpressionNode* )asgn, NodeData::Type::INT);
                            }
                            break;
        case Asgn::Type::SUBASS:
                            {
                                checkOperandsOfType((ExpressionNode* )asgn, NodeData::Type::INT);
                            }
                            break; 
        case Asgn::Type::DIVASS:
                            {
                                checkOperandsOfType((ExpressionNode* )asgn, NodeData::Type::INT);
                            }
                            break;
        case Asgn::Type::MULASS:
                            {
                                checkOperandsOfType((ExpressionNode* )asgn, NodeData::Type::INT);
                            }
                            break; 

        default:
            {
                throw std::runtime_error("Semantics::analyzeAsgn() - Unknown Assignment Type");
            }
            break;
    }
}


void Semantics::analyzeBinaryNode(const Binary* binary) const
{
    
    // Check if binary is valid
    if (!isBinaryNode(binary))
    {
        throw std::runtime_error("Semantics::analyzeBinaryNode() - Invalid Binary");
    }
    if (!expOperandsExist((ExpressionNode* )binary))
    {
        throw std::runtime_error("Semantics::analyzeBinaryNode() - LHS and RHS Expression Operands must exist");
    }

    setAndGetExpData(binary);

    switch (binary->getBinaryType())
    {
        case Binary::Type::MUL:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::DIV:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::MOD:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::ADD:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::INT);
                            }
                            break;

        case Binary::Type::SUB:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::INDEX:
                            {
                                checkIndex(binary);
                            }
                            break;
        case Binary::Type::And:
        case Binary::Type::Or:
            checkOperandsOfType((Exp *)binary, Data::Type::Bool);
            break;
        case Binary::Type::LT:
        case Binary::Type::LEQ:
        case Binary::Type::GT:
        case Binary::Type::GEQ:
        case Binary::Type::EQ:
        case Binary::Type::NEQ:
            checkOperandsOfSameType((Exp *)binary);
            break;
        default:
            {
                throw std::runtime_error("Semantics::analyzeBinaryNode() - Unknown Binary Type");
            }
            break;
    }
}


void Semantics::analyzeCallNode(const Call* call) const
{

}


void Semantics::analyzeExpressionNode(ExpressionNode* expression)
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::analyzeExpressionNode() - Invalid Exp");
    }

    switch (expression->getExpressionNodeType())
    {
        case ExpressionNode::Type::ASSIGN:
                                        {
                                            analyzeAsgn((Asgn* )expression);
                                        }
                                        break;
        case ExpressionNode::Type::BINARY:
                                        {
                                            analyzeBinaryNode((Binary* )expression);
                                        }
                                        break;

        case ExpressionNode::Type::CALL:
                                        {
                                            analyzeCallNode((Call* )expression);
                                        }
                                        break;
        case ExpressionNode::Type::CONSTANT:
            // Not analyzed
            break;
        case ExpressionNode::Type::IDENTIFIER:
                                        {
                                            analyzeIdentifierNode((Id* )expression);
                                        }
                                        break;
        case ExpressionNode::Type::UNARY:
                                        {
                                            analyzeUnaryNode((Unary* )expression);
                                        }
                                        break;  

        case ExpressionNode::Type::UNARYASSIGN:
                                        {
                                            analyzeUnaryAsgn((UnaryAsgn* )expression);
                                        }
                                        break;

        default:
            {
                throw std::runtime_error("Semantics::analyzeExpressionNode() - Unknown Expression Type");
            }
            break;
    }
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