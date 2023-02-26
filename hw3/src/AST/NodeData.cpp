/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: NodeData.cpp
DESC: NodeData class definitions for AST nodes. 

*/

#include "NodeData.hpp"

// ************ NodeData Class Constructor ************************
NodeData::NodeData(const NodeData::Type nodeDataType, bool isArray, bool isStatic) :  m_isArray(isArray), m_isStatic(isStatic)
{
    //set next to null
    m_next = nullptr;
   
    //check if array
    if(isArray == true)
    {
        //create new PrimitiveType
        m_next = new NodeData(nodeDataType,false,false);

        //set type to undefined
        m_nodeDataType = NodeData::Type::UNDEFINED;
    }
    else
    {
        m_nodeDataType = nodeDataType;
    }
}

// ****************** NodeData Printers  ******************************
std::string NodeData::printTokenString() const
{
    return convertTypeToString(m_nodeDataType);
}
std::string NodeData::printTokenStringWithType() const
{
    return convertTypeToString(m_nodeDataType);
}

std::string NodeData::convertTypeToString(NodeData::Type type)
{

    std::string tokenOutputString;

    switch (type)
    {
        case Type::INT:
                    {
                        tokenOutputString = "int";
                    }
                    break;

        case Type::BOOL:
                    {
                        tokenOutputString = "bool";
                    }
                    break;

        case Type::CHAR:
                    {
                        tokenOutputString = "char";
                    }
                    break;

        case Type::STRING:
                        {
                            tokenOutputString = "string";
                        }
                        break;

        case Type::UNDEFINED:
                        {
                            tokenOutputString = "undefined";
                        }
                        break;
    
        case Type::VOID:
                {
                    tokenOutputString = "void";
                }
                break;

        default:
            {
                throw std::runtime_error("NodeData::convertTypeToString: Invalid Type");
            }
            break;
    }

    return tokenOutputString;
}


// ****************** NodeData Getters  ******************************
bool NodeData::getIsArray() const
{
    return m_isArray;
}
bool NodeData::getIsStatic() const
{
    return m_isStatic;
}
NodeData::Type NodeData::getNextType() const
{
    if (m_next == nullptr)
    {
        return m_nodeDataType;
    }
    
    return m_next->getNextType();
}
std::string NodeData::getCopyString() const
{
    return m_copyString;
}
NodeData::Type NodeData::getType() const
{
    return m_nodeDataType;
}


// ****************** NodeData Setters  ******************************

void NodeData::setCopyString(std::string copyString)
{
    m_copyString = copyString;
}


void NodeData::setIsArray(bool isArray)
{
    m_isArray = isArray;
}


void NodeData::setIsStatic(bool isStatic)
{
    m_isStatic = isStatic;
}


void NodeData::setType(NodeData::Type type)
{
    m_nodeDataType = type;

    if(m_next != nullptr)
    {
        m_next->setType(type);
    }
}