/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: ExprssionNodes.cpp
DESC: ExpressionNodes Subclass Member Definitions. 

*/
#include "ExpressionNodes.hpp"

//********************************************************************************
// ************ ExpressionNode Class Member Functions *********************************
//********************************************************************************

//Constructor
ExpressionNode::ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType, NodeData* nodeData) : Node::Node{tokenLineNumber, Node::Type::EXPRESSION}, m_nodeData{nodeData}, m_declarationType{expressionType}
{

}


// ****************** Printing ******************************
std::string ExpressionNode::printTokenStringWithType() const
{
    std::string expressionTypeString = m_nodeData->printTokenStringWithType();

    if (expressionTypeString != "undefined")
    {
        return printTokenString() + " of type " + expressionTypeString;
    }
    else
    {
        return printTokenString() + " of undefined type";
    }
    
}


// ****************** Setters ******************************
void ExpressionNode::setNodeData(NodeData* nodeData)
{
    m_nodeData = nodeData;
}

// ****************** Getters ******************************
NodeData* ExpressionNode::getNodeData() const
{
    return m_nodeData;
}

ExpressionNode::Type ExpressionNode::getExpressionNodeType() const
{
    return m_declarationType;
}




//********************************************************************************
// ************ AssignmentNode Class Member Functions *********************************
//********************************************************************************

//AssignmentNode Constructor
Asgn :: Asgn(const int tokenLineNumber, const Type assignmentType) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::ASSIGN, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_assignmentType{assignmentType}
{

}

std::string Asgn :: printTokenString() const
{
    
    std::string tokenOutputString = "Assign: ";

    //switch statement to determine tokenOutputString
    switch (m_assignmentType)
    {
        case::Asgn::Type::ASGN:
                                    {
                                        tokenOutputString += "<=";
                                    }
                                    break;
        
        case::Asgn::Type::ADDASS:
                                    {
                                        tokenOutputString += "+=";
                                    }
                                    break;
        
        case::Asgn::Type::SUBASS:
                                    {
                                        tokenOutputString += "-=";
                                    }
                                    break;
        
        case::Asgn::Type::MULASS:
                                    {
                                        tokenOutputString += "*=";
                                    }
                                    break;
        
        case::Asgn::Type::DIVASS:
                                    {
                                        tokenOutputString += "/=";
                                    }
                                    break;
        default:
            {
                throw std::runtime_error("ERROR. Could not determine Asgn::Type");
            }
            break;
        }

    return tokenOutputString;
}


//********************************************************************************
// ************ BinaryNode Class Member Functions *********************************
//********************************************************************************

//BinaryNode Constructor
Binary :: Binary(const int tokenLineNumber, const Type binaryType) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::BINARY, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_binaryType{binaryType}
{
    switch (m_binaryType)
    {
        case Binary::Type::ADD:
                            {
                                m_nodeData->setType(NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::SUB:
                            {
                                m_nodeData->setType(NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::MUL:
                            {
                                m_nodeData->setType(NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::DIV:
                            {
                                m_nodeData->setType(NodeData::Type::INT);
                            }
                            break;
        
        case Binary::Type::MOD:
                        {
                            m_nodeData->setType(NodeData::Type::INT);
                        }
                        break;
        
        case Binary::Type::EQ:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                            }
                            break;
        
        case Binary::Type::NEQ:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                            }
                            break;
        
        case Binary::Type::LT:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                            }
                            break;
        
        case Binary::Type::LEQ:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                            }
                            break;
        
        case Binary::Type::GT:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                            }
                            break;
        
        case Binary::Type::GEQ:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                            }
                            break;
        
        default:
            {
                throw std::runtime_error("ERROR. Could not determine Binary::Type");
            }
            break;
    }
}

