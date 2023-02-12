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

// Function, Parameters, Primitives,  Variable
// class DeclarationNodes : public Node
// {
//     public:

//     //Declaration Type Enum
//     enum class Type
//     {
//         FUNCTION,
//         PARAMETER,
//         VARIABLE,
//     };

//     //Constructor
//     DeclarationNodes(int tokenLineNumber, const DeclarationNodes::Type declarationType);

//     protected:
// };

class PrimitiveType
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
        PrimitiveType(const PrimitiveType::Type type, const bool isArray = false);

        //printTokenString
        std::string printTokenString() const;

        //setters

        //setPrimitiveType
        void setPrimitiveType(const PrimitiveType::Type type);


        //getters
        bool getIsArray() const;

        Type getPrimitiveType() const;
    

    protected:

        PrimitiveType::Type m_type;

        const bool m_isArray;

        PrimitiveType *m_next;
};

class FunctionNode : public Node
{
    public:

        //Constructor
        FunctionNode(int tokenLineNumber, const std::string functionName, PrimitiveType *returnType);
    
        //printTokenString
        std::string printTokenString() const;


    protected:

        PrimitiveType *m_returnType;
}; 


class ParameterNode : public Node
{
    public:

        //Constructor
        ParameterNode(int tokenLineNumber, const std::string parameterName, PrimitiveType *parameterType);
    
        //printTokenString
        std::string printTokenString() const;

        //setters
        void setParameterType(PrimitiveType::Type parameterType);
    

    protected:

        PrimitiveType *m_parameterType;
};


class VariableNode : public Node
{
    public:

        //Constructor
        VariableNode(int tokenLineNumber, const std::string variableName, PrimitiveType *variableType, const bool isStaticVariable = false);

        //printTokenString
        std::string printTokenString() const;

        //set static variable
        static void setStaticVariable();

        //setters
        void setVariableType(const PrimitiveType::Type variableType);
    

    protected:

        PrimitiveType *m_variableType;

        bool  m_isStaticVariable;
}; 


#endif