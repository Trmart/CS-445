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
// ExpressionNode :: ExpressionNode(int tokenLineNumber, const ExpressionNode::Type expressionType) : Node::Node(tokenLineNumber), m_expressionType(expressionType)
// {

// }

// std::string ExpressionNode :: printTokenString() const
// {
//     //return token string
//     return "ExpressionNode";
// }

//********************************************************************************
// ************ AssignmentNode Class Member Functions *********************************
//********************************************************************************

//AssignmentNode Constructor
Asgn :: Asgn(const int tokenLineNumber, const Type assignmentType) : Node::Node{tokenLineNumber}, m_assignmentType{assignmentType}
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
Binary :: Binary(const int tokenLineNumber, const Type binaryType) : Node::Node{tokenLineNumber}, m_binaryType{binaryType}
{

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
Call :: Call(const int tokenLineNumber, std::string functionName) : Node::Node{tokenLineNumber, functionName}
{

}

//CallNode printTokenString
std::string Call::printTokenString() const
{
    return "Call: " + m_stringValue;
}

//********************************************************************************
// ************ ConstantNode Class Member Functions *********************************
//********************************************************************************


//ConstantNode Constructor
Const :: Const(int tokenLineNumber, const Type constantType, const std::string constantValue) : Node::Node{tokenLineNumber}, m_constantType{constantType}
{
    //switch statement to determine tokenOutputString
    switch (m_constantType)
    {
        case Const::Type::INT:
                                {
                                    m_numValue = std::stoi(constantValue);
                                }
                                break;
        
        case Const::Type::BOOL:
                                {
                                    m_boolValue = (constantValue == "true" ? true : false); 
                                }
                                break;
        
        case Const::Type::STRING:
                                    {
                                        m_stringValue = m_tokenFormatter.parseCharacters(constantValue);
                                    }
                                    break;
        
        case Const::Type::CHAR:
                                {
                                    //create new temp string and concatenate the first and last character of the constantValue string
                                    std::string tempString = m_tokenFormatter.deleteLeftmostAndRightmostCharacters(constantValue);
                                    
                                    //parse the tempString and assign the char value to m_tokenData.charValue
                                    m_charValue = m_tokenFormatter.parseLeftmostCharacter(tempString);

                                    if(tempString.length() > 1 && tempString[0] != '\\')
                                    {
                                        //throw error flag
                                        m_isCharLengthGreaterThan1 = true;
                                    }
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
                                    tokenOutputString += std::to_string(m_numValue);
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
Id :: Id(const int tokenLineNumber,std:: string identifierName, bool isArray) : Node::Node{tokenLineNumber, identifierName}, m_isArray{isArray}
{

}

//IdentifierNode printTokenString
std::string Id::printTokenString() const
{
    return "Id: " + m_stringValue;
}

//********************************************************************************
// ************ UnaryNode Class Member Functions *********************************
//********************************************************************************

//UnaryNode Constructor
Unary :: Unary(int tokenLineNumber, const Type unaryType) : Node::Node{tokenLineNumber}, m_unaryType{unaryType}
{

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
UnaryAsgn :: UnaryAsgn(const int tokenLineNumber, const Type unaryAssignmentType) : Node::Node{tokenLineNumber}, m_unaryAssignmentType{unaryAssignmentType}
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