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
    //possible needed for hw4
    
    // if(!m_validMainExists)
    // {
    //     EmitDiagnostics::Error::emitUndefinedMainError();
    // }
}




//********************Analyzers**********************
void Semantics::analyzeAST(Node *node)
{
    //check if node is nullptr
    if(node == nullptr || node->getIsNodeAnalyzed())
    {
        return;
    }

    //set node to analyzed
    node->setIsNodeAnalyzed();


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
                                    
                                    //check if node is a Range node
                                    if(statement->getStatementNodeType() == StatementNode::Type::RANGE)
                                    {
                                        return;
                                    }
                                    
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

    //analyze children

    std::vector<Node*> childrenNodes = node->getChildernNodes();
    for(int i = 0; i < childrenNodes.size(); i++)
    {
        analyzeAST(childrenNodes[i]);
    }
    //check if node is a function node
    if(isFunctionNode(node))
    {
        //leave scope
        leaveScope();
    }

    //check if node is a paramter node
    else if(isForNode(node))
    {
        //leave scope
        leaveScope();
    }

    //check if node is a Compound node
    else if(isCompoundNode(node))
    {
        // Don't leave the scope if the parent is a func or for
        StatementNode* statement = (StatementNode *)node;
        if (!isFunctionNode(statement->getParentNode()) && !isForNode(statement->getParentNode()))
        {
            leaveScope();
        }
    }


    //analyze sibling node
    analyzeAST(node->getSiblingNode());

}

//*********************Declaration Nodes**********************


void Semantics::analyzeDeclarationNodeSemantics(const DeclarationNode* declaration)
{

    //check to make sure declaration is not nullptr
    if(declaration == nullptr)
    {
        throw std::runtime_error("ERROR. Semantics::analyzeDeclarationNodeSemantics() - nullptr Declaration Node");
    }

    //check if node is of declaration type
    if(declaration->getNodeType() != Node::Type::DECLARATION)
    {
        throw std::runtime_error("ERROR. Semantics::analyzeDeclarationNodeSemantics() - Node is not of Declaration Type");
    }

    //switch on declaration node type
    switch (declaration->getDeclarationNodeType())
    {
        case DeclarationNode::Type::FUNCTION:
                                        {
                                            const Func* function = (const Func*)declaration;
                                            analyzeFunctionNodeSemantics(function);
                                        }
                                        break;
        case DeclarationNode::Type::PARAMETER:
                                        {
                                            const Parm* parameter = (const Parm*)declaration;
                                            analyzeParmNodeSemantics(parameter);
                                        }
                                        break;

        case DeclarationNode::Type::VARIABLE:
                                        {
                                            Var* variable = (Var*)declaration;
                                            analyzeVariableNodeSemantics(variable);
                                        }
                                        break; 

        default:
            {
                throw std::runtime_error("ERROR. Semantics::analyzeDeclarationNodeSemantics() - Invalid Declaration Node Type");
            }
            break;
    }
}


void Semantics::analyzeFunctionNodeSemantics(const Func* function)
{

}


void Semantics::analyzeParmNodeSemantics(const Parm* parameter)
{

}


