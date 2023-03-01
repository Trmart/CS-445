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



//currenty working. Doesn't seem to have an errors. 3/1/23

Semantics::Semantics(SymbolTable* symbolTable) : m_symbolTable{symbolTable}
{

}

// Semantic Analysis
//currenty working. Doesn't seem to have an errors. 3/1/23

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

//currenty working. Doesn't seem to have an errors. 3/1/23
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

//currenty working. Doesn't seem to have an errors. 3/1/23
void Semantics::analyzeDeclarationNodeSemantics(const DeclarationNode* declaration)
{

    //check to make sure declaration is not nullptr
    if(!isDeclarationNode(declaration))
    {
        throw std::runtime_error("ERROR. Semantics::analyzeDeclarationNodeSemantics() - nullptr Declaration Node or Node is not of Declaration Type");
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

//currenty working. Doesn't seem to have an errors. 3/1/23
void Semantics::analyzeVariableNodeSemantics(Var* variable)
{
    //check if variable is nullptr and if node is of variable type
    if(!isVariableNode(variable))
    {
        throw std::runtime_error("ERROR. Semantics::analyzeVariableNodeSemantics() - Node is not of Variable Type");
    }

    // Global vars are always initialized
    if (m_symbolTable->depth() == 1 || variable->getNodeData()->getIsStatic())
    {
        variable->setInitialized();
    }

    
    //add to symbol table
    addToSymbolTable(variable);


}

//*********************Expression Nodes**********************


//seems to work up until checkOperands or CheckSameTypeOperands is called
//must have an error with one or both of these functions
//get a seg fault and a string length runtime error
void Semantics::analyzeAssignmentNodeSemantics(const Asgn* assignment)
{
    //check if node is a nullptr and if node is of assignment type

    if(!isAssignmentNode(assignment))
    {
        throw std::runtime_error("ERROR. Semantics::checkUnaryAssignmentOperands() - Node is not of Assignment Type OR Node is nullptr");
    }


    //check if left operand is declared
    std::vector<Node*> childrenNodes = assignment->getChildernNodes();

    //get left and right operands (childern Nodes)
    Node* leftHandSideNode = (Node* )(childrenNodes[0]);
    Node* righttHandSideNode = (Node* )(childrenNodes[1]);

    //analyze the right hand side
    analyzeAST(righttHandSideNode);

    setAndGetExpressionNodeData(assignment);

    //check if left hand side is an identifier
    if(isIdentifierNode(leftHandSideNode))
    {
        Id* leftHandSideIdentifier = (Id* )(leftHandSideNode);
        Var* previousDeclaration = (Var* )(getFromSymbolTable(leftHandSideIdentifier->getIdentifierName())); 
        

        //check if the previous declaration is a variable
        if(isVariableNode(previousDeclaration))
        {
            //mark the variable as initialized
            previousDeclaration->setInitialized();
        }
        else
        {
            //ERROR(7): Symbol 'x' is not declared.
            EmitDiagnostics::Error::emitGenericError(leftHandSideIdentifier->getTokenLineNumber(), "Symbol '"+ leftHandSideIdentifier->getIdentifierName() + "' is not declared."); 
        }
    }


    //the left hand side is not an identifier
    else
    {
        Binary* leftHandSideBinary = (Binary* )(childrenNodes[0]);

        Id* arrayIdentifier = (Id* )(leftHandSideBinary->getChildernNodes()[0]);

        Var* previousDeclaration = (Var* )(getFromSymbolTable(arrayIdentifier->getIdentifierName()));
        
        //check if node is not null
        if(isVariableNode(previousDeclaration))
        {
            //if node is not null, set initialized to true
            previousDeclaration->setInitialized();
        }

    }

    //switch assignment type

    switch (assignment->getAssignmentType())
    {
        case Asgn::Type::ASGN:
                                {
                                    //check if left and right operands are valid
                                    // checkSameTypeOperands((ExpressionNode*)(assignment));
                                }
                                break;
        case Asgn::Type::ADDASS:
                                {
                                    //check if left and right operands are valid
                                    // checkOperands((ExpressionNode*)(assignment), NodeData::Type::INT);
                                }
                                break;
        case Asgn::Type::SUBASS:
                                {
                                    //check if left and right operands are valid
                                    // checkOperands((ExpressionNode*)(assignment), NodeData::Type::INT);
                                }
                                break;
        case Asgn::Type::MULASS:
                                {
                                    //check if left and right operands are valid
                                    // checkOperands((ExpressionNode*)(assignment), NodeData::Type::INT);
                                }
                                break;
        case Asgn::Type::DIVASS:
                                {
                                    //check if left and right operands are valid
                                    // checkOperands((ExpressionNode*)(assignment), NodeData::Type::INT);
                                }
                                break;
        default:
            {
                throw std::runtime_error("ERROR. Semantics::analyzeAssignmentNodeSemantics() - Invalid Assignment Node Type");
            }
            break;
    }
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
    //check to make sure identifier is not nullptr and that it is an identifier node
    if(!isIdentifierNode(identifier))
    {
        throw std::runtime_error("ERROR. Semantics::analyzeIdentifierNodeSemantics() - nullptr Identifier Node");
    }

    setAndGetExpressionNodeData(identifier);

    //cast to declaration node
    //and get the declaration node from the symbol table
    DeclarationNode* previousDeclaration = (DeclarationNode* )(getFromSymbolTable(identifier->getIdentifierName()));
    
    //check if previous declaration is not null
    if(previousDeclaration == nullptr)
    {
        //ERROR(7): Symbol 'x' is not declared.
        EmitDiagnostics::Error::emitGenericError(identifier->getTokenLineNumber(), "Symbol '"+ identifier->getIdentifierName() + "' is not declared."); 
        return;
    }

    //check if previous declaration is a function node
    if(isFunctionNode(previousDeclaration))
    {
        //throw error
        EmitDiagnostics::Error::emitGenericError(identifier->getTokenLineNumber(), "Cannot use function '" + identifier->getIdentifierName() + "' as a variable.");

    }
    
    
    //check if previous declaration is a variable node
    if(isVariableNode(previousDeclaration))
    {
        //cast to variable node
        Var* previousDeclarationVariable = (Var* )(previousDeclaration);

        //set the varibale node to initialized
        previousDeclarationVariable->setInitialized();

        // Don't warn if the uninitialized id is an array index (see hw4/test/lhs.c-)
        if (!previousDeclarationVariable->getIsInitialized() && previousDeclarationVariable->getShowErrors())
        {
            if (!hasIndexAncestor((ExpressionNode* )identifier) || identifier->getIsArray())
            {
                if (!hasAssignmentAncestor((ExpressionNode* )identifier))
                {
                    EmitDiagnostics::Warning::emitGenericWarnings(identifier->getTokenLineNumber(), "Variable '" + identifier->getIdentifierName() + "' may be uninitialized when used here.");
                    previousDeclarationVariable->setShowErrors(false);
                }
            }
        }
    }

    //check if previous declaration is a parameter node
    if(isParameterNode(previousDeclaration))
    {
        //cast to parameter node
        Parm* previousDeclarationParameter = (Parm* )(previousDeclaration);

        //set the parameter node to initialized
        previousDeclarationParameter->setUsed();
    }
    
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


//seems to be working properly. No errors currently present. 3/1/23
void Semantics::analyzeForNodeSemantics() const
{
    //enter for into symbol table
    m_symbolTable->enter("For Loop");
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

//possibly have an error with this function
//get a seg fault and a string length runtime error when its called 3/1/23
void Semantics::checkSameTypeOperands(ExpressionNode* expression) const
{
    // if (!isExpressionNode(expression))
    // {
    //     throw std::runtime_error("Semantics::checkOperandsOfSameType() - Invalid Exp");
    // }
    // if (!expressionOperandsExist(expression))
    // {
    //     throw std::runtime_error("Semantics::checkOperandsOfSameType() - LHS and RHS Exp operands must exist");
    // }

    // //get teh symbol of the expression
    // std::string sym = getExpressionSymbol(expression);

    // //get the children of the expression
    // std::vector<Node* > childrenNodes = expression->getChildernNodes();
    
    // //cast the children to expression nodes. set lhs and rhs
    // ExpressionNode* leftHandSideExpression = (ExpressionNode *)(childrenNodes[0]);
    // ExpressionNode* rightHandSideExpression = (ExpressionNode *)(childrenNodes[1]);
    
    // NodeData* leftHandSideData = setAndGetExpressionNodeData(leftHandSideExpression);
    // NodeData* rightHandSideData = setAndGetExpressionNodeData(rightHandSideExpression);

    // // Ignore cases where the LHS has no type
    // if (leftHandSideData->getType() == NodeData::Type::UNDEFINED)
    // {
    //     expression->getNodeData()->setType(NodeData::Type::UNDEFINED);
    //     return;
    // }


    // // Both sides must be the same type
    // if (leftHandSideData->getType() != rightHandSideData->getType())
    // {
    //     EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires operands of the same type but lhs is type " + leftHandSideData->printTokenString() + " and rhs is type " + rightHandSideData->printTokenString() + ".");
    // }

    // // Both sides must be arrays or both must not be arrays
    // if (leftHandSideData->getIsArray() && !rightHandSideData->getIsArray())
    // {
    //     EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires both operands be arrays or not but lhs is an array and rhs is not an array.");
    // }
    // else if (!leftHandSideData->getIsArray() && rightHandSideData->getIsArray())
    // {
    //     EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires both operands be arrays or not but lhs is not an array and rhs is an array.");
    // }


    // //if both nodes are identifiers
    // if (isIdentifierNode(leftHandSideExpression) && isIdentifierNode(rightHandSideExpression))
    // {
    //     //cast the nodes to identifiers
    //     Id* leftHandSideIdentifier = (Id *)leftHandSideExpression;
    //     Id* rightHandSideIdentifier = (Id *)rightHandSideExpression;

    //     //if the identifiers are not the same
    //     if (leftHandSideIdentifier->getIdentifierName() != rightHandSideIdentifier->getIdentifierName())
    //     {
    //         //cast the nodes to declarations
    //         DeclarationNode* prevLhsDecl = (DeclarationNode *)(getFromSymbolTable(leftHandSideIdentifier->getIdentifierName()));
    //         DeclarationNode* prevRhsDecl = (DeclarationNode *)(getFromSymbolTable(rightHandSideIdentifier->getIdentifierName()));
            
    //         if ((isVariableNode(prevLhsDecl)) && (isVariableNode(prevRhsDecl)))
    //         {
    //             if (rightHandSideData->getCopyString() != leftHandSideIdentifier->getIdentifierName())
    //             {
    //                 leftHandSideData->setCopyString(rightHandSideIdentifier->getIdentifierName());
    //             }
    //         }
    //     }
    // }
}


//possibly have an error with this function
//get a seg fault and a string length runtime error when its called 3/1/23
void Semantics::checkOperands(ExpressionNode* expression, const NodeData::Type type) const
{
    // //check if the node is an expression node
    // if(!isExpressionNode(expression))
    // {
    //     throw std::runtime_error("ERROR. Semantics::checkOperands() - Node is not of Expression Type");
    // }

    // //check if operands exist
    // if(!expressionOperandsExist(expression))
    // {
    //     throw std::runtime_error("ERROR. Semantics::checkOperands() - Operands do not exist");
    // }

    // //get teh operand symbol
    // std::string symbol = getExpressionSymbol(expression);

    // //convert symbol type to string
    // std::string typeString = NodeData::convertTypeToString(type);

    // std::vector<Node *> childrenNodes = expression->getChildernNodes();
    
    // ExpressionNode* leftHandSideExpression = (ExpressionNode *)(childrenNodes[0]);
    // ExpressionNode* righttHandSideExpression = (ExpressionNode *)(childrenNodes[1]);
    
    // NodeData* leftHandSideData = setAndGetExpressionNodeData(leftHandSideExpression);
    // NodeData* rightHandSideData = setAndGetExpressionNodeData(righttHandSideExpression);

    // // Ignore cases where the LHS or RHS has no type
    // if (leftHandSideData->getType() == NodeData::Type::UNDEFINED || rightHandSideData->getType() == NodeData::Type::UNDEFINED)
    // {
    //     expression->getNodeData()->setType(NodeData::Type::UNDEFINED);
    //     return;
    // }

    // if (leftHandSideData->getType() != type)
    // {
    //     EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + symbol + "' requires operands of type " + typeString + " but lhs is of type " + leftHandSideData->printTokenString() + ".");
    // }

    // if (rightHandSideData->getType() != type)
    // {
    //     EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + symbol + "' requires operands of type " + typeString + " but rhs is of type " + rightHandSideData->printTokenString() + ".");
    // }

    // // If it is a binary operation, we want the operands to be only the passed type (not an array of that type)
    // if (isBinaryNode(expression))
    // {
    //     Binary *binary = (Binary *)expression;
        
    //     if (isIdentifierNode(leftHandSideExpression))
    //     {
    //         Id *leftHandSideIdentifier = (Id *)leftHandSideExpression;

    //         DeclarationNode *prevDeclaration = (DeclarationNode *)(getFromSymbolTable(leftHandSideIdentifier->getIdentifierName()));
    //         if ((prevDeclaration != nullptr && prevDeclaration->getNodeData()->getIsArray()) || leftHandSideIdentifier->getIsArray())
    //         {
    //             EmitDiagnostics::Error::emitGenericError(binary->getTokenLineNumber(), "The operation '" + binary->getSymbol() + "' does not work with arrays.");
    //             return;
    //         }
    //     }
    //     if (isIdentifierNode(righttHandSideExpression))
    //     {
    //         Id *rightHandSideIdentifier = (Id *)righttHandSideExpression;

    //         DeclarationNode *prevDeclaration = (DeclarationNode *)(getFromSymbolTable(rightHandSideIdentifier->getIdentifierName()));
            
    //         if ((prevDeclaration != nullptr && prevDeclaration->getNodeData()->getIsArray()) || rightHandSideIdentifier->getIsArray())
    //         {
    //             EmitDiagnostics::Error::emitGenericError(binary->getTokenLineNumber(), "The operation '" + binary->getSymbol() + "' does not work with arrays.");
    //             return;
    //         }
    //     }
    // }
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
    //check if the node is an expression node
    if(!isExpressionNode(expression))
    {
        throw std::runtime_error("ERROR. Semantics::expressionOperandsExist() - Node is not of Expression Type");
    }


    //retrieve the childern nodes
    std::vector<Node* > childernNodes = expression->getChildernNodes();

    //check if an operand exists
    if(childernNodes.size() < 2 || childernNodes[0] == nullptr || childernNodes[1] == nullptr)
    {
        return false;
    }

    //check if the childern nodes are expression nodes
    if(!isExpressionNode(childernNodes[0]) || !isExpressionNode(childernNodes[1]))
    {
        return false;
    }

    //return true if operands exist
    return true; 
}


bool Semantics::leftHandSideExists(const ExpressionNode* expression) const
{

}


std::string Semantics::getExpressionSymbol(const ExpressionNode* expression) const
{

}


//possibly have an error with this function
//get a seg fault and a string length runtime error when its called 3/1/23
NodeData* Semantics::setAndGetExpressionNodeData(const ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::setAndGetExpData() - Invalid Exp");
    }

    switch (expression->getExpressionNodeType())
    {
        case ExpressionNode::Type::ASSIGN:
                                        {
                                            Asgn* asgn = (Asgn *)expression;
                                            ExpressionNode* leftHandSideExpression = (ExpressionNode *)(expression->getChildernNodes()[0]);
                                            asgn->setNodeData(setAndGetExpressionNodeData(leftHandSideExpression));
                                        }
                                        break;
        case ExpressionNode::Type::BINARY:
                                        {
                                            Binary *binary = (Binary *)expression;
                                            
                                            if(binary->getBinaryType() == Binary::Type::INDEX)
                                            {
                                                Id *arrayIdentifier = (Id *)(binary->getChildernNodes()[0]);
                                                binary->setNodeData(new NodeData(setAndGetExpressionNodeData(arrayIdentifier)->getType(), false, false));
                                            }
                                        }
                                        break;
        case ExpressionNode::Type::CALL:
                                    {
                                        Call *call = (Call *)expression;
                                        
                                        DeclarationNode* prevDeclaration = getFromSymbolTable(call->getFunctionCallName());
                                        
                                        if(prevDeclaration != nullptr && !isVariableNode(prevDeclaration))
                                        {
                                            call->setNodeData(prevDeclaration->getNodeData());
                                        }
                                    }
                                    break;
        case ExpressionNode::Type::IDENTIFIER:
                                        {
                                            Id *identifier = (Id *)expression;
                                            
                                            DeclarationNode *prevDeclaration = getFromSymbolTable(identifier->getIdentifierName());
                                            
                                            if (prevDeclaration != nullptr && !isFunctionNode(prevDeclaration))
                                            {
                                                identifier->setNodeData(prevDeclaration->getNodeData());
                                            }
                                        }
                                        break;
    }

    return expression->getNodeData();
}



//********************Symbol Table Functions**********************


//currenty working. Doesn't seem to have an errors. 3/1/23

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

            if(variable->getIsUsed() == false && variable->getHasNotBeenUsed() == false)
            {
                EmitDiagnostics::Warning::emitGenericWarnings(variable->getTokenLineNumber(), "The variable '" + variable->getName() + "' seems not to be used.");
                variable->setHasNotBeenUsed();
            }
        }
        
        //check if node is a parameter node
        else if(isParameterNode(declaration))
        {
            //cast to a parameter node
            Parm* parameter = (Parm*)declaration;

            if(parameter->getIsUsed() == false && parameter->getHasNotBeenUsed() == false)
            {
                
                EmitDiagnostics::Warning::emitGenericWarnings(parameter->getTokenLineNumber(), "The variable '" + parameter->getName() + "' seems not to be used.");
                parameter->setHasNotBeenUsed();
            }
        }

    }

    if(m_symbolTable->depth() <= 1)
    {
        //dont leavescope if we are at the global scope
        return;
    }
    //leave the scope. call symbol table's leave function
    m_symbolTable->leave();
}



//currenty working. Doesn't seem to have an errors. 3/1/23

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



//currenty working. Doesn't seem to have an errors. 3/1/23

DeclarationNode* Semantics::getFromSymbolTable(const std::string name) const
{
    if(name.length() == 0)
    {
        throw std::runtime_error("ERROR. Semantics::getFromSymbolTable() - Empty Name");
    }

    DeclarationNode* previousDeclaration = (DeclarationNode* )(m_symbolTable->lookup(name));
    return previousDeclaration;
}