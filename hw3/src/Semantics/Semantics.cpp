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



//**************************************************
//********************Analyzers**********************
//**************************************************


void Semantics::analyzeAST(Node *node)
{
    // Check if node is valid
    if(node == nullptr || node->getIsNodeAnalyzed())
    {
        return;
    }

    // Set node as analyzed
    node->setIsNodeAnalyzed();

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
    std:: vector<Node*> children = node->getChildernNodes();
    for (int i = 0; i < children.size(); i++)
    {
        analyzeAST(children[i]);
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


//****************************************************************  
//*********************Declaration Nodes**********************
//****************************************************************


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


//****************************************************************
//*********************Expression Nodes**********************
//****************************************************************

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
        case Binary::Type::AND:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::BOOL);
                            }
                            break; 
        case Binary::Type::OR:
                            {
                                checkOperandsOfType((ExpressionNode* )binary, NodeData::Type::BOOL);
                            }
                            break;
        
        case Binary::Type::LT:
                            {
                                checkOperandsOfSameType((ExpressionNode *)binary);
                            }
                            break; 
        
        case Binary::Type::LEQ:
                            {
                                checkOperandsOfSameType((ExpressionNode *)binary);
                            }
                            break;
                        
        case Binary::Type::GT:
                            {
                                checkOperandsOfSameType((ExpressionNode *)binary);
                            }
                            break; 
        case Binary::Type::GEQ:
                            {
                                checkOperandsOfSameType((ExpressionNode *)binary);
                            }
                            break;
        
        case Binary::Type::EQ:
                            {
                                checkOperandsOfSameType((ExpressionNode *)binary);
                            }
                            break;

        case Binary::Type::NEQ:
                            {
                                checkOperandsOfSameType((ExpressionNode *)binary);
                            }
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
    // Check if call is valid
    if (!isCallNode(call))
    {
        throw std::runtime_error("Semantics::analyzeCallNode() - Invalid Call");
    }

    setAndGetExpData(call);

    DeclarationNode* prevDecl = (DeclarationNode* )(getFromSymTable(call->getFunctionCallName()));

    // If the function name is not in the symbol table
    if (prevDecl == nullptr)
    {
        EmitDiagnostics::Error::emitGenericError(call->getTokenLineNumber(), "Symbol '" + call->getFunctionCallName() + "' is not declared.");
        return;
    }

    // If the function name is not associated with a function
    if (!isFunctionNode(prevDecl))
    {
        EmitDiagnostics::Error::emitGenericError(call->getTokenLineNumber(), "'" + call->getFunctionCallName() + "' is a simple variable and cannot be called.");
        if (isVariableNode(prevDecl))
        {
            Var *var = (Var *)prevDecl;
            var->setUsed();
        }
        else if (isParameterNode(prevDecl))
        {
            Parm *parm = (Parm *)prevDecl;
            parm->setUsed();
        }
        return;
    }
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
                                            analyzeAssignmentNode((Asgn* )expression);
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
                                            analyzeUnaryAsssignmentNode((UnaryAsgn* )expression);
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
    // Check if id is valid
    if(!isIdentifierNode(id))
    {
        throw std::runtime_error("Semantics::analyzeIdentifierNode() - Invalid Identifier");
    }

    // Check if the identifier is a function
    setAndGetExpData(id);

    DeclarationNode* prevDecl = (DeclarationNode* )(getFromSymTable(id->getIdentifierName()));
    
    // If the identifier is not in the symbol table
    if(prevDecl == nullptr)
    {
        EmitDiagnostics::Error::emitGenericError(id->getTokenLineNumber(), "Symbol '" + id->getIdentifierName() + "' is not declared.");
        return;
    }
    
    // If the identifier is a function
    if (isFunctionNode(prevDecl))
    {
        // If the identifier is a function, it cannot be used as a variable
        EmitDiagnostics::Error::emitGenericError(id->getTokenLineNumber(), "Cannot use function '" + id->getIdentifierName() + "' as a variable.");
        return;
    }  

    else if (isVariableNode(prevDecl))
    {
        // Mark the function as used
        Var* prevDeclVar = (Var* )prevDecl;
        prevDeclVar->setUsed();

        // Check if the variable is initialized
        if (!prevDeclVar->getIsInitialized() && prevDeclVar->getShowErrors())
        {   
            // If the variable is not initialized, check if it is an array or if it is used in an assignment
            if (!hasIndexAncestor((ExpressionNode* )id) || id->getIsArray())
            {
                // If the variable is not initialized, check if it is used in an assignment
                if (!hasAsgnAncestor((ExpressionNode* )id))
                {
                    EmitDiagnostics::Warning::emitGenericWarnings(id->getTokenLineNumber(), "Variable '" + id->getIdentifierName() + "' may be uninitialized when used here.");
                    prevDeclVar->setShowErrors(false);
                }
            }
        }

    } 
    
    else if (isParameterNode(prevDecl))
    {
        Parm* prevDeclParm = (Parm* )prevDecl;
        prevDeclParm->setUsed();
    }
}