void Semantics::analyzeVariableNodeSemantics(Var* variable)
{
    //check if variable is nullptr
    if(variable == nullptr)
    {
        throw std::runtime_error("ERROR. Semantics::analyzeVariableNodeSemantics() - nullptr Variable Node");
    }

    //check if node is of variable type
    if(!isVariableNode(variable))
    {
        throw std::runtime_error("ERROR. Semantics::analyzeVariableNodeSemantics() - Node is not of Variable Type");
    }


    
    //add to symbol table
    addToSymbolTable(variable);


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
    //check to make sure expression is not nullptr
    if(expression == nullptr)
    {
        throw std::runtime_error("ERROR. Semantics::analyzeExpressionNodeSemantics() - nullptr Expression Node");
    }

    //check if node is of expression type
    if(!isExpressionNode(expression))
    {
        throw std::runtime_error("ERROR. Semantics::analyzeExpressionNodeSemantics() - Node is not of Expression Type");
    }

    switch(expression->getExpressionNodeType())
    {
        case ExpressionNode::Type::ASSIGN:
                                        {
                                            const Asgn* assignment = (const Asgn*)expression;
                                            analyzeAssignmentNodeSemantics(assignment);
                                        }
                                        break;

        case ExpressionNode::Type::BINARY:
                                        {
                                            const Binary* binary = (const Binary*)expression;
                                            analyzeBinaryNodeSemantics(binary);
                                        }
                                        break;
        case ExpressionNode::Type::CALL:
                                        {
                                            const Call* call = (const Call*)expression;
                                            analyzeCallNodeSemantics(call);
                                        }
                                        break;
        case ExpressionNode::Type::CONSTANT:
                                        {
                                            //do nothing
                                            //constant nodes do not need to be analyzed
                                        }
                                        break;
        case ExpressionNode::Type::IDENTIFIER:
                                        {
                                            const Id* identifier = (const Id*)expression;
                                            analyzeIdentifierNodeSemantics(identifier);
                                        }
                                        break;

        case ExpressionNode::Type::UNARY:
                                        {
                                            const Unary* unary = (const Unary*)expression;
                                            analyzeUnaryNodeSemantics(unary);
                                        }
                                        break;

        case ExpressionNode::Type::UNARYASSIGN:
                                        {
                                            const UnaryAsgn* unaryAssignment = (const UnaryAsgn*)expression;
                                            analyzeUnaryAsssignmentNodeSemantics(unaryAssignment);
                                        }
                                        break;

        default:
            {
                throw std::runtime_error("ERROR. Semantics::analyzeExpressionNodeSemantics() - Invalid Expression Node Type");
            }
            break;
    }
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
        //check to make sure declaration is not nullptr
    if(statement == nullptr)
    {
        throw std::runtime_error("ERROR. Semantics::analyzeStatmentNodeSemantics() - nullptr Statement Node");
    }

    //check if node is of declaration type
    if(!isStatementNode(statement))
    {
        throw std::runtime_error("ERROR. Semantics::analyzeStatmentNodeSemantics() - Node is not of Statement Type");
    }

    //switch on declaration node type
    switch (statement->getStatementNodeType())
    {
        case StatementNode::Type::BREAK:
                                        {
                                            //do nothing? 
                                            //is break analyzed??
                                        }
                                        break; 
        
        case StatementNode::Type::COMPOUND:
                                        {
                                            const Compound* compound = (const Compound*)statement;
                                            analyzeCompoundNodeSemantics(compound);
                                        }
                                        break; 

        case StatementNode::Type::FOR:
                                        {
                                            const For* forNode = (const For*)statement;
                                            analyzeForNodeSemantics();
                                        }
                                        break; 
        case StatementNode::Type::IF:
                                        {
                                            //do nothing? 
                                            //is if analyzed??
                                        }
                                        break;
        case StatementNode::Type::RETURN:
                                        {
                                            const Return* returnNode = (const Return*)statement;
                                            analyzeReturnNodeSemantics(returnNode);
                                        }
                                        break;
        case StatementNode::Type::RANGE:
                                        {
                                            throw std::runtime_error("ERROR. Semantics::analyzeStatmentNodeSemantics() - RANGE Statement Node Type");
                                        }
                                        break;
        
        case StatementNode::Type::WHILE:
                                        {
                                           //do nothing?
                                           //is while analyzed??
                                        }
                                        break; 
        default:
            {
                throw std::runtime_error("ERROR. Semantics::analyzeStatmentNodeSemantics() - Invalid Statement Node Type");
            }
            break;
    }
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
    //get the symbols from symbol table
    std::map<std::string, void*> symbols = m_symbolTable->getSymbols();

    //iterate through the symbols
    for(auto const& [name, value]: symbols)
    {
        Node* node = (Node*)value;

        //check if the node is a declaration node
        if (!isDeclarationNode(node))
        {
            throw std::runtime_error("ERROR. Semantics::leaveScope() - illegal node in symbol table");
        }
        
        DeclarationNode* declaration = (DeclarationNode*)node;

        //check if the decalration is a variable
        if(isVariableNode(declaration))
        {
            //cast to a variable node 
            Var* variable = (Var*)declaration;

            if(variable->getIsUsed() == false)
            {
                EmitDiagnostics::Warning::emitGenericWarnings(variable->getTokenLineNumber(), "The variable '" + variable->getName() + "' seems not to be used.");
            }
        }
        
        //check if node is a parameter node
        else if(isParameterNode(declaration))
        {
            //cast to a parameter node
            Parm* parameter = (Parm*)declaration;

            if(parameter->getIsUsed() == false)
            {
                EmitDiagnostics::Warning::emitGenericWarnings(parameter->getTokenLineNumber(), "The variable '" + parameter->getName() + "' seems not to be used.");
            }
        }

    }

    //leave the scope. call symbol table's leave function
    m_symbolTable->leave();
}


bool Semantics::addToSymbolTable(const DeclarationNode* declaration, const bool global)
{
    if (!isDeclarationNode(declaration))
    {
        throw std::runtime_error("Semantics::addToSymTable() - Invalid Decl");
    }

    bool inserted = false;
    if (global)
    {
        inserted = m_symbolTable->insertGlobal(declaration->getName(), (void *)declaration);
    }
    else
    {
        inserted = m_symbolTable->insert(declaration->getName(), (void *)declaration);
    }

    if (!inserted)
    {
        DeclarationNode *prevDecl = (DeclarationNode *)(getFromSymbolTable(declaration->getName()));
        if (prevDecl == nullptr)
        {
            throw std::runtime_error("Semantics::addToSymTable() - Failed to insert Decl");
        }
        std::stringstream msg;
        msg << "Symbol '" << declaration->getName() << "' is already declared at line " << prevDecl->getTokenLineNumber() << ".";
        EmitDiagnostics::Error::emitGenericError(declaration->getTokenLineNumber(), msg.str());
    }

    return inserted;
}


DeclarationNode* Semantics::getFromSymbolTable(const std::string name) const
{
    if(name.length() == 0)
    {
        throw std::runtime_error("ERROR. Semantics::getFromSymbolTable() - Empty Name");
    }

    DeclarationNode* previousDeclaration = (DeclarationNode* )(m_symbolTable->lookup(name));
    return previousDeclaration;
}