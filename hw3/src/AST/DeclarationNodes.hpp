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

class Primitive
{
    public:

        //Primitive Type Enum
        enum class Type
        {
            INT,
            CHAR,
            BOOL,
            VOID,
        };

        //Constructor
        Primitive(Type type, const bool isArray = false);

        //printTokenString
        std::string printTokenString() const;

        //setters

        //setPrimitiveType
        void setType(Type type);


        //getters
        bool getIsArray() const;

        Type getType() const { return m_type; }
    

    protected:

        Type m_type;

        const bool m_isArray;

        Primitive* m_next;
};

class Func : public Node
{
    public:

        //Constructor
        Func(const int tokenLineNumber, Primitive* returnType, const std::string functionName);
    
        //printTokenString
        std::string printTokenString() const;


    protected:

        const Primitive *m_returnType;
}; 


class Parm : public Node
{
    public:

        //Constructor
        Parm(const int tokenLineNumber,  Primitive* parameterType, const std::string parameterName);
    
        //printTokenString
        std::string printTokenString() const;

        //setters
        void setType(Primitive::Type parameterType);
    

    protected:

        Primitive* m_parameterType;
};


class Var : public Node
{
    public:

        //Constructor
        Var(const int tokenLineNumber, Primitive* variableType, const std::string variableName, const bool isStaticVariable = false);

        //printTokenString
        std::string printTokenString() const;

        //set static variable
        void makeStatic();

        //setters
        void setType(const Primitive::Type variableType);
    

    protected:

        Primitive* m_variableType;

        bool  m_isStaticVariable;
}; 


#endif