//BinaryNode printTokenString
std::string Binary::printTokenString() const
{
    std::string tokenOutputString = "Op: ";

    //switch statement to determine tokenOutputString
    switch (m_binaryType)
    {
        case::Binary::Type::ADD:
                                    {
                                        tokenOutputString += "+";
                                    }
                                    break;
        
        case::Binary::Type::SUB:
                                    {
                                        tokenOutputString += "-";
                                    }
                                    break;
        
        case::Binary::Type::MUL:
                                    {
                                        tokenOutputString += "*";
                                    }
                                    break;
        
        case::Binary::Type::DIV:
                                    {
                                        tokenOutputString += "/";
                                    }
                                    break;
        
        case::Binary::Type::MOD:
                                    {
                                        tokenOutputString += "%";
                                    }
                                    break;

        case::Binary::Type::EQ:
                                    {
                                        tokenOutputString += "=";
                                    }
                                    break;
        
        case::Binary::Type::NEQ:
                                    {
                                        tokenOutputString += "!=";
                                    }
                                    break;

        case::Binary::Type::LT:
                                    {
                                        tokenOutputString += "<";
                                    }
                                    break;
        case::Binary::Type::GT:
                                    {
                                        tokenOutputString += ">";
                                    }
                                    break;
        case::Binary::Type::LEQ:
                                    {
                                        tokenOutputString += "!>";
                                    }
                                    break; 

        case::Binary::Type::GEQ:
                                    {
                                        tokenOutputString += "!<";
                                    }
                                    break;

        case::Binary::Type::AND:
                                    {
                                        tokenOutputString += "and";
                                    }
                                    break;

        case::Binary::Type::OR:
                                    {
                                        tokenOutputString += "or";
                                    }
                                    break; 

        case::Binary::Type::INDEX:
                                    {
                                        tokenOutputString += "[";
                                    }
                                    break;
        
        default:
            {
                throw std::runtime_error("ERROR. Could not determine Binary::Type");
            }
            break;
        }

    return tokenOutputString;
}

//********************************************************************************
// ************ CallNode Class Member Functions *********************************
//********************************************************************************

//CallNode Constructor
Call :: Call(const int tokenLineNumber, std::string functionName) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::CALL, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_functionName{functionName}
{

}

//CallNode printTokenString
std::string Call::printTokenString() const
{
    return "Call: " + m_functionName;
}

//********************************************************************************
// ************ ConstantNode Class Member Functions *********************************
//********************************************************************************


//ConstantNode Constructor
Const :: Const(int tokenLineNumber, const Type constantType, const std::string constantValue) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::CONSTANT, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_constantType{constantType}
{
    switch (m_constantType)
    {
        case Const::Type::INT:
                            {
                                m_nodeData->setType(NodeData::Type::INT);
                                m_intValue = std::stoi(constantValue);
                            }
                            break;
        
        case Const::Type::BOOL:
                            {
                                m_nodeData->setType(NodeData::Type::BOOL);
                                m_boolValue = (constantValue == "true" ? true : false); 
                            }
                            break;
        
        case Const::Type::STRING:
                            {
                                m_nodeData->setType(NodeData::Type::CHAR);
                                m_stringValue = m_tokenFormatter.parseCharacters(m_tokenFormatter.deleteLeftmostAndRightmostCharacters(constantValue));
                                m_nodeData->setIsArray(true);

                            }
                            break;
        
        case Const::Type::CHAR:
                            {
                                m_nodeData->setType(NodeData::Type::CHAR);
                                
                                //create new temp string and concatenate the first and last character of the constantValue string
                                std::string tempString = m_tokenFormatter.deleteLeftmostAndRightmostCharacters(constantValue);
                                
                                //parse the tempString and assign the char value to m_tokenData.charValue
                                m_charValue = m_tokenFormatter.parseLeftmostCharacter(tempString);

                                if(tempString.length() > 1 && tempString[0] != '\\')
                                {
                                    //throw error flag
                                    m_isCharLengthGreaterThanOne = true;
                                }
                            }
                            break;
        
        default:
            {
                throw std::runtime_error("ERROR. Could not determine Const::Type");
            }
            break;
    }
}

//ConstantNode printTokenString
std::string Const::printTokenString() const
{
    //create tokenOutputString
    std::string tokenOutputString = "Const ";
    
    switch (m_constantType)
    {
        case Const::Type::INT:
                                {
                                    tokenOutputString += std::to_string(m_intValue);
                                }
                                break;
        
        
        case Const::Type::BOOL:
                                {

                                    if(m_boolValue == true)
                                    {
                                        tokenOutputString += "true";
                                    }
                                    else
                                    {
                                        tokenOutputString += "false";
                                    }
                                }
                                break;
        
        
        case Const::Type::CHAR:
                                {
                                    tokenOutputString += "'" + std::string(1, m_charValue) + "'";
                                }
                                break;
        
        
        case Const::Type::STRING:
                                {
                                    tokenOutputString += m_stringValue ;
                                }
                                break;
    }


    return tokenOutputString;
}

//********************************************************************************
// ************ IdentifierNode Class Member Functions ****************************
//********************************************************************************

//IdentifierNode Constructor
Id :: Id(const int tokenLineNumber,std:: string identifierName, bool isArray) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::IDENTIFIER, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_identifierName{identifierName}, m_isArray{isArray}
{

}

//IdentifierNode printTokenString
std::string Id::printTokenString() const
{
    return "Id: " + m_identifierName;
}

//********************************************************************************
// ************ UnaryNode Class Member Functions *********************************
//********************************************************************************

//UnaryNode Constructor
Unary :: Unary(int tokenLineNumber, const Type unaryType) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::UNARY, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_unaryType{unaryType}
{
    switch (m_unaryType)
    {
        case Unary::Type::CHSIGN:
                                {
                                    m_nodeData->setType(NodeData::Type::INT);
                                }
                                break;
        case Unary::Type::NOT:
                                {
                                    m_nodeData->setType(NodeData::Type::BOOL);
                                }
                                break;
        case Unary::Type::QUESTION:
                                {
                                    m_nodeData->setType(NodeData::Type::INT);
                                }
                                break;
        case Unary::Type::SIZEOF:
                                {
                                    m_nodeData->setType(NodeData::Type::INT);
                                }
                                break;
                                
        default:
            {
                throw std::runtime_error("ERROR. Could not determine Unary::Type");
            }
            break;
    }
}

//UnaryNode printTokenString
std::string Unary::printTokenString() const
{
    //create tokenOutputString
    std::string tokenOutputString = "Op: ";

    //switch statement to determine tokenOutputString
    switch (m_unaryType)
    {
        case::Unary::Type::CHSIGN:
                                {
                                    tokenOutputString += "chsign";
                                }
                                break;
        
        case::Unary::Type::NOT:
                                {
                                    tokenOutputString += "not";
                                }
                                break;

        case::Unary::Type::QUESTION:
                                    {
                                        tokenOutputString += "?";
                                    }
                                    break;

        case::Unary::Type::SIZEOF:
                                {
                                    tokenOutputString += "sizeof";
                                }
                                break;
        default:
            {
                throw std::runtime_error("ERROR. Could not determine Unary::Type");
            }
            break;
        }

    return tokenOutputString;
}

//********************************************************************************
// ************ UnaryAssignmentNode Class Member Functions ***********************
//********************************************************************************

//UnaryAssignmentNode Constructor
UnaryAsgn :: UnaryAsgn(const int tokenLineNumber, const Type unaryAssignmentType) : ExpressionNode::ExpressionNode{tokenLineNumber, ExpressionNode::Type::UNARYASSIGN, new NodeData(NodeData::Type::UNDEFINED, false, false)}, m_unaryAssignmentType{unaryAssignmentType}
{

}

//UnaryAssignmentNode printTokenString
std::string UnaryAsgn::printTokenString() const
{
    //create tokenOutputString
    std::string tokenOutputString = "Assign: ";

    //switch statement to determine tokenOutputString
    switch (m_unaryAssignmentType)
    {
        case::UnaryAsgn::Type::INC:
                                        {
                                            tokenOutputString += "++";
                                        }
                                        break;
        
        case::UnaryAsgn::Type::DEC:
                                        {
                                            tokenOutputString += "--";
                                        }
                                        break;
        
        default:
            {
                throw std::runtime_error("ERROR. Could not determine UnaryAsgn::Type");
            }
            break;
        }

    return tokenOutputString;
}