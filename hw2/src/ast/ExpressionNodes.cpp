/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: ExprssionNodes.cpp
DESC: ExpressionNodes Subclass Member Definitions. 

*/
#include "ExpressionNodes.hpp"

//********************************************************************************
// ************ ExpressionNode Class Member Functions *********************************
//********************************************************************************

//ExpressionNode Constructor
ExpressionNode :: ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType) : Node::Node(tokenLineNumber), m_expressionType(expressionType)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize sibling node to nullptr
    m_siblingNode = nullptr; 

}

std::string ExpressionNode :: printTokenString() const
{
    //return token string
    return "ExpressionNode";
}

//********************************************************************************
// ************ AssignmentNode Class Member Functions *********************************
//********************************************************************************

//AssignmentNode Constructor
AssignmentNode :: AssignmentNode(int tokenLineNumber, const AssignmentNode::Type assignmentType) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::ASSIGN), m_assignmentType(assignmentType)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize m_assignmentType
    m_assignmentType = assignmentType;
}

std::string AssignmentNode :: printTokenString() const
{
    
    std::string tokenOutputString = "Assign: ";

    //switch statement to determine tokenOutputString
    switch (m_assignmentType)
    {
        case::AssignmentNode::Type::ASGN:
                                    {
                                        tokenOutputString += "ASGN";
                                    }
                                    break;
        
        case::AssignmentNode::Type::ADDASS:
                                    {
                                        tokenOutputString += "+=";
                                    }
                                    break;
        
        case::AssignmentNode::Type::SUBASS:
                                    {
                                        tokenOutputString += "-=";
                                    }
                                    break;
        
        case::AssignmentNode::Type::MULASS:
                                    {
                                        tokenOutputString += "*=";
                                    }
                                    break;
        
        case::AssignmentNode::Type::DIVASS:
                                    {
                                        tokenOutputString += "/=";
                                    }
                                    break;
        default:
            {
                tokenOutputString += "ERROR. Could not determine AssignmentNode::Type.";
            }
            break;
        }

    return tokenOutputString;
}


//********************************************************************************
// ************ BinaryNode Class Member Functions *********************************
//********************************************************************************

//BinaryNode Constructor
BinaryNode :: BinaryNode(int tokenLineNumber, const BinaryNode::Type binaryType) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::BINARY), m_binaryType(binaryType)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize m_binaryType
    m_binaryType = binaryType;
}

//BinaryNode printTokenString
std::string BinaryNode::printTokenString() const
{
    std::string tokenOutputString = "Op: ";

    //switch statement to determine tokenOutputString
    switch (m_binaryType)
    {
        case::BinaryNode::Type::ADD:
                                    {
                                        tokenOutputString += "+";
                                    }
                                    break;
        
        case::BinaryNode::Type::SUB:
                                    {
                                        tokenOutputString += "-";
                                    }
                                    break;
        
        case::BinaryNode::Type::MUL:
                                    {
                                        tokenOutputString += "*";
                                    }
                                    break;
        
        case::BinaryNode::Type::DIV:
                                    {
                                        tokenOutputString += "/";
                                    }
                                    break;
        
        case::BinaryNode::Type::MOD:
                                    {
                                        tokenOutputString += "%";
                                    }
                                    break;

        case::BinaryNode::Type::EQ:
                                    {
                                        tokenOutputString += "==";
                                    }
                                    break;
        
        case::BinaryNode::Type::NEQ:
                                    {
                                        tokenOutputString += "!=";
                                    }

        case::BinaryNode::Type::LT:
                                    {
                                        tokenOutputString += "<";
                                    }
                                    break;
        case::BinaryNode::Type::GT:
                                    {
                                        tokenOutputString += ">";
                                    }
                                    break;
        case::BinaryNode::Type::LEQ:
                                    {
                                        tokenOutputString += "<=";
                                    }

        case::BinaryNode::Type::GEQ:
                                    {
                                        tokenOutputString += ">=";
                                    }
                                    break;

        case::BinaryNode::Type::AND:
                                    {
                                        tokenOutputString += "and";
                                    }
                                    break;

        case::BinaryNode::Type::OR:
                                    {
                                        tokenOutputString += "or";
                                    }

        case::BinaryNode::Type::INDEX:
                                    {
                                        tokenOutputString += "[";
                                    }
                                    break;
        
        default:
            {
                tokenOutputString += "ERROR. Could not determine BinaryNode::Type.";
            }
            break;
        }

    return tokenOutputString;
}

//********************************************************************************
// ************ CallNode Class Member Functions *********************************
//********************************************************************************

//CallNode Constructor
CallNode :: CallNode(int tokenLineNumber, std::string functionName) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::CALL)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize string value
    m_tokenData.stringValue  = functionName;
}

//CallNode printTokenString
std::string CallNode::printTokenString() const
{
    return "Call: " + m_tokenData.stringValue;
}

//********************************************************************************
// ************ ConstantNode Class Member Functions *********************************
//********************************************************************************