void Semantics::analyzeUnaryNode(const Unary* unary) const
{
    // Check if unary is valid
    if (!isUnaryNode(unary))
    {
        throw std::runtime_error("Semantics::analyzeUnaryNode() - Invalid Unary Type");
    }

    // set the data of the unary node
    setAndGetExpData(unary);

    // Check the operands of the unary node
    checkUnaryOperands(unary);

}


void Semantics::analyzeUnaryAsssignmentNode(const UnaryAsgn* unaryAsgn) const
{
    // Check if unaryAsgn is valid
    if (!isUnaryAssignmentNode(unaryAsgn))
    {
        throw std::runtime_error("Semantics::analyzeUnaryAsssignmentNode() - Invalid UnaryAsgn Type");
    }

    // set the data of the unaryAsgn node
    setAndGetExpData(unaryAsgn);

    // Check the operands of the unaryAsgn node
    checkUnaryAsgnOperands(unaryAsgn);
}


//*********************************************************
//*********************Statement Nodes**********************
//*********************************************************


void Semantics::analyzeCompoundNode(const Compound* compound) const
{
    // Check if compound is valid
    if (!isCompoundNode(compound))
    {
        throw std::runtime_error("Semantics::analyzeCompound() - Invalid Compound");
    }

    // Ignore compounds following func or for
    if (!isFunctionNode(compound->getParentNode()) && !isForNode(compound->getParentNode()))
    {
        // Enter the compound statement
        m_symbolTable->enter("Compound Statement");
    }
}


void Semantics::analyzeForNode() const
{
    // enter the for loop
    m_symbolTable->enter("For Loop");
}


void Semantics::analyzeReturnNode(const Return* returnNode) const
{
    // Check if returnNode is valid
    if (!isReturnNode(returnNode))
    {
        throw std::runtime_error("Semantics::analyzeReturnNode() - Invalid Return Type");
    }

    // get the function that the return node is in
    std::vector<Node* > children = returnNode->getChildernNodes();
    
    
    // Check if the return node is in a function
    if (children.size() > 0)
    {
        ExpressionNode* returnChild = (ExpressionNode* )(children[0]);
        
        // Check if the return node is in a function
        if (isIdentifierNode(returnChild))
        {
            // Check if the return node is in a function 
            Id* id = (Id* )returnChild;
            DeclarationNode* prevDeclaration = (DeclarationNode* )(getFromSymTable(id->getIdentifierName()));
            
            // Check if the return node is in a function trying to return an array
            if ((prevDeclaration != nullptr && prevDeclaration->getNodeData()->getIsArray()) || id->getIsArray())
            {
                EmitDiagnostics::Error::emitGenericError(returnNode->getTokenLineNumber(), "Cannot return an array.");
            }
        }
    }
}


void Semantics::analyzeStatementNode(const StatementNode* statement) const
{
     if (!isStatementNode(statement))
    {
        throw std::runtime_error("Semantics::analyzeStatementNode() - Invalid Statement");
    }

    switch (statement->getStatementNodeType())
    {
        case StatementNode::Type::BREAK:
                                    {
                                    
                                        // Break Is Not analyzed
                                    }
                                    break;
        
        case StatementNode::Type::COMPOUND:
                                        {
                                            Compound* compound = (Compound* )statement;
                                            analyzeCompoundNode(compound);
                                        }
                                        break;
        
        case StatementNode::Type::FOR:
                                    {
                                        analyzeForNode();
                                    }
                                    break; 
        
        case StatementNode::Type::IF:
                                    {
                                        // If Is Not analyzed
                                    }
                                    break;
        
        case StatementNode::Type::RANGE:
                                    {

                                        throw std::runtime_error("Semantics::analyzeStatmentNode() - Range Type Not Implemented");
                                    }
                                    break;
        
        case StatementNode::Type::RETURN:
                                    {
                                        Return* returnStatement = (Return* )statement;
                                        analyzeReturnNode(returnStatement);
                                    }
                                    break;
        
        case StatementNode::Type::WHILE:
                                    {
                                        // While Is Not analyzed
                                    }
                                    break;
        
        default:
        {
            throw std::runtime_error("Semantics::analyzeStatementNode() - Unknown Type");
        }
        break;
    }
}



