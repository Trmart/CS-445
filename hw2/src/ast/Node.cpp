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

//Base Constructors

Node :: Node(int tokenLineNumber) : m_tokenLineNumber{tokenLineNumber}, m_siblingNode{nullptr}
{

}


//Int Constructor
Node :: Node(int tokenLineNumber, int numValue) : m_tokenLineNumber{tokenLineNumber}, m_numValue{numValue}, m_siblingNode{nullptr}
{

}

//Char Constructor
Node :: Node(int tokenLineNumber, char charValue) : m_tokenLineNumber{tokenLineNumber}, m_charValue{charValue}, m_siblingNode{nullptr}
{

}

//Bool Constructor
Node :: Node(int tokenLineNumber, bool boolValue) : m_tokenLineNumber{tokenLineNumber}, m_boolValue{boolValue}, m_siblingNode{nullptr}
{

}

//String Constructor
Node :: Node(int tokenLineNumber, std::string stringValue) : m_tokenLineNumber{tokenLineNumber}, m_stringValue{stringValue}, m_siblingNode{nullptr}
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
void Node :: printASTNode() const
{
    printTokenString(); 
}

//Print The Whole AST
void Node :: printAST() const
{
    int numSiblingNodes = 0; 

    int numTabs = 0; 

    printASTNode(); 
    printTokenString(); 

    //increment number of tabs. default is 1
    numTabs++; 

    //go through and print all of the childern nodes. 
    for(int i = 0; i < m_childernNodes.size(); i++)
    {
        Node *tempChildNode = m_childernNodes[i]; 
        
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

            tempChildNode->printAST();

            numSiblingNodes = tempSiblingCount; 

        }
    }

    numTabs--; 

    numSiblingNodes++; 


    //check to see if the sibling node is nullptr
    if(m_siblingNode != nullptr)
    {
        printASTNode();
        std :: cout << "Sibling: " + std :: to_string(numSiblingNodes) << "  "; 
        m_siblingNode->printAST(); 
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
    //check if the node is not null
    if(node != nullptr)
    {
        //check if the sibling is not null
        if(m_siblingNode != nullptr)
        {
            //if sibling is not null, recursivley call addSiblingNode untill the node can be added. 
            m_siblingNode->addSiblingNode(node); 
        }
        else
        {
            //if sibling is null, add sibling node
            m_siblingNode = node; 
        }
    }
    else
    {
        return; 
    }
}

int Node :: getTokenLineNumber() const
{
    return m_tokenLineNumber;
}