//ConstantNode Constructor
ConstantNode :: ConstantNode(int tokenLineNumber, const std::string constantValue, Type constantType) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::CONSTANT), m_constantType(constantType)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize m_constantType
    m_constantType = constantType;

    switch (m_constantType)
    {
        case ConstantNode::Type::INT:
                                {
                                    m_tokenData.numValue = std::stoi(constantValue);
                                }
                                break;
        
        case ConstantNode::Type::BOOL:
                                {
                                    m_tokenData.boolValue = (constantValue == "true" ? true : false); 
                                }
                                break;
        
        case ConstantNode::Type::STRING:
                                    {
                                        m_tokenData.stringValue = m_tokenFormatter.parseCharacters(constantValue);
                                    }
                                    break;
        
        case ConstantNode::Type::CHAR:
                                {
                                    //create new temp string and concatenate the first and last character of the constantValue string
                                    std::string tempString = m_tokenFormatter.deleteLeftmostAndRightmostCharacters(constantValue);
                                    
                                    //parse the tempString and assign the char value to m_tokenData.charValue
                                    m_tokenData.charValue = m_tokenFormatter.parseLeftmostCharacter(tempString);

                                    if(tempString.length() > 1 && tempString[0] != '\\')
                                    {
                                        //throw error flag
                                        m_tokenData.isCharLengthGreaterThan1 = true;
                                    }
                                }
                                break; 
    }
}

//ConstantNode printTokenString
std::string ConstantNode::printTokenString() const
{
    //create tokenOutputString
    std::string tokenOutputString = "Const: ";
    
    switch (m_constantType)
    {
        case ConstantNode::Type::INT:
                                {
                                    tokenOutputString += std::to_string(m_tokenData.numValue);
                                }
                                break;
        
        
        case ConstantNode::Type::BOOL:
                                {

                                    if(m_tokenData.boolValue == true)
                                    {
                                        tokenOutputString += "true";
                                    }
                                    else
                                    {
                                        tokenOutputString += "false";
                                    }
                                }
                                break;
        
        
        case ConstantNode::Type::CHAR:
                                {
                                    tokenOutputString += "'" + std::string(1, m_tokenData.charValue) + "'";
                                }
                                break;
        
        
        case ConstantNode::Type::STRING:
                                {
                                    tokenOutputString += "\"" + m_tokenData.stringValue + "\"";
                                }
                                break;
    }


    return tokenOutputString;
}

//********************************************************************************
// ************ IdentifierNode Class Member Functions ****************************
//********************************************************************************

//IdentifierNode Constructor
IdentifierNode :: IdentifierNode(int tokenLineNumber, bool isArray, std:: string identifierName) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::IDENTIFIER)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize string value
    m_tokenData.stringValue  = identifierName;

    //initialize m_isArray
    m_isArray = isArray;
}

//IdentifierNode printTokenString
std::string IdentifierNode::printTokenString() const
{
    return "Id: " + m_tokenData.stringValue;
}

//********************************************************************************
// ************ UnaryNode Class Member Functions *********************************
//********************************************************************************

//UnaryNode Constructor
UnaryNode :: UnaryNode(int tokenLineNumber, Type unaryType) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::UNARY), m_unaryType(unaryType)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize m_unaryType
    m_unaryType = unaryType;
}

//UnaryNode printTokenString
std::string UnaryNode::printTokenString() const
{
    //create tokenOutputString
    std::string tokenOutputString = "Op: ";

    //switch statement to determine tokenOutputString
    switch (m_unaryType)
    {
        case::UnaryNode::Type::CHSIGN:
                                {
                                    tokenOutputString += "chsign";
                                }
                                break;
        
        case::UnaryNode::Type::NOT:
                                {
                                    tokenOutputString += "not";
                                }
                                break;

        case::UnaryNode::Type::QUESTION:
                                    {
                                        tokenOutputString += "?";
                                    }
                                    break;

        case::UnaryNode::Type::SIZEOF:
                                {
                                    tokenOutputString += "sizeof";
                                }
                                break;
        default:
            {
                tokenOutputString += "ERROR. Could not determine UnaryNode::Type.";
            }
            break;
        }

    return tokenOutputString;
}

//********************************************************************************
// ************ UnaryAssignmentNode Class Member Functions ***********************
//********************************************************************************

//UnaryAssignmentNode Constructor
UnaryAssignmentNode :: UnaryAssignmentNode(int tokenLineNumber, Type unaryAssignmentType) : ExpressionNode::ExpressionNode(tokenLineNumber, ExpressionNode::Type::UNARYASSIGN), m_unaryAssignmentType(unaryAssignmentType)
{
    //initialize tokenLineNumber
    m_tokenData.tokenLineNumber = tokenLineNumber;

    //initialize m_unaryAssignmentType
    m_unaryAssignmentType = unaryAssignmentType;
}

//UnaryAssignmentNode printTokenString
std::string UnaryAssignmentNode::printTokenString() const
{
    //create tokenOutputString
    std::string tokenOutputString = "Asign: ";

    //switch statement to determine tokenOutputString
    switch (m_unaryAssignmentType)
    {
        case::UnaryAssignmentNode::Type::INC:
                                        {
                                            tokenOutputString += "++";
                                        }
                                        break;
        
        case::UnaryAssignmentNode::Type::DEC:
                                        {
                                            tokenOutputString += "--";
                                        }
                                        break;
        
        default:
            {
                tokenOutputString += "ERROR. Could not determine UnaryAssignmentNode::Type.";
            }
            break;
        }

    return tokenOutputString;
}