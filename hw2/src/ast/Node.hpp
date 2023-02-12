/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: Node.hpp
DESC: Node base class declarations for AST nodes. Statements, Expressions, and Declarations will inherit from this class.

*/

#ifndef NODE_HPP
#define NODE_HPP

#include "../scanType.hpp"
#include "../TokenFormatter.hpp"
#include <vector>
#include <string>
#include <iostream>

//This is the base class for all nodes in the AST
//Statements, Expressions, and Declarations all inherit from this class
class Node
{
    public:
        

        enum class Type {None, Statement, Expression, Declaration};
        
        
        // ************ Node Class Constructors ************************
        
        //Base Constructors
        Node(); 
        Node(int tokenLineNumber);

        //Int Constructor
        Node(const int tokenLineNumber, const int numValue);

        //Char Constructor
        Node(const int tokenLineNumber, const char charValue);

        //Bool Constructor
        Node(const int tokenLineNumber, const bool boolValue);

        //String Constructor
        Node(const int tokenLineNumber, const std::string stringValue);

        
        // ******************** Node Base Class Destructor *********************
        ~Node(); 


        // ******************* Node Print Functions *****************************

        //Print Token Output String
        virtual std::string printTokenString() const;

        //Print AST Nodes
        virtual void printASTNode() const;

        //Print The Whole AST
        void printAST() const;

        //Print the Formatting Output Tabs for the Correct AST Output 
        void printOutputTabs(const int numTabs) const; 
        
        // ****************** Node adding functions ******************************

        //add child node to AST
        void addChildNode(Node* node);

        //add sibling node to AST 
        void addSiblingNode(Node* node); 

        int getTokenLineNumber() const;

    protected:


        //token data storage struct from scanType.hpp
        const int m_tokenLineNumber; 
        int m_numValue;
        bool m_boolValue;
        char m_charValue;
        std::string m_stringValue;
        bool m_isCharLengthGreaterThan1 = false;
        

        //Vector of current AST childern Nodes
        std::vector<Node*>m_childernNodes;

        //Keep track of Sibling Nodes
        Node * m_siblingNode;  

        //Node Type
        // Node::Type m_nodeType;


}; 


#endif