%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/26/2023

FILE: parser.y
DESC: yacc parser for the calculator language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#include "scanType.hpp"

#include "Emit/EmitDiagnostics.hpp"
#include "CompilerFlags.hpp"
#include "Semantics/Semantics.hpp"
#include "Semantics/symbolTable.hpp"
#include "AST/AST.hpp"

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
                            $$ = $1;
                            root = $$;
                        }
                        ;

declList                : declList decl
                        {
                            $$ = $1;
                            $$->addSiblingNode($2);
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
                            Var *node = (Var *)$$;
                            node->setType($1);
                        }
                        ;

scopedVarDecl           : STATIC typeSpec varDeclList SEMICOLON
                        {
                            $$ = $3;
                            Var *node = (Var *)$$;
                            node->setType($2);
                            node->setStatic();
                        }
                        | typeSpec varDeclList SEMICOLON
                        {
                            $$ = $2;
                            Var *node = (Var *)$$;
                            node->setType($1);
                        }
                        ;

varDeclList             : varDeclList COMMA varDeclInit
                        {
                            $$ = $1;
                            $$->addSiblingNode($3);
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
                            Var* var = (Var* )($1);
                            var->setInitialized();
                            $$ = var;
                            $$->addChildNode($3);
                        }
                        ;

varDeclId               : ID
                        {
                            $$ = new Var($1->tokenLineNumber, $1->tokenInformation, new NodeData(NodeData::Type::UNDEFINED, false, false));
                        }
                        | ID LBRACK NUMCONST RBRACK
                        {
                            $$ = new Var($1->tokenLineNumber, $1->tokenInformation, new NodeData(NodeData::Type::UNDEFINED, true, false));
                        }
                        ;

typeSpec                : INT
                        {
                            $$ = NodeData::Type::INT;
                        }
                        | BOOL
                        {
                            $$ = NodeData::Type::BOOL;
                        }
                        | CHAR
                        {
                            $$ = NodeData::Type::CHAR;
                        }
                        ;

funDecl                 : typeSpec ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = new Func($2->tokenLineNumber, $2->tokenInformation, new NodeData($1, false, false));
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        | ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = new Func($1->tokenLineNumber, $2->tokenInformation, new NodeData(NodeData::Type::VOID, false, false));
                            $$->addChildNode($3);
                            $$->addChildNode($5);
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
                            $$ = $1;
                            $$->addSiblingNode($3);
                        }
                        | parmTypeList
                        {
                            $$ = $1;
                        }
                        ;

parmTypeList            : typeSpec parmIdList
                        {
                            $$ = $2;
                            Parm* node = (Parm* )$$;
                            node->setType($1);
                        }
                        ;

parmIdList              : parmIdList COMMA parmId
                        {
                            if ($1 == nullptr)
                            {
                                $$ = $3;
                            }
                            else
                            {
                                $$ = $1;
                                $$->addSiblingNode($3);
                            }
                        }
                        | parmId
                        {
                            $$ = $1;
                        }
                        ;

parmId                  : ID
                        {
                            $$ = new Parm($1->tokenLineNumber, $1->tokenInformation, new NodeData(NodeData::Type::UNDEFINED, false, false));
                        }
                        | ID LBRACK RBRACK
                        {
                            $$ = new Parm($1->tokenLineNumber, $1->tokenInformation, new NodeData(NodeData::Type::UNDEFINED, true, false));
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
                            $$ = new Compound($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($3);
                        }
                        ;

localDecls              : localDecls scopedVarDecl
                        {
                            if ($1 == nullptr)
                            {
                                $$ = $2;
                            }
                            else
                            {
                                $$ = $1;
                                $$->addSiblingNode($2);
                            }
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

stmtList                : stmtList stmt
                        {
                            if ($1 == nullptr)
                            {
                                $$ = $2;
                            }
                            else
                            {
                                $$ = $1;
                                $$->addSiblingNode($2);
                            }
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

selectStmtUnmatched     : IF simpleExp THEN stmt
                        {
                            $$ = new If($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                        }
                        | IF simpleExp THEN stmtMatched ELSE stmtUnmatched
                        {
                            $$ = new If($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

selectStmtMatched       : IF simpleExp THEN stmtMatched ELSE stmtMatched
                        {
                            $$ = new If($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

iterStmtUnmatched       : WHILE simpleExp DO stmtUnmatched
                        {
                            $$ = new While($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                        }
                        | FOR ID ASGN iterRange DO stmtUnmatched
                        {
                            $$ = new For($1->tokenLineNumber);
                            Var* node = new Var($2->tokenLineNumber, $2->tokenInformation, new NodeData(NodeData::Type::INT, false, false));
                            node->setInitialized();
                            $$->addChildNode(node);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

iterStmtMatched         : WHILE simpleExp DO stmtMatched
                        {
                            $$ = new While($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                        }
                        | FOR ID ASGN iterRange DO stmtMatched
                        {
                            $$ = new For($1->tokenLineNumber);
                            Var *node = new Var($2->tokenLineNumber, $2->tokenInformation, new NodeData(NodeData::Type::INT, false, false));
                            node->setInitialized();
                            $$->addChildNode(node);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

iterRange               : simpleExp TO simpleExp
                        {
                            $$ = new Range($1->getTokenLineNumber());
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | simpleExp TO simpleExp BY simpleExp
                        {
                            $$ = new Range($1->getTokenLineNumber());
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                            $$->addChildNode($5);
                        }
                        ;

returnStmt              : RETURN SEMICOLON
                        {
                            $$ = new Return($1->tokenLineNumber);
                        }
                        | RETURN exp SEMICOLON
                        {
                            $$ = new Return($1->tokenLineNumber);
                            $$->addChildNode($2);
                        }
                        ;

breakStmt               : BREAK SEMICOLON
                        {
                            $$ = new Break($1->tokenLineNumber);
                        }
                        ;

exp                     : mutable assignop exp
                        {
                            $$ = $2;
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | mutable INC
                        {
                            $$ = new UnaryAsgn($1->getTokenLineNumber(), UnaryAsgn::Type::INC);
                            $$->addChildNode($1);
                        }
                        | mutable DEC
                        {
                            $$ = new UnaryAsgn($1->getTokenLineNumber(), UnaryAsgn::Type::DEC);
                            $$->addChildNode($1);
                        }
                        | simpleExp
                        {
                            $$ = $1;
                        }
                        ;

assignop                : ASGN
                        {
                            $$ = new Asgn($1->tokenLineNumber, Asgn::Type::ASGN);
                        }
                        | ADDASGN
                        {
                            $$ = new Asgn($1->tokenLineNumber, Asgn::Type::ADDASS);
                        }
                        | SUBASGN
                        {
                            $$ = new Asgn($1->tokenLineNumber, Asgn::Type::SUBASS);
                        }
                        | MULASGN
                        {
                            $$ = new Asgn($1->tokenLineNumber, Asgn::Type::MULASS);
                        }
                        | DIVASGN
                        {
                            $$ = new Asgn($1->tokenLineNumber, Asgn::Type::DIVASS);
                        }
                        ;

simpleExp               : simpleExp OR andExp
                        {
                            $$ = new Binary($1->getTokenLineNumber(), Binary::Type::OR);
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | andExp
                        {
                            $$ = $1;
                        }
                        ;

andExp                  : andExp AND unaryRelExp
                        {
                            $$ = new Binary($1->getTokenLineNumber(), Binary::Type::AND);
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | unaryRelExp
                        {
                            $$ = $1;
                        }
                        ;

unaryRelExp             : NOT unaryRelExp
                        {
                            $$ = new Unary($1->tokenLineNumber, Unary::Type::NOT);
                            $$->addChildNode($2);
                        }
                        | relExp
                        {
                            $$ = $1;
                        }
                        ;

relExp                  : sumExp relOp sumExp
                        {
                            $$ = $2;
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | sumExp
                        {
                            $$ = $1;
                        }
                        ;

relOp                   : LT
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::LT);
                        }
                        | LEQ
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::LEQ);
                        }
                        | GT
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::GT);
                        }
                        | GEQ
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::GEQ);
                        }
                        | EQ
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::EQ);
                        }
                        | NEQ
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::NEQ);
                        }
                        ;

sumExp                  : sumExp sumOp mulExp
                        {
                            $$ = $2;
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | mulExp
                        {
                            $$ = $1;
                        }
                        ;

sumOp                   : ADD
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::ADD);
                        }
                        | SUB
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::SUB);
                        }
                        ;

mulExp                  : mulExp mulOp unaryExp
                        {
                            $$ = $2;
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | unaryExp
                        {
                            $$ = $1;
                        }
                        ;

mulOp                   : MUL
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::MUL);
                        }
                        | DIV
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::DIV);
                        }
                        | MOD
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::MOD);
                        }
                        ;

unaryExp                : unaryOp unaryExp
                        {
                            $$ = $1;
                            $$->addChildNode($2);
                        }
                        | factor
                        {
                            $$ = $1;
                        }
                        ;

unaryOp                 : SUB
                        {
                            $$ = new Unary($1->tokenLineNumber, Unary::Type::CHSIGN);
                        }
                        | MUL
                        {
                            $$ = new Unary($1->tokenLineNumber, Unary::Type::SIZEOF);
                        }
                        | QUESTION
                        {
                            $$ = new Unary($1->tokenLineNumber, Unary::Type::QUESTION);
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
                            $$ = new Id($1->tokenLineNumber, $1->tokenInformation);
                        }
                        | ID LBRACK exp RBRACK
                        {
                            $$ = new Binary($1->tokenLineNumber, Binary::Type::INDEX);
                            Id *node = new Id($1->tokenLineNumber, $1->tokenInformation, true);
                            $$->addChildNode(node);
                            $$->addChildNode($3);
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
                            $$ = new Call($1->tokenLineNumber, $1->tokenInformation);
                            $$->addChildNode($3);
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
                            $$ = $1;
                            $$->addSiblingNode($3);
                        }
                        | exp
                        {
                            $$ = $1;
                        }
                        ;

constant                : NUMCONST
                        {
                            $$ = new Const($1->tokenLineNumber, Const::Type::INT, $1->tokenInformation);
                        }
                        | BOOLCONST
                        {
                            $$ = new Const($1->tokenLineNumber, Const::Type::BOOL, $1->tokenInformation);
                        }
                        | CHARCONST
                        {
                            $$ = new Const($1->tokenLineNumber, Const::Type::CHAR, $1->tokenInformation);
                        }
                        | STRINGCONST
                        {
                            $$ = new Const($1->tokenLineNumber, Const::Type::STRING, $1->tokenInformation);
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
    std::string fileName = compilerFlags.getFile();

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
    if(compilerFlags.getPrintASTFlag())
    {
        //if the root is null, throw an error
        if (root == nullptr)
        {
            throw std::runtime_error("main(): Cannot print root: nullptr");
        }

        //print the AST
        root->printAST();
    }

    //create the symbol table
    SymbolTable symbolTable = SymbolTable();

    //get symbol table debug flag
    symbolTable.debug(compilerFlags.getSymbolTableFlag());

    //create the semantics analyzer
    Semantics analyzer = Semantics(&symbolTable);
    
    //perform semantic analysis
    analyzer.analyze(root);

    //if the -D flag was passed, print the symbol table
    // if(compilerFlags.getSymbolTableFlag())
    // {
    //     //if the root is null, throw an error
    //     if (root == nullptr)
    //     {
    //         throw std::runtime_error("Cannot print root: nullptr");
    //     }

    // }

    //if the -P flag was passed, print the AST with types
    if(compilerFlags.getPrintASTWithTypesFlag())
    {
        //if the root is null, throw an error
        if (root == nullptr)
        {
            throw std::runtime_error("main(): Cannot print root: nullptr");
        }

        //print the AST with types
        root->printAST();
    }

    //code generation will eventually go here

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