//**************************************************
//********************Symbol Checkers**********************
//**************************************************


void Semantics::checkIndex(const Binary* binary) const
{

    // Check if binary is valid
    if (binary->getBinaryType() != Binary::Type::INDEX)
    {
        throw std::runtime_error("Semantics::checkIndex() - Invalid Binary");
    }

    // Get the children of the binary node
    std::vector<Node* > children = binary->getChildernNodes();
    Id* arrayIdentifier = (Id* )(children[0]);
    ExpressionNode* indexExpression = (ExpressionNode* )(children[1]);

    // Check if the index expression is valid
    if (!isExpressionNode(indexExpression))
    {
        throw std::runtime_error("Semantics::checkIndex() - Invalid Binary");
    }

    NodeData* arrayIdentifierData = setAndGetExpData(arrayIdentifier);
    if (arrayIdentifierData->getType() == NodeData::Type::UNDEFINED)
    {
        binary->getNodeData()->setType(NodeData::Type::UNDEFINED);
    }

    DeclarationNode* prevArrayDeclaration = (DeclarationNode* )(getFromSymTable(arrayIdentifier->getIdentifierName()));
    if (prevArrayDeclaration == nullptr || !prevArrayDeclaration->getNodeData()->getIsArray() || !arrayIdentifier->getIsArray())
    {
        EmitDiagnostics::Error::emitGenericError(binary->getTokenLineNumber(), "Cannot index nonarray '" + arrayIdentifier->getIdentifierName() + "'.");
    }

    NodeData* indexData = setAndGetExpData(indexExpression);
    if (indexData->getType() != NodeData::Type::INT)
    {
        EmitDiagnostics::Error::emitGenericError(binary->getTokenLineNumber(), "Array '" + arrayIdentifier->getIdentifierName() + "' should be indexed by type int but got type " + indexData->printTokenString() + ".");
    }

    if (prevArrayDeclaration != nullptr && prevArrayDeclaration->getNodeData()->getIsArray() && isIdentifierNode(indexExpression))
    {
        Id* indexIdentifier = (Id* )indexExpression;
        if (indexIdentifier->getIdentifierName() == indexIdentifier->getIdentifierName())
        {
            EmitDiagnostics::Error::emitGenericError(binary->getTokenLineNumber(), "Array index is the unindexed array '" + arrayIdentifier->getIdentifierName() + "'.");
        }
    }
    else if (prevArrayDeclaration != nullptr && isIdentifierNode(indexExpression))
    {
        Var* prevArrayVar = (Var* )prevArrayDeclaration;
        Id *indexId = (Id *)indexExpression;
        if (indexId->getIdentifierName() == prevArrayVar->getNodeData()->getCopyString())
        {
            EmitDiagnostics::Error::emitGenericError(binary->getTokenLineNumber(), "Array index is the unindexed array '" + indexId->getIdentifierName() + "'.");
        }
    }
}


