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