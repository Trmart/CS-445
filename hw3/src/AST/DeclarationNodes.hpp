/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: DeclarationNodes.hpp
DESC: DeclarationNodes Subclass. Inherits from Node Base Class. 

*/

#ifndef DECLARATIONNODES_HPP
#define DECLARATIONNODES_HPP


#include "Node.hpp"
#include "NodeData.hpp"

// Function, Parameters, Primitives,  Variable
class DeclarationNode : public Node
{
    public:

    //Declaration Type Enum
    enum class Type
    {
        FUNCTION,
        PARAMETER,
        VARIABLE,
    };

    //Constructor
    DeclarationNode(int tokenLineNumber, const DeclarationNode::Type declarationType, const std::string declarationName, NodeData* data);


    // ****************** Setters ******************************
    void setType(const NodeData::Type type);
    void setShowErrors(const bool showErrors);

    // ****************** Getters ******************************
    const std::string getName() const;
    const NodeData* getNodeData() const;
    const bool getShowErrors() const;
    const DeclarationNode::Type getDeclarationNodeType() const;

    protected:
        const std::string m_declarationName;
        NodeData* m_nodeData;
        const DeclarationNode::Type m_declarationType;
        bool m_showErrors = true; 
};


class Func : public DeclarationNode
{
    public:

        //Constructor
        Func(const int tokenLineNumber, const std::string functionName, NodeData* functionReturnType);
    
        //printTokenString
        std::string printTokenString() const override;

}; 


class Parm : public DeclarationNode
{
    public:

        //Constructor
        Parm(const int tokenLineNumber, const std::string parmName, NodeData* parmData);
    
        //printTokenString
        std::string printTokenString() const override;

        //getters 
        bool getIsUsed() const;
        
        //setters
        void setUsed();
    

    protected:

        bool m_isUsed = false;
};


class Var : public DeclarationNode
{
    public:

        //Constructor
        Var(const int tokenLineNumber, const std::string variableName, NodeData* variableData);

        //printTokenString
        std::string printTokenString() const override;

        //setters
        void setStatic();
        void setInitialized();
        void setUsed();

        //getters                           
        bool getIsUsed() const;
        bool getIsInitialized() const;
    

    protected:

        bool  m_isUsed = false;
        bool  m_isInitialized = false;
}; 


#endif