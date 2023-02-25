/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/26/2023

FILE: Semantics.hpp
DESC: Semantics Class Declaration.  For semantic analysis of AST

*/
#ifndef SEMANTICS_HPP
#define SEMANTICS_HPP

#include "symbolTable.hpp"
#include "ASTNodeIdentifier.hpp"
#include "../Emit/EmitDiagnostics.hpp"
#include "../AST/AST.hpp"

#include <string>
#include <sstream>

class Semantics
{
    public: 

        // Constructor
        Semantics(SymbolTable* symbolTable);

        // Semantic Analysis
        void analyze(Node* node);


    protected:

        //********************Analyzers**********************
        void analyzeAST(Node *node);
        
        //*********************Declaration Nodes**********************
        void analyzeDeclarationNode(const DeclarationNode* declaration);
        void analyzeFunctionNode(const Func* func);
        void analyzeParmNode(const Parm* parm);
        void analyzeVariableNode(Var* var);
        
        //*********************Expression Nodes**********************
        void analyzeAssignmentNode(const Asgn* asgn);
        void analyzeBinaryNode(const Binary* binary) const;
        void analyzeCallNode(const Call* call) const;
        void analyzeExpressionNode(ExpressionNode* expression);
        void analyzeIdentifierNode(const Id* id) const;
        void analyzeUnaryNode(const Unary* unary) const;
        void analyzeUnaryAsgn(const UnaryAsgn* unaryAsgn) const;
        
        //*********************Statement Nodes**********************
        void analyzeCompoundNode(const Compound* compound) const;
        void analyzeForNode() const;
        void analyzeReturnNode(const Return* returnNode) const;
        void analyzeStatementNode(const StatementNode* statement) const;


        //********************Symbol Checkers**********************
        void checkIndex(const Binary* binary) const;
        void checkOperandsOfSameType(ExpressionNode* expression) const;
        void checkOperandsOfType(ExpressionNode* expression, const NodeData::Type type) const;
        void checkUnaryOperands(const Unary* unary) const;
        void checkUnaryAsgnOperands(const UnaryAsgn* unaryAsgn) const;


        //********************Helper Functions**********************
        bool isMainFunc(const Func* func) const;
        bool isDeclared(const Id* id) const;
        bool hasIndexAncestor(const ExpressionNode* expression) const;
        bool hasAsgnAncestor(const ExpressionNode* expression) const;
        bool expOperandsExist(const ExpressionNode* expression) const;
        bool lhsExists(const ExpressionNode* expression) const;
        std::string getExpSym(const ExpressionNode* expression) const;
        NodeData* setAndGetExpData(const ExpressionNode* expression) const;



        //********************Symbol Table Functions**********************
        void leaveScope();
        bool addToSymTable(const DeclarationNode* declaration, const bool global=false);
        DeclarationNode * getFromSymTable(const std::string name) const;


        //********************Data Members**********************
        SymbolTable* m_symbolTable;
        Node* m_root;
        bool m_validMainExists = false;

}; 

#endif // SEMANTICS_HPP