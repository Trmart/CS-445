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
DeclarationNode::DeclarationNode(int tokenLineNumber, const DeclarationNode::Type declarationType, const std::string declarationName, NodeData* data) : Node::Node(tokenLineNumber, Node::Type::DECLARATION),  m_declarationType(declarationType), m_declarationName(declarationName), m_nodeData(data)
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
std::string DeclarationNode::getName() const
{
    return m_declarationName;
}
NodeData* DeclarationNode::getNodeData() const
{
    return m_nodeData;
}
bool DeclarationNode::getShowErrors() const
{
    return m_showErrors;
}
DeclarationNode::Type DeclarationNode::getDeclarationNodeType() const
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
    
    return "Parm: " + m_declarationName + " of type " + m_nodeData->printTokenString();
    
}

//setUsed
void Parm::setUsed()
{
    m_isUsed = true;
}
void Parm::setHasNotBeenUsed()
{
    m_hasNotBeenUsed = false;
}

bool Parm::getIsUsed() const
{
    return m_isUsed;
}

bool Parm::getHasNotBeenUsed() const
{
    return m_hasNotBeenUsed;
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

    return "Var: " + m_declarationName + " of type " + m_nodeData->printTokenString();

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

void Var::setHasNotBeenUsed()
{
    m_hasNotBeenUsed = true;
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

bool Var::getHasNotBeenUsed() const
{
    return m_hasNotBeenUsed;
}