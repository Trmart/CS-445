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

#include "scanType.hpp"
#include "TokenFormatter.hpp"
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
        Node(int tokenLineNumber, const Node::Type nodeType);

        //Int Constructor
        Node(int tokenLineNumber, int numValue, const Node::Type nodeType);

        //Char Constructor
        Node(int tokenLineNumber, char charValue, const Node::Type nodeType);

        //Bool Constructor
        Node(int tokenLineNumber, bool boolValue, const Node::Type nodeType);

        //String Constructor
        Node(int tokenLineNumber, std::string stringValue, const Node::Type nodeType);

        
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

    protected:
        
        //token data struct from scanType.hpp
        TokenData m_tokenData;

        //Vector of current AST childern Nodes
        std::vector<Node*>m_childernNodes;

        //Keep track of Sibling Nodes
        Node * m_siblingNode;  

        //Node Type
        Node::Type m_nodeType;


}; 


#endif