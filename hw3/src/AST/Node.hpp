/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

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
        

        enum class Type {NONE, EXPRESSION, DECLARATION, STATEMENT};
        
        
        // ************ Node Class Constructors ************************

        Node(const int tokenLineNumber);
        
        Node(const int tokenLineNumber, const Node::Type nodeType);

        
        // ******************** Node Base Class Destructor *********************
        ~Node(); 


        // ******************* Node Print Functions *****************************

        //Print Token Output String
        virtual std::string printTokenString() const;
        virtual std::string printTokenStringWithType() const;

        //Print AST Nodes
        virtual void printASTNode(const bool showNodeTypes = false) const;

        //Print The Whole AST
        void printAST(const bool showNodeTypes = false) const;

        //Print the Formatting Output Tabs for the Correct AST Output 
        void printOutputTabs(const int numTabs) const; 
        
        // ****************** Node adding functions ******************************

        //add child node to AST
        void addChildNode(Node* node);

        //add sibling node to AST 
        void addSiblingNode(Node* node); 

        bool isAncestorNodeAssignedAType(const Node::Type nodeType) const;
        
        // ****************** Node Getters and Setters ******************************
        
        int getTokenLineNumber() const;
        Node* getSiblingNode() const;
        Node::Type getNodeType() const;
        Node* getParentNode() const;
        bool getIsNodeAnalyzed() const;
        Node* getNodeAncestor(const Node::Type nodeType) const;
        std::vector<Node* > getChildernNodes() const;
        
        
        void setIsNodeAnalyzed();
        void setNodeType(const Node::Type nodeType);
        void setParentNode(Node* parentNode);


    protected:


        //Keep track of Sibling Nodes
        Node* m_siblingNode;  


    private:


        //token data storage struct from scanType.hpp
        const int m_tokenLineNumber; 

        //Vector of current AST childern Nodes
        std::vector<Node* >m_childernNodes;


        //Node Type
        const Node::Type m_nodeType;

        //Parent Node
        Node* m_parentNode;

        //isNodeAnalyzed
        bool m_isNodeAnalyzed = false;
}; 


#endif