void Semantics::checkOperandsOfSameType(ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::checkOperandsOfSameType() - Invalid Exp");
    }
    if (!expOperandsExist(expression))
    {
        throw std::runtime_error("Semantics::checkOperandsOfSameType() - LHS and RHS Exp operands must exist");
    }

    std::string sym = getExpSym(expression);

    std::vector<Node* > children = expression->getChildernNodes();
    ExpressionNode* lhsExp = (ExpressionNode* )(children[0]);
    ExpressionNode* rhsExp = (ExpressionNode* )(children[1]);
    NodeData *lhsData = setAndGetExpData(lhsExp);
    NodeData *rhsData = setAndGetExpData(rhsExp);

    // Ignore cases where the LHS has no type
    if (lhsData->getType() == NodeData::Type::UNDEFINED)
    {
        expression->getNodeData()->setType(NodeData::Type::UNDEFINED);
        return;
    }

    // Both sides must be the same type
    if (lhsData->getType() != rhsData->getType())
    {
        EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires operands of the same type but lhs is type " + lhsData->printTokenString() + " and rhs is type " + rhsData->printTokenString() + ".");
    }

    // Both sides must be arrays or both must not be arrays
    if (lhsData->getIsArray() && !rhsData->getIsArray())
    {
        EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires both operands be arrays or not but lhs is an array and rhs is not an array.");
    }
    else if (!lhsData->getIsArray() && rhsData->getIsArray())
    {
        EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires both operands be arrays or not but lhs is not an array and rhs is an array.");
    }

    if (isIdentifierNode(lhsExp) && isIdentifierNode(rhsExp))
    {
        Id *lhsId = (Id *)lhsExp;
        Id *rhsId = (Id *)rhsExp;
        if (lhsId->getIdentifierName() != rhsId->getIdentifierName())
        {
            DeclarationNode* prevLhsDeclaration = (DeclarationNode* )(getFromSymTable(lhsId->getIdentifierName()));
            DeclarationNode *prevRhsDeclaration = (DeclarationNode* )(getFromSymTable(rhsId->getIdentifierName()));
            if ((prevLhsDeclaration != nullptr && isVariableNode(prevLhsDeclaration)) && (prevRhsDeclaration != nullptr && isVariableNode(prevRhsDeclaration)))
            {
                if (rhsData->getCopyString() != lhsId->getIdentifierName())
                {
                    lhsData->setCopyString(rhsId->getIdentifierName());
                }
            }
        }
    }
}


void Semantics::checkOperandsOfType(ExpressionNode* expression, const NodeData::Type type) const
{
     if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::checkOperandsOfSameType() - Invalid Exp");
    }
    if (!expOperandsExist(expression))
    {
        throw std::runtime_error("Semantics::checkOperandsOfSameType() - LHS and RHS Exp operands must exist");
    }

    std::string sym = getExpSym(expression);

    std::vector<Node* > children = expression->getChildernNodes();
    ExpressionNode* lhsExp = (ExpressionNode* )(children[0]);
    ExpressionNode* rhsExp = (ExpressionNode* )(children[1]);
    NodeData* lhsData = setAndGetExpData(lhsExp);
    NodeData* rhsData = setAndGetExpData(rhsExp);

    // Ignore cases where the LHS has no type
    if (lhsData->getType() == NodeData::Type::UNDEFINED)
    {
        expression->getNodeData()->setType(NodeData::Type::UNDEFINED);
        return;
    }

    // Both sides must be the same type
    if (lhsData->getType() != rhsData->getType())
    {
        EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires operands of the same type but lhs is type " + lhsData->printTokenString() + " and rhs is type " + rhsData->printTokenString() + ".");
    }

    // Both sides must be arrays or both must not be arrays
    if (lhsData->getIsArray() && !rhsData->getIsArray())
    {
        EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires both operands be arrays or not but lhs is an array and rhs is not an array.");
    }
    else if (!lhsData->getIsArray() && rhsData->getIsArray())
    {
        EmitDiagnostics::Error::emitGenericError(expression->getTokenLineNumber(), "'" + sym + "' requires both operands be arrays or not but lhs is not an array and rhs is an array.");
    }

    if (isIdentifierNode(lhsExp) && isIdentifierNode(rhsExp))
    {
        Id* lhsId = (Id* )lhsExp;
        Id* rhsId = (Id* )rhsExp;
        if (lhsId->getIdentifierName() != rhsId->getIdentifierName())
        {
            DeclarationNode* prevLhsDecl = (DeclarationNode* )(getFromSymTable(lhsId->getIdentifierName()));
            DeclarationNode* prevRhsDecl = (DeclarationNode* )(getFromSymTable(rhsId->getIdentifierName()));
            if ((prevLhsDecl != nullptr && isVariableNode(prevLhsDecl)) && (prevRhsDecl != nullptr && isVariableNode(prevRhsDecl)))
            {
                if (rhsData->getCopyString() != lhsId->getIdentifierName())
                {
                    lhsData->setCopyString(rhsId->getIdentifierName());
                }
            }
        }
    }
}


void Semantics::checkUnaryOperands(const Unary* unary) const
{
     if (!isUnaryNode(unary))
    {
        throw std::runtime_error("Semantics::checkUnaryOperands() - Invalid Unary");
    }
    if (!lhsExists((ExpressionNode* )unary))
    {
        throw std::runtime_error("Semantics::checkUnaryOperands() - LHS operand must exist");
    }

    std::vector<Node* > children = unary->getChildernNodes();
    
    ExpressionNode *lhsExp = (ExpressionNode* )(children[0]);
    
    NodeData *lhsData = setAndGetExpData(lhsExp);

    if (lhsData->getType() == NodeData::Type::UNDEFINED)
    {
        unary->getNodeData()->setType(NodeData::Type::UNDEFINED);
        return;
    }

    switch (unary->getUnaryType())
    {
        case Unary::Type::CHSIGN:
                            {
                                if (lhsData->getIsArray())
                                {
                                    EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "The operation '" + unary->printTokenString() + "' does not work with arrays.");
                                }
                                if (lhsData->getType() != NodeData::Type::INT)
                                {
                                    EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "Unary '" + unary->printTokenString() + "' requires an operand of type int but was given type " + lhsData->printTokenString() + ".");
                                }
                            }
                            break;
        
        case Unary::Type::QUESTION:
                                {
                                    if (lhsData->getIsArray())
                                    {
                                        EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "The operation '" + unary->printTokenString() + "' does not work with arrays.");
                                    }
                                    if (lhsData->getType() != NodeData::Type::INT)
                                    {
                                        EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "Unary '" + unary->printTokenString() + "' requires an operand of type int but was given type " + lhsData->printTokenString() + ".");
                                    }
                                }
                                break;
        
        case Unary::Type::SIZEOF:
                            {
                                if (!lhsData->getIsArray())
                                {
                                    EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "The operation 'sizeof' only works with arrays.");
                                }
                            }
                            break;

        case Unary::Type::NOT:
                        {
                            if (lhsData->getType() != NodeData::Type::BOOL)
                            {
                                EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "Unary '" + unary->printTokenString() + "' requires an operand of type bool but was given type " + lhsData->printTokenString() + ".");
                            }
                            if (lhsData->getIsArray())
                            {
                                EmitDiagnostics::Error::emitGenericError(unary->getTokenLineNumber(), "The operation 'not' does not work with arrays.");
                            }
                        }
                        break;
        
        
        default:
        {
            throw std::runtime_error("Semantics::checkUnaryOperands() - Unknown type");
        }
        break;
    }
}


void Semantics::checkUnaryAsgnOperands(const UnaryAsgn* unaryAsgn) const
{
    if (!isUnaryAssignmentNode(unaryAsgn))
    {
        throw std::runtime_error("Semantics::checkUnaryAsgnOperands() - Invalid UnaryAsgn");
    }
    if (!lhsExists((ExpressionNode* )unaryAsgn))
    {
        throw std::runtime_error("Semantics::checkUnaryAsgnOperands() - LHS operand must exist");
    }

    std::vector<Node *> children = unaryAsgn->getChildernNodes();
    ExpressionNode* lhsExp = (ExpressionNode* )(children[0]);
    NodeData* lhsData = setAndGetExpData(lhsExp);
    
    
    if (lhsData->getType() == NodeData::Type::UNDEFINED)
    {
        unaryAsgn->getNodeData()->setType(NodeData::Type::UNDEFINED);
        return;
    }

    switch (unaryAsgn->getUnaryAssignmentType())
    {
        
        case UnaryAsgn::Type::INC:
                                {
                                    if (lhsData->getIsArray())
                                    {
                                        EmitDiagnostics::Error::emitGenericError(unaryAsgn->getTokenLineNumber(), "The operation '" + unaryAsgn->printTokenString() + "' does not work with arrays.");
                                    }
                                    if (lhsData->getType() != NodeData::Type::INT)
                                    {
                                        EmitDiagnostics::Error::emitGenericError(unaryAsgn->getTokenLineNumber(), "Unary '" + unaryAsgn->printTokenString() + "' requires an operand of type int but was given type " + lhsData->printTokenString() + ".");
                                    }
                                }
                                break;
        
        case UnaryAsgn::Type::DEC:
                                {
                                    if (lhsData->getIsArray())
                                    {
                                        EmitDiagnostics::Error::emitGenericError(unaryAsgn->getTokenLineNumber(), "The operation '" + unaryAsgn->printTokenString() + "' does not work with arrays.");
                                    }
                                    if (lhsData->getType() != NodeData::Type::INT)
                                    {
                                        EmitDiagnostics::Error::emitGenericError(unaryAsgn->getTokenLineNumber(), "Unary '" + unaryAsgn->printTokenString() + "' requires an operand of type int but was given type " + lhsData->printTokenString() + ".");
                                    }
                                }
                                break;
        
        default:
        {
            throw std::runtime_error("Semantics::checkUnaryAsgnOperands() - Unknown type");
        }
        break;
    }
}


//**********************************************************
//********************Helper Functions**********************
//**********************************************************



bool Semantics::isMainFunc(const Func* func) const
{
    if (!isFunctionNode(func))
    {
        throw std::runtime_error("Semantics::isMainFunc() - Invalid Func");
    }

    // Function name must be main and in global scope
    if (func->getName() != "main" || m_symbolTable->depth() != 1)
    {
        return false;
    }

    // Get the function children
    std::vector<Node* > funcChildren = func->getChildernNodes();

    // There can't be any parms (children)
    if (funcChildren[0] != nullptr)
    {
        return false;
    }

    // If main is previously defined as a variable
    DeclarationNode* prevDeclaration = getFromSymTable(func->getName());
    if (isVariableNode(prevDeclaration))
    {
        return false;
    }

    return true;
}


bool Semantics::isDeclared(const Id* id) const
{
    if (!isIdentifierNode(id))
    {
        throw std::runtime_error("Semantics::isDeclared() - Invalid Id");
    }

    // If the id name is not in the symbol table, it is not declared
    if (getFromSymTable(id->getIdentifierName()) == nullptr)
    {
        return false;
    }
    return true;
}


bool Semantics::hasIndexAncestor(const ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::hasIndexAncestor() - Invalid Exp");
    }

    Node* lastParent = (Node* )expression;
    Node* parent = expression->getParentNode();
    
    // If the parent is an index node, then the expression is an index
    while (parent != nullptr)
    {
        if (isBinaryNode(parent))
        {
            Binary *binary = (Binary *)parent;
            if (binary->getBinaryType() == Binary::Type::INDEX)
            {
                // On the right side
                if (binary->getChildernNodes()[1] == lastParent)
                {
                    return true;
                }
            }
        }
        
        lastParent = parent;
        
        parent = parent->getParentNode();
    }
    return false;
}


bool Semantics::hasAsgnAncestor(const ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::hasAsgnAncestor() - Invalid Exp");
    }

    Node* lastParent = (Node* )expression;
    Node* parent = expression->getParentNode();
    while (parent != nullptr)
    {
        if (isAssignmentNode(parent))
        {
            Asgn *asgn = (Asgn *)parent;
            if (asgn->getAssignmentType() == Asgn::Type::ASGN)
            {
                // On the left side
                if (asgn->getChildernNodes()[0] == lastParent)
                {
                    return true;
                }
            }
        }
        
        
        lastParent = parent;
        
        
        parent = parent->getParentNode();
    }
    
    
    return false;
}


bool Semantics::expOperandsExist(const ExpressionNode* expression) const
{
    // If the expression has no children, it is not valid
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::expOperandsExist() - Invalid Exp");
    }

    std::vector<Node* > children = expression->getChildernNodes();
    
    // If the expression has no children, it is not valid
    if (children.size() < 2 || children[0] == nullptr || children[1] == nullptr)
    {
        return false;
    }
    
    // If the expression has no children, it is not valid
    if (!isExpressionNode(children[0]) || !isExpressionNode(children[1]))
    {
        return false;
    }
    
    
    return true;
}


bool Semantics::lhsExists(const ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::lhsExists() - Invalid Exp");
    }

    std::vector<Node *> children = expression->getChildernNodes();
    
    
    ExpressionNode* lhsExp = (ExpressionNode* )(children[0]);
    
    
    if (children.size() == 0 || lhsExp == nullptr)
    {
        return false;
    }
    
    
    return true;
}


std::string Semantics::getExpSym(const ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::getExpSym() - Invalid Exp");
    }

    if (isAssignmentNode(expression))
    {
        Asgn *asgn = (Asgn *)expression;
        return asgn->printTokenString();
    }
    else if (isBinaryNode(expression))
    {
        Binary *binary = (Binary *)expression;
        return  binary->printTokenString();
    }
    else
    {
        throw std::runtime_error("Semantics::getExpSym() - Exp is not an operation");
    }
}


NodeData* Semantics::setAndGetExpData(const ExpressionNode* expression) const
{
    if (!isExpressionNode(expression))
    {
        throw std::runtime_error("Semantics::setAndGetExpData() - Invalid Exp");
    }

    std::string name;

    switch (expression->getExpressionNodeType())
    {
        case ExpressionNode::Type::ASSIGN:
                                        {
                                            Asgn* asgn = (Asgn* )expression;
                                            ExpressionNode* lhsExp = (ExpressionNode* )(expression->getChildernNodes()[0]);
                                            asgn->setNodeData(setAndGetExpData(lhsExp));
                                        }
                                        break;
        
        case ExpressionNode::Type::BINARY:
                                        {
                                            Binary* binary = (Binary* )expression;
                                            
                                            if (binary->getBinaryType() == Binary::Type::INDEX)
                                            {
                                                Id *arrayId = (Id *)(binary->getChildernNodes()[0]);
                                                binary->setNodeData(new NodeData(setAndGetExpData(arrayId)->getType(), false, false));
                                            }
                                        }
                                        break;
        
        case ExpressionNode::Type::CALL:
                                    {
                                        Call* call = (Call* )expression;
                                        
                                        DeclarationNode* prevDecl = getFromSymTable(call->getFunctionCallName());
                                        
                                        if (prevDecl != nullptr && prevDecl->getDeclarationNodeType() != DeclarationNode::Type::VARIABLE)
                                        {
                                            call->setNodeData(prevDecl->getNodeData());
                                        }
                                    }
                                    break;
        
        case ExpressionNode::Type::IDENTIFIER:
                                {
                                    Id* id = (Id* )expression;
                                    
                                    DeclarationNode* prevDecl = getFromSymTable(id->getIdentifierName());
                                    
                                    if (prevDecl != nullptr && prevDecl->getDeclarationNodeType() != DeclarationNode::Type::FUNCTION)
                                    {
                                        id->setNodeData(prevDecl->getNodeData());
                                    }
                                }
                                break;
    }
    
    
    return expression->getNodeData();
}


//**************************************************
//********************Symbol Table Functions**********************
//**************************************************


void Semantics::leaveScope()
{
    std::map<std::string, void *> syms = m_symbolTable->getSymbols();
    for (auto const& [name, voisIdode] : syms)
    {
        Node *node = (Node *)voisIdode;
        if (!isDeclarationNode(node))
        {
            throw std::runtime_error("Semantics::leaveScope() - Illegal node found in symbol table");
        }

        DeclarationNode* declaration = (DeclarationNode* )node;
        if (isVariableNode(declaration))
        {
            Var* var = (Var* )declaration;
            if (var->getIsUsed() == false)
            {
                EmitDiagnostics::Warning::emitGenericWarnings(var->getTokenLineNumber(), "The variable '" + var->getName() + "' seems not to be used.");
            }
        }
        else if (isParameterNode(declaration))
        {
            Parm *parm = (Parm *)declaration;
            if (parm->getIsUsed() == false)
            {
                EmitDiagnostics::Warning::emitGenericWarnings(parm->getTokenLineNumber(), "The variable '" + parm->getName() + "' seems not to be used.");
            }
        }
    }

    m_symbolTable->leave();
}


bool Semantics::addToSymTable(const DeclarationNode* declaration, const bool global)
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
        DeclarationNode* prevDeclaration = (DeclarationNode* )(getFromSymTable(declaration->getName()));
        if (prevDeclaration == nullptr)
        {
            throw std::runtime_error("Semantics::addToSymTable() - Failed to insert Decl");
        }
        std::stringstream msg;
        msg << "Symbol '" << declaration->getName() << "' is already declared at line " << prevDeclaration->getTokenLineNumber() << ".";
        EmitDiagnostics::Error::emitGenericError(declaration->getTokenLineNumber(), msg.str());
    }

    return inserted;
}


DeclarationNode* Semantics::getFromSymTable(const std::string name) const
{
    if (name.length() == 0)
    {
        throw std::runtime_error("Semantics::getFromSymTable() - Invalid name");
    }

    DeclarationNode* prevDeclaration = (DeclarationNode* )(m_symbolTable->lookup(name));
    return prevDeclaration;
}