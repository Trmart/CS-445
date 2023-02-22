/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: Node.cpp
DESC: Node base class definitions for AST nodes. Statements, Expressions, and Declarations will inherit from this class.

*/

#include "Node.hpp"


// ************ Node Class Constructors ************************


Node::Node(const int tokenLineNumber) : m_tokenLineNumber(tokenLineNumber), m_nodeType(Node::Type::None), m_siblingNode(nullptr), m_parentNode(nullptr)
{

}


Node::Node(const int tokenLineNumber, const Node::Type nodeType) : m_tokenLineNumber(tokenLineNumber), m_nodeType(nodeType), m_siblingNode(nullptr), m_parentNode(nullptr)
{

}


// ******************** Node Base Class Destructor *********************
Node :: ~Node()
{
    // delete the AST nodes sibling
    if(m_siblingNode != nullptr)
    {
        delete m_siblingNode;
    }

    //delete all the AST Nodes Childern
    for(auto &node : m_childernNodes)
    {
        delete node; 
    } 
}


// ******************* Node Print Functions *****************************

//Print Token Output String
std::string Node ::printTokenString() const
{
    return " [line: " + std::to_string(m_tokenLineNumber) + "]";
}

//Print AST Nodes
void Node :: printASTNode(const bool showNodeTypes) const
{
    std:: cout << printTokenString(); 
}

//Print The Whole AST
void Node :: printAST(const bool showNodeTypes) const
{
    static int numSiblingNodes = 0; 

    static int numTabs = 0; 

    printASTNode(showNodeTypes); 

    std::cout << " [line: " << m_tokenLineNumber << "]" << std::endl;

    //increment number of tabs. default is 1
    numTabs++; 

    //go through and print all of the childern nodes. 
    for(int i = 0; i < m_childernNodes.size(); i++)
    {
        Node* tempChildNode = m_childernNodes[i]; 
        
        //check and make sure the ith child node is not null
        if(tempChildNode != nullptr)
        {
            //print formatting output tabs
            printOutputTabs(numTabs); 

            //print current child node
            std :: cout << "Child: " + std::to_string(i) << "  "; 
            
            //init temp sibling count to how current node sibling count. 
            int tempSiblingCount = numSiblingNodes; 

            numSiblingNodes = 0; 

            tempChildNode->printAST(showNodeTypes);

            numSiblingNodes = tempSiblingCount; 

        }
    }

    numTabs--; 

    numSiblingNodes++; 


    //check to see if the sibling node is nullptr
    if(m_siblingNode != nullptr)
    {
        //print formatting output tabs
        printOutputTabs(numTabs);
        //print current sibling node
        std :: cout << "Sibling: " + std :: to_string(numSiblingNodes) << "  "; 
        //print the sibling node
        m_siblingNode->printAST(showNodeTypes); 
    } 

    //decrement number of sibling nodes
    numSiblingNodes--;
}

//Print the Formatting Output Tabs for the Correct AST Output 
void Node :: printOutputTabs(const int numTabs) const
{
    for(int i = 0; i < numTabs; i++)
    {
        std::cout << ".   "; 
    }
}

// ****************** Node adding functions ******************************

//add child node to AST
void Node :: addChildNode(Node* node)
{
    //add the sibling node to the childern node vector
    m_childernNodes.push_back(node); 
}

//add sibling node to AST 
void Node :: addSiblingNode(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (m_siblingNode == nullptr)
    {
        m_siblingNode = node;
    }
    else
    {
        m_siblingNode->addSiblingNode(node);
    }
}

int Node :: getTokenLineNumber() const
{
    return m_tokenLineNumber;
}


