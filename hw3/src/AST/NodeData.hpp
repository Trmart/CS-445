/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: NodeData.hpp
DESC: NodeData class declarations for AST nodes. 

*/
#ifndef NODEDATA_HPP
#define NODEDATA_HPP


#include <iostream>
#include <string>

class NodeData
{

    public:

        //Node Data Type Enum
        enum class Type { UNDEFINED, INT, BOOL, CHAR, STRING, VOID };

        // ************ NodeData Class Constructor ************************
        NodeData(const NodeData::Type nodeDataType, bool isArray, bool isStatic);

        // ****************** NodeData Printers  ******************************
        std::string printTokenString() const;
        std::string printTokenStringWithType() const;
        static std::string convertTypeToString(const NodeData::Type type);
        
        
        // ****************** NodeData Getters  ******************************
        bool getIsArray() const;
        bool getIsStatic() const;
        NodeData::Type getNextType() const;
        std::string getCopyString() const;
        NodeData::Type getType() const;
        
        
        // ****************** NodeData Setters  ******************************
        void setCopyString(std::string copyString);
        void setIsArray(bool isArray);
        void setIsStatic(bool isStatic);
        void setType(NodeData::Type type);


    protected:

        //Node Data Type
        NodeData::Type m_nodeDataType;

        //is Array
        bool m_isArray = false;

        //is Static
        bool m_isStatic = false;

        NodeData* m_next = nullptr;

        std::string m_copyString;

}; // end class NodeData


#endif // NODEDATA_HPP