%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/


#include "scanType.hpp"

#include "EmitDiagnostics.hpp"
#include "CompilerFlags.hpp"
#include "Semantics.hpp"
#include "symbolTable.hpp"
#include "AST.hpp"

#include <iostream>
#include <string>
#include <stdio.h>

// From yacc
extern int yylex();
extern int yydebug;
extern FILE *yyin;

// From c-.l scanner
extern int lineCount;
extern int errorCount;

// AST
Node* root;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << lineCount + 1 << "): " << msg << std::endl;
    errorCount++;
}

%}

%union 
{
    NodeData::Type type;
    TokenData* tokenData;
    Node* node;
}

%token <tokenData> NUMCONST BOOLCONST CHARCONST STRINGCONST ID
%token <tokenData> INT BOOL CHAR STATIC
%token <tokenData> ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token <tokenData> IF THEN ELSE WHILE FOR TO BY DO
%token <tokenData> COLON SEMICOLON COMMA
%token <tokenData> RETURN BREAK
%token <tokenData> AND OR NOT
%token <tokenData> ADD SUB MUL DIV MOD INC DEC QUESTION
%token <tokenData> RPAREN LPAREN RBRACK LBRACK T_BEGIN T_END
%token <tokenData> EQ NEQ LT LEQ GT GEQ

%type <node> program declList decl varDecl scopedVarDecl varDeclList varDeclInit
%type <node> varDeclId funDecl parms parmList parmTypeList parmIdList parmId stmt
%type <node> stmtUnmatched stmtMatched expStmt compoundStmt localDecls stmtList
%type <node> selectStmtUnmatched selectStmtMatched iterStmtUnmatched iterStmtMatched iterRange
%type <node> returnStmt breakStmt exp assignop simpleExp andExp unaryRelExp relExp relOp sumExp
%type <node> sumOp mulExp mulOp unaryExp unaryOp factor mutable immutable call args argList constant

%type <type> typeSpec

%%

program                 : declList
                        {
                            root = $1;
                        }
                        ;

declList                : declList decl
                        {
                            $$ = addSiblingNode($1,$2);
                        }
                        | decl
                        {
                            $$ = $1;
                        }
                        ;

decl                    : varDecl
                        {
                            $$ = $1;
                        }
                        | funDecl
                        {
                            $$ = $1;
                        }
                        ;

varDecl                 : typeSpec varDeclList SEMICOLON
                        {
                            $$ = $2;
                            setSiblingsType($$, $1);
                        }
                        ;

scopedVarDecl           : STATIC typeSpec varDeclList SEMICOLON
                        {
                            $$ = $3;
                            setSiblingsType($$, $2);
                            //$$->isStatic = true;
                            setStatic();
                        }
                        | typeSpec varDeclList SEMICOLON
                        {
                            $$ = $2;
                            setSiblingsType($$, $1);
                        }
                        ;

varDeclList             : varDeclList COMMA varDeclInit
                        {
                            $$ = addSiblingNode($1, $3);
                        }
                        | varDeclInit
                        {
                            $$ = $1;
                        }
                        ;

varDeclInit             : varDeclId
                        {
                            $$ = $1;
                        }
                        | varDeclId COLON simpleExp
                        {
                            $$ = $1; 
                            $1->m_childNodes[0] = $3;
                        }
                        ;

varDeclId               : ID
                        {
                            $$ = newDeclNode(VarK, $1);
                            $$->attr.name = $1->tokenContent;
                        }
                        | ID LBRACK NUMCONST RBRACK
                        {
                            $$ = newDeclNode(VarK, $1);
                            $$->attr.name = $1->tokenContent;
                            $$->isArray = true;
                            $$->expType = Undefined;
                            $1->thisTokenData = $1; 
                        }
                        ;

typeSpec                : INT
                        {
                            $$ = ReturnType::INT;
                        }
                        | BOOL
                        {
                            $$ = ReturnType::BOOL;
                        }
                        | CHAR
                        {
                            $$ = ReturnType::CHAR;
                        }
                        ;

funDecl                 : typeSpec ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = newDeclNode(DeclarationType::FUNCTION, $2);
                            $$->nodeAttributes.name = $2->tokenContent;
                            $$->m_childNodes[0] = $4;
                            $$->m_childNodes[1] = $6;
                            $$->setExpType($1);
                        }
                        | ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = newDeclNode(DeclarationType::FUNCTION, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->m_childNodes[0] = $3;
                            $$->m_childNodes[1] = $5;
                        }
                        ;

parms                   : parmList
                        {
                            $$ = $1;
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

parmList                : parmList SEMICOLON parmTypeList
                        {
                            $$->addSiblingNode($1, $3)
                        }
                        | parmTypeList
                        {
                            $$ = $1;
                        }
                        ;

parmTypeList            : typeSpec parmIdList
                        {
                            $$ = $2;
                            setSiblingsType($$, $1);
                        }
                        ;

parmIdList              : parmIdList COMMA parmId
                        {
                            $$ = addSiblingNode($1, $3);
                            
                        }
                        | parmId
                        {
                            $$ = $1;
                        }
                        ;

parmId                  : ID
                        {
                            $$ = newDeclNode(DeclarationType::PARAMETER, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | ID LBRACK RBRACK
                        {
                            $$ = newDeclNode(DeclarationType::PARAMETER, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->isArray = true;
                        }
                        ;

stmt                    : stmtUnmatched
                        {
                            $$ = $1;
                        }
                        | stmtMatched
                        {
                            $$ = $1;
                        }
                        ;

stmtUnmatched           : selectStmtUnmatched
                        {
                            $$ = $1;
                        }
                        | iterStmtUnmatched
                        {
                            $$ = $1;
                        }
                        ;

stmtMatched             : selectStmtMatched
                        {
                            $$ = $1;
                        }
                        | iterStmtMatched
                        {
                            $$ = $1;
                        }
                        | expStmt
                        {
                            $$ = $1;
                        }
                        | compoundStmt
                        {
                            $$ = $1;
                        }
                        | returnStmt
                        {
                            $$ = $1;
                        }
                        | breakStmt
                        {
                            $$ = $1;
                        }
                        ;

expStmt                 : exp SEMICOLON
                        {
                            $$ = $1;
                        }
                        | SEMICOLON
                        {
                            $$ = nullptr;
                        }
                        ;

compoundStmt            : T_BEGIN localDecls stmtList T_END
                        {
                            $$ = newStmtNode(StatementType::COMPOUND, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $3;
                        }
                        ;

localDecls              : localDecls scopedVarDecl
                        {
                            $$ = addSiblingNode($1, $2);
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

stmtList                : stmtList stmt
                        {
                            $$ = addSiblingNode($1, $2);
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

selectStmtUnmatched     : IF simpleExp THEN stmt
                        {
                            $$ = newStmtNode(StatementType::IF, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $4;
                        }
                        | IF simpleExp THEN stmtMatched ELSE stmtUnmatched
                        {
                            $$ = newStmtNode(StatementType::IF, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $4;
                            $$->m_childNodes[2] = $6;
                        }
                        ;

selectStmtMatched       : IF simpleExp THEN stmtMatched ELSE stmtMatched
                        {
                            $$ = newStmtNode(StatementType::IF, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $4;
                            $$->m_childNodes[2] = $6;
                        }
                        ;

iterStmtUnmatched       : WHILE simpleExp DO stmtUnmatched
                        {
                            $$ = newStmtNode(StatementType::WHILE, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $4;
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | FOR ID ASGN iterRange DO stmtUnmatched
                        {
                            $$ = newStmtNode(StatementType::FOR, $1);
                            $$->m_childNodes[0] = newDeclNode(DeclarationType::VARIABLE, $2);
                            $$->m_childNodes[0]->setExpType(ReturnType::INT); 
                            $$->nodeAttributes.name = $3->tokenContent;
                            $$->m_childNodes[1] = $4;
                            $$->m_childNodes[2] = $6;
                        }
                        ;

iterStmtMatched         : WHILE simpleExp DO stmtMatched
                        {
                            $$ = newStmtNode(StatementType::WHILE, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $4;
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | FOR ID ASGN iterRange DO stmtMatched
                        {
                            $$ = newStmtNode(StatementType::FOR, $1);
                            $$->m_childNodes[0] = $2;
                            $$->m_childNodes[1] = $4;
                            $$->m_childNodes[2] = $6;
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        ;

iterRange               : simpleExp TO simpleExp
                        {
                            $$ = newStmtNode(StatementType::RANGE, $1);
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                        }
                        | simpleExp TO simpleExp BY simpleExp
                        {
                            $$ = newStmtNode(StatementType::RANGE, $1);
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                            $$->m_childNodes[2] = $5;
                        }
                        ;

returnStmt              : RETURN SEMICOLON
                        {
                            $$ = newStmtNode(StatementType::RETURN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | RETURN exp SEMICOLON
                        {
                            $$ = newStmtNode(StatementType::RETURN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->m_childNodes[0] = $2;
                            $$->setExpType($2->getExpType());
                        }
                        ;

breakStmt               : BREAK SEMICOLON
                        {
                            $$ = newStmtNode(StatementType::BREAK, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        ;

exp                     : mutable assignop exp
                        {
                            $$ = $2;
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                        }
                        | mutable INC
                        {
                            $$ = newExpNode(ExpressionType::ASSIGN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->m_childNodes[0] = $1;
                            $$->setExpType(ReturnType::INT);
                        }
                        | mutable DEC
                        {
                            $$ = newExpNode(ExpressionType::ASSIGN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->m_childNodes[0] = $1;
                            $$->setExpType(ReturnType::INT);
                        }
                        | simpleExp
                        {
                            $$ = $1;
                        }
                        ;

assignop                : ASGN
                        {
                           $$ = newExprNode(ExpressionType::ASSIGN, $1);
                           $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | ADDASGN
                        {
                            $$ = newExprNode(ExpressionType::ASSIGN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | SUBASGN
                        {
                            $$ = newExprNode(ExpressionType::ASSIGN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | MULASGN
                        {
                            $$ = newExprNode(ExpressionType::ASSIGN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | DIVASGN
                        {
                            $$ = newExprNode(ExpressionType::ASSIGN, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        ;

simpleExp               : simpleExp OR andExp
                        {
                            $$ = newExpNode(ExpressionType::OP, $2);
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                            $$->nodeAttributes.name = $2->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | andExp
                        {
                            $$ = $1;
                        }
                        ;

andExp                  : andExp AND unaryRelExp
                        {
                            $$ = newExpNode(ExpressionType::OP, $2);
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                            $$->nodeAttributes.name = $2->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | unaryRelExp
                        {
                            $$ = $1;
                        }
                        ;

unaryRelExp             : NOT unaryRelExp
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->m_childNodes[0] = $2;
                            $$->nodeAttributes.name = $2->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | relExp
                        {
                            $$ = $1;
                        }
                        ;

relExp                  : sumExp relOp sumExp
                        {
                            $$ = $2;
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                        }
                        | sumExp
                        {
                            $$ = $1;
                        }
                        ;

relOp                   : LT
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | LEQ
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | GT
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | GEQ
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | EQ
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        | NEQ
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::BOOL);
                        }
                        ;

sumExp                  : sumExp sumOp mulExp
                        {
                            $$ = $2;
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                        }
                        | mulExp
                        {
                            $$ = $1;
                        }
                        ;

sumOp                   : ADD
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        | SUB
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        ;

mulExp                  : mulExp mulOp unaryExp
                        {
                            $$ = $2;
                            $$->m_childNodes[0] = $1;
                            $$->m_childNodes[1] = $3;
                        }
                        | unaryExp
                        {
                            $$ = $1;
                        }
                        ;

mulOp                   : MUL
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        | DIV
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        | MOD
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        ;

unaryExp                : unaryOp unaryExp
                        {
                            $$ = $1;
                            $$->m_childNodes[0] = $2;
                        }
                        | factor
                        {
                            $$ = $1;
                        }
                        ;

unaryOp                 : SUB
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        | MUL
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        | QUESTION
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::INT);
                        }
                        ;

factor                  : mutable
                        {
                            $$ = $1;
                        }
                        | immutable
                        {
                            $$ = $1;
                        }
                        ;

mutable                 : ID
                        {
                            $$ = newExpNode(ExpressionType::OP, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | ID LBRACK exp RBRACK
                        {
                            $$ = newExpNode(ExpressionType::OP, $2);
                            $$->nodeAttributes.name = $2->tokenContent;
                            $$->m_childNodes[0] = newExpNode(ExpressionType::IDENTIFIER, $1);
                            $$->m_childNodes[0]->nodeAttributes.name = $1->tokenContent;
                            $$->m_childNodes[0]->setIsArray(true); 
                            $$->m_childNodes[1] = $3;
                        }
                        ;

immutable               : LPAREN exp RPAREN
                        {
                            $$ = $2;
                        }
                        | call
                        {
                            $$ = $1;
                        }
                        | constant
                        {
                            $$ = $1;
                        }
                        ;

call                    : ID LPAREN args RPAREN
                        {
                            $$ = newExpNode(ExpressionType::CALL, $1);
                            $$->m_childNodes[0] = $3;
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        ;

args                    : argList
                        {
                            $$ = $1;
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

argList                 : argList COMMA exp
                        {
                            $$ = addSiblingNode($1, $3);
                        }
                        | exp
                        {
                            $$ = $1;
                        }
                        ;

constant                : NUMCONST
                        {
                            $$ = newExpNode(ExpressionType::CONSTANT, $1);
                            $$->nodeAttributes.intVal = $1->numValue;
                            $$->setExpType(ReturnType::INT);
                        }
                        | BOOLCONST
                        {
                            $$ = newExpNode(ExpressionType::CONSTANT, $1);
                            $$->nodeAttributes.intVal = $1->numValue;
                            $$->setExpType(ReturnType::BOOL);
                            $$->nodeAttributes.name = $1->tokenContent;
                        }
                        | CHARCONST
                        {
                            $$ = newExpNode(ExpressionType::CONSTANT, $1);
                            $$->nodeAttributes.name = $1->tokenContent;
                            $$->setExpType(ReturnType::CHAR);
                            $$->m_tokenData = $1;
                        }
                        | STRINGCONST
                        {
                            $$ = newExpNode(ExpressionType::CONSTANT, $1);
                            $$->nodeAttributes.stringVal = $1->stringValue;
                            $$->setExpType(ReturnType::CHARINT);
                            $$->setIsArray(true);
                        }
                        ;

%%

int main(int argc, char *argv[])
{

    //create the compiler flags object. This will parse the command line arguments
    CompilerFlags compilerFlags(argc, argv);

    //get the debug flag from the compiler flags object
    yydebug = compilerFlags.getDebugFlag();

    //get the file name from the compiler flags object
    std::string fileName = argv[argc - 1];

    //if the compiler flags object has an error, print the error and exit
    if (argc > 1 && !(yyin = fopen(fileName.c_str(), "r")))
    {
        // if failed to open file
        //print error message
        //exit with error
        throw std::runtime_error("Cannot open file: \'" + fileName + "\'");
        
        //print the number of errors and warnings
        EmitDiagnostics::Error::emitArgListError("source file \"" + fileName + "\" could not be opened. Terminating compilation."); 

        EmitDiagnostics::Warning::emitWarningCount();

        EmitDiagnostics::Error::emitErrorCount();

        exit(1);
    }

    //parse the input
    yyparse();



    //if the the -p flag was passed, print the AST
    if(compilerFlags.getPrintASTFlag() && !compilerFlags.getPrintASTWithTypesFlag())
    {
        //if the root is null, throw an error
        if (root == nullptr)
        {
            throw std::runtime_error("main(): Cannot print root: nullptr");
        }

        //print the AST without types
        printAST(root, 0, false);
    }
    else if(compilerFlags.getPrintASTFlag() && compilerFlags.getPrintASTWithTypesFlag())
    {
        //if the root is null, throw an error
        if (root == nullptr)
        {
            throw std::runtime_error("main(): Cannot print root: nullptr");
        }

        //setupIO();
        //create the semantics analyzer
        Semantics semanticAnalyzer = Semantics();
    
        //perform semantic analysis
        //semanticAnalyzer.semanticAnalysis(root);

        //code generation will eventually go here

        if(EmitDiagnostics::Error::getErrorCount() < 1)
        {
            //print the AST with types
            printAST(root, 0, true);
        }
    }


    //print the number of errors and warnings
    EmitDiagnostics::Warning::emitWarningCount();
    EmitDiagnostics::Error::emitErrorCount();

    //delete the tree root. Free the memory. 
    delete root;

    //close the file sent into the c- compiler
    fclose(yyin);


    //close the file and exit with success
    return 0;
}
