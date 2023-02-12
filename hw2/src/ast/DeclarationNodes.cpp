/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: DeclarationNodes.cpp
DESC: DeclarationNodes Subclass Member Definitions. 
*/

#include "DeclarationNodes.hpp"

//******************************************************
// ************ PrimitiveType Class *******************
//******************************************************
PrimitiveType::PrimitiveType(const PrimitiveType::Type type, const bool isArray) : m_type(type), m_isArray(isArray)
{
    //set next to null
    m_next = nullptr;
    
    //check if array
    if (isArray)
    {
        //create new PrimitiveType
        m_next = new PrimitiveType(type);
        //set type to void
        m_type = Type::VOID;
    }
    //not array
    else
    {
        //set type
        m_type = type;
    }
}

std::string PrimitiveType::printTokenString() const
{
    std::string tokenOutputString;
    switch(m_type)
    {
        case Type::INT:
                    {
                        tokenOutputString = "int";
                    }
                    break;

        case Type::CHAR:
                    {
                        tokenOutputString = "char";
                    }
                    break;
        
        case Type::BOOL:
                    {
                        tokenOutputString = "bool";
                    }
                    break;


        case Type::VOID:
                    {
                        tokenOutputString = "void";
                    }
                    break;
        default:
            {
                tokenOutputString += "ERROR. Could not determine PrimitiveType::Type.";
            }
            break;
    }
    return tokenOutputString;
}

//setPrimitiveType
void PrimitiveType::setPrimitiveType(const PrimitiveType::Type type)
{
    //set type
    m_type = type;

    //check if next is not null
    if (m_next != nullptr)
    {
        //set next type
        m_next->setPrimitiveType(type);
    }
}

//getters

//getPrimitiveType
PrimitiveType::Type PrimitiveType::getPrimitiveType() const
{
    return m_type;
}

//getIsArray
bool PrimitiveType::getIsArray() const
{
    return m_isArray;
}

//******************************************************
// ************ FunctionNode Class *********************
//******************************************************

//Constructor
FunctionNode::FunctionNode(int tokenLineNumber, const std::string functionName, PrimitiveType *returnType) : Node::Node(tokenLineNumber,functionName), m_returnType(returnType)
{

}

//printTokenString
std::string FunctionNode::printTokenString() const
{
    return "Func: " + m_stringValue + " returns type " + m_returnType->printTokenString();
}

//******************************************************
// ************ ParameterNode Class ********************
//******************************************************

//Constructor
ParameterNode::ParameterNode(int tokenLineNumber, const std::string parameterName, PrimitiveType *parameterType) : Node::Node(tokenLineNumber,parameterName), m_parameterType(parameterType)
{

}

//printTokenString
std::string ParameterNode::printTokenString() const
{
    if (m_parameterType->getIsArray())
    {
        return "Param: " + m_stringValue + " of array of type " + m_parameterType->printTokenString();
    }
    else
    {
        return "Param: " + m_stringValue + " of type " + m_parameterType->printTokenString();
    }
}

//setParameterType
void ParameterNode::setParameterType(PrimitiveType::Type parameterType)
{
    //set parameter type
    m_parameterType->setPrimitiveType(parameterType);

    //check if siblingNode is not null
    if (m_siblingNode != nullptr)
    {
        //set temp node to siblingNode
        ParameterNode *node = dynamic_cast<ParameterNode*>(m_siblingNode);
        
        //set node type
        node->setParameterType(parameterType);
    }
}

//******************************************************
// ************ VariableNode Class *********************
//******************************************************

//Constructor
VariableNode::VariableNode(int tokenLineNumber, const std::string variableName, PrimitiveType *variableType, const bool isStaticVariable) : Node::Node(tokenLineNumber,variableName), m_variableType(variableType), m_isStaticVariable(isStaticVariable)
{

}

//printTokenString
std::string VariableNode::printTokenString() const
{
    if (m_variableType->getIsArray() && m_isStaticVariable)
    {
        return "Var: " + m_stringValue + " of static array of type " + m_variableType->printTokenString();
    }
    else if (m_variableType->getIsArray())
    {
        return "Var: " + m_stringValue + " of array of type " + m_variableType->printTokenString();
    }
    else if(m_isStaticVariable)
    {
        return "Var: " + m_stringValue + " of static type " + m_variableType->printTokenString();
    }
    else
    {
        return "Var: " + m_stringValue + " of type " + m_variableType->printTokenString();
    }
}
