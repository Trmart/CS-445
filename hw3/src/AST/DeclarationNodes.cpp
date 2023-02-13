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
Primitive::Primitive(Type type, const bool isArray) : m_isArray(isArray)
{
    //set next to null
    m_next = nullptr;
    
    //check if array
    if (isArray)
    {
        //create new PrimitiveType
        m_next = new Primitive(type);
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

std::string Primitive::printTokenString() const
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
                throw std::runtime_error("ERROR. Could not determine Primitive::Type");
            }
            break;
    }
    return tokenOutputString;
}

//setPrimitiveType
void Primitive::setType(Type type)
{
    //set type
    m_type = type;

    //check if next is not null
    if (m_next != nullptr)
    {
        //set next type
        m_next->setType(type);
    }
}


//getIsArray
bool Primitive::getIsArray() const
{
    return m_isArray;
}

//******************************************************
// ************ FunctionNode Class *********************
//******************************************************

//Constructor
Func::Func(const int tokenLineNumber,  Primitive* returnType, const std::string functionName) : Node::Node(tokenLineNumber,functionName), m_returnType(returnType)
{

}

//printTokenString
std::string Func::printTokenString() const
{
    return "Func: " + m_stringValue + " returns type " + m_returnType->printTokenString();
}

//******************************************************
// ************ ParameterNode Class ********************
//******************************************************

//Constructor
Parm::Parm(const int tokenLineNumber,  Primitive* parameterType, const std::string parameterName) : Node::Node(tokenLineNumber,parameterName), m_parameterType(parameterType)
{

}

//printTokenString
std::string Parm::printTokenString() const
{
    if (m_parameterType->getIsArray())
    {
        return "Parm: " + m_stringValue + " of array of type " + m_parameterType->printTokenString();
    }
    else
    {
        return "Parm: " + m_stringValue + " of type " + m_parameterType->printTokenString();
    }
}

//setParameterType
void Parm::setType(Primitive::Type parameterType)
{
    //set parameter type
    m_parameterType->setType(parameterType);

    //check if siblingNode is not null
    if (m_siblingNode != nullptr)
    {
        //set temp node to siblingNode
        Parm *node = (Parm *)m_siblingNode;
        
        //set node type
        node->setType(parameterType);
    }
}

//******************************************************
// ************ VariableNode Class *********************
//******************************************************

//Constructor
Var::Var(const int tokenLineNumber,  Primitive* variableType, const std::string variableName, const bool isStaticVariable) : Node::Node(tokenLineNumber,variableName), m_variableType(variableType), m_isStaticVariable(isStaticVariable)
{

}

//printTokenString
std::string Var::printTokenString() const
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

//***********************setters***********************
//set static variable
void Var::makeStatic()
{
    //check if siblingNode is not null
    if(m_siblingNode != nullptr)
    {
        //set temp node to siblingNode
        ((Var* )m_siblingNode)->makeStatic();
    }
    
    m_isStaticVariable = true;
}

//set variable type
void Var::setType(const Primitive::Type variableType)
{
    //set variable type
    m_variableType->setType(variableType);

    if(m_siblingNode != nullptr)
    {
        //set temp node to siblingNode
        Var* node = (Var *)m_siblingNode;

        //set node type
        node->setType(variableType);
    }
}
