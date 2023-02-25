/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: DeclarationNodes.cpp
DESC: DeclarationNodes Subclass Member Definitions. 
*/

#include "DeclarationNodes.hpp"



//******************************************************
// ************ DeclarationNode Class *******************
//******************************************************

//Constructor
DeclarationNode::DeclarationNode(int tokenLineNumber, const DeclarationNode::Type declarationType, const std::string declarationName, NodeData* data) : Node::Node(tokenLineNumber, Node::Type::DECLARATION), m_declarationName(declarationName), m_nodeData(data), m_declarationType(declarationType)
{

}


// ****************** Setters ******************************
void DeclarationNode::setType(const NodeData::Type type)
{
    //set type
    m_nodeData->setType(type);
    
    //check if node data is not null
    if (m_siblingNode != nullptr)
    {
        //set type
        DeclarationNode* node = (DeclarationNode*)m_siblingNode;
        node->setType(type);
    }
}



void DeclarationNode::setShowErrors(const bool showErrors)
{
    m_showErrors = showErrors;
}

// ****************** Getters ******************************
const std::string DeclarationNode::getName() const
{
    return m_declarationName;
}
const NodeData* DeclarationNode::getNodeData() const
{
    return m_nodeData;
}
const bool DeclarationNode::getShowErrors() const
{
    return m_showErrors;
}
const DeclarationNode::Type DeclarationNode::getDeclarationNodeType() const
{
    return m_declarationType;
}



//******************************************************
// ************ FunctionNode Class *********************
//******************************************************

//Constructor
Func::Func(const int tokenLineNumber, const std::string functionName, NodeData* functionReturnType) : DeclarationNode::DeclarationNode(tokenLineNumber, DeclarationNode::Type::FUNCTION, functionName, functionReturnType)
{

}

//printTokenString
std::string Func::printTokenString() const
{
    return "Func: " + m_declarationName + " returns type " + m_nodeData->printTokenString();
}

//******************************************************
// ************ ParameterNode Class ********************
//******************************************************

//Constructor
Parm::Parm(const int tokenLineNumber, const std::string parmName, NodeData* parmData) : DeclarationNode::DeclarationNode(tokenLineNumber, DeclarationNode::Type::PARAMETER, parmName, parmData)
{

}

//printTokenString
std::string Parm::printTokenString() const
{
    if(m_nodeData == nullptr)
    {
        throw std::runtime_error("Error: ParameterNode::printTokenString() - m_nodeData is null");
    }
    if (m_nodeData->getIsArray())
    {
        return "Parm: " + m_declarationName + " of array of type " + m_nodeData->printTokenString();
    }
    else
    {
        return "Parm: " + m_declarationName + " of type " + m_nodeData->printTokenString();
    }
}

//setUsed
void Parm::setUsed()
{
    m_isUsed = true;
}

//******************************************************
// ************ VariableNode Class *********************
//******************************************************

//Constructor
Var::Var(const int tokenLineNumber,  const std::string variableName, NodeData* variableType) : DeclarationNode::DeclarationNode(tokenLineNumber, DeclarationNode::Type::VARIABLE, variableName, variableType)
{

}

//printTokenString
std::string Var::printTokenString() const
{
    if(m_nodeData == nullptr)
    {
        throw std::runtime_error("Error: VariableNode::printTokenString() - m_nodeData is null");
    }
    if (m_nodeData->getIsArray() && m_nodeData->getIsStatic())
    {
        return "Var: " + m_declarationName + " of static array of type " + m_nodeData->printTokenString();
    }
    else if (m_nodeData->getIsArray())
    {
        return "Var: " + m_declarationName + " of array of type " + m_nodeData->printTokenString();
    }
    else if(m_nodeData->getIsStatic())
    {
        return "Var: " + m_declarationName + " of static type " + m_nodeData->printTokenString();
    }
    else
    {
        return "Var: " + m_declarationName + " of type " + m_nodeData->printTokenString();
    }
}

//***********************setters***********************

void Var::setStatic()
{
    if(m_siblingNode != nullptr)
    {
        ((Var* )m_siblingNode)->setStatic();
    }


    m_nodeData->setIsStatic(true);
}


void Var::setInitialized()
{
    m_isInitialized = true;
}


void Var::setUsed()
{
    m_isUsed = true;
}

//***********************getters***********************

bool Var::getIsInitialized() const
{
    return m_isInitialized;
}

bool Var::getIsUsed() const
{
    return m_isUsed;
}