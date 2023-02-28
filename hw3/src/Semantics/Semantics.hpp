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
        void semanticAnalysis(Node* node);


    private:

        //********************Analyzers**********************
        void analyzeAST(Node *node);
        
        //*********************Declaration Nodes**********************
        void analyzeDeclarationNodeSemantics(const DeclarationNode* declaration);
        void analyzeFunctionNodeSemantics(const Func* function);
        void analyzeParmNodeSemantics(const Parm* parameter);
        void analyzeVariableNodeSemantics(Var* var);
        
        //*********************Expression Nodes**********************
        void analyzeAssignmentNodeSemantics(const Asgn* assignment);
        void analyzeBinaryNodeSemantics(const Binary* binary) const;
        void analyzeCallNodeSemantics(const Call* call) const;
        void analyzeExpressionNodeSemantics(ExpressionNode* expression);
        void analyzeIdentifierNodeSemantics(const Id* identifier) const;
        void analyzeUnaryNodeSemantics(const Unary* unary) const;
        void analyzeUnaryAsssignmentNodeSemantics(const UnaryAsgn* unaryAssignment) const;
        
        //*********************Statement Nodes**********************
        void analyzeCompoundNodeSemantics(const Compound* compound) const;
        void analyzeForNodeSemantics() const;
        void analyzeReturnNodeSemantics(const Return* returnNode) const;
        void analyzeStatementNodeSemantics(const StatementNode* statement) const;


        //********************Symbol Checkers**********************
        void checkIndex(const Binary* binary) const;
        void checkSameTypeOperands(ExpressionNode* expression) const;
        void checkOperands(ExpressionNode* expression, const NodeData::Type type) const;
        void checkUnaryOperands(const Unary* unary) const;
        void checkUnaryAssignmentOperands(const UnaryAsgn* unaryAssignment) const;


        //********************Helper Functions**********************
        bool isMainFunc(const Func* func) const;
        bool isDeclared(const Id* id) const;
        bool hasIndexAncestor(const ExpressionNode* expression) const;
        bool hasAssignmentAncestor(const ExpressionNode* expression) const;
        bool expressionOperandsExist(const ExpressionNode* expression) const;
        bool leftHandSideExists(const ExpressionNode* expression) const;
        std::string getExpressionSymbol(const ExpressionNode* expression) const;
        NodeData* setAndGetExpressionNodeData(const ExpressionNode* expression) const;



        //********************Symbol Table Functions**********************
        void leaveScope();
        bool addToSymbolTable(const DeclarationNode* declaration, const bool global=false);
        DeclarationNode* getFromSymbolTable(const std::string name) const;


        //********************Data Members**********************
        SymbolTable* m_symbolTable;
        Node* m_root;
        bool m_validMainExists = false;

}; 

#endif // SEMANTICS_HPP