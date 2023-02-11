%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: parser.y
DESC: yacc parser for the calculator language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#include "scanType.hpp"  // TokenData Type
#include "CompilerFlags.hpp" // Compiler Flags
#include "ast/AST.hpp" // AST Node Types
#include <stdio.h>
#include <string>
#include <iostream>


// Variables for YACC
extern int yylex();
extern FILE *yyin;
extern int yydebug;

// Variables for ERR,from c-.l scanner
extern int lineNumber;         // ERR line number from the scanner!!
extern int numberOfErrors;    // ERR err count

Node *root; // AST root node

//ERROR Message Definition and Output Function
#define YYERROR_VERBOSE
void yyerror(const char *message)
{
    //Output the error message
    std::cout << "ERROR(" << lineNumber + 1 << "): " << message << std::endl;
    
    //increment the error count
    numberOfErrors++;
}

%}

// this is included in the tab.hpp file
// so scanType.hpp must be included before the tab.hpp file!!!!
%union 
{
    PrimitiveType::Type primitiveType;
    TokenData *tokenData;
    Node *node;
}

/* Primative Types */
%type <primitiveType> typeSpec

/* Token Data */
%token <tokenData> ID NUMCONST STRINGCONST CHARCONST BOOLCONST 
%token <tokenData> STATIC INT CHAR BOOL 
%token <tokenData> FOR WHILE BY DO 
%token <tokenData> IF ELSE THEN 
%token <tokenData> RETURN BREAK
%token <tokenData> AND OR 
%token <tokenData> INC DEC TO LEQ ASGN GEQ NEQ EQ
%token <tokenData> ADDASS SUBASS MULASS DIVASS 
%token <tokenData> LCURLY RCURLY LPAREN RPAREN LBRACK RBRACK 
%token <tokenData> SEMICOLON COLON QUESTION COMMA
%token <tokenData>  ADD SUB MUL DIV MOD NOT GT LT

/* AST Nodes */
%type <node> program declList decl varDecl scopedVarDecl varDeclList varDeclInit
%type <node> varDeclId funDecl parms parmList parmTypeList parmIdList parmId stmt
%type <node> stmtUnmatched stmtMatched expStmt compoundStmt localDecls stmtList
%type <node> selectStmtUnmatched selectStmtMatched iterStmtUnmatched iterStmtMatched iterRange
%type <node> returnStmt breakStmt exp assignop simpleExp andExp unaryRelExp relExp relOp sumExp
%type <node> sumOp mulExp mulOp unaryExp unaryOp factor mutable immutable call args argList constant


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
                            $$->addSibling($2);
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
                            VariableNode *node = (VariableNode *)$$;
                            node->setVariableType($1);
                        }
                        ;

scopedVarDecl           : STATIC typeSpec varDeclList SEMICOLON
                        {
                            $$ = $3;
                            VariableNode *node = (VariableNode *)$$;
                            node->setVariableType($2);
                            node->setStaticVariable();
                        }
                        | typeSpec varDeclList SEMICOLON
                        {
                            $$ = $2;
                            VariableNode *node = (VariableNode *)$$;
                            node->setVariableType($1);
                        }
                        ;

varDeclList             : varDeclList COMMA varDeclInit
                        {
                            $$ = $1;
                            $$->addSibling($3);
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
                            $$->addChild($3);
                        }
                        ;

varDeclId               : ID
                        {
                            $$ = new Var($1->tokenLineNum, new Primitive(Primitive::Type::Void), $1->tokenContent);
                        }
                        | ID LBRACK NUMCONST RBRACK
                        {
                            $$ = new Var($1->tokenLineNum, new Primitive(Primitive::Type::Void, true), $1->tokenContent);
                        }
                        ;

typeSpec                : INT
                        {
                            $$ = Primitive::Type::Int;
                        }
                        | BOOL
                        {
                            $$ = Primitive::Type::Bool;
                        }
                        | CHAR
                        {
                            $$ = Primitive::Type::Char;
                        }
                        ;

funDecl                 : typeSpec ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = new Func($2->tokenLineNum, new Primitive($1), $2->tokenContent);
                            $$->addChild($4);
                            $$->addChild($6);
                        }
                        | ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = new Func($1->tokenLineNum, new Primitive(Primitive::Type::Void), $1->tokenContent);
                            $$->addChild($3);
                            $$->addChild($5);
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
                            $$->addSibling($3);
                        }
                        | parmTypeList
                        {
                            $$ = $1;
                        }
                        ;

parmTypeList            : typeSpec parmIdList
                        {
                            $$ = $2;
                            Parm *node = (Parm *)$$;
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
                                $$->addSibling($3);
                            }
                        }
                        | parmId
                        {
                            $$ = $1;
                        }
                        ;

parmId                  : ID
                        {
                            $$ = new Parm($1->tokenLineNum, new Primitive(Primitive::Type::Void), $1->tokenContent);
                        }
                        | ID LBRACK RBRACK
                        {
                            $$ = new Parm($1->tokenLineNum, new Primitive(Primitive::Type::Void, true), $1->tokenContent);
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

compoundStmt            : LCURLY localDecls stmtList RCURLY
                        {
                            $$ = new Compound($1->tokenLineNum);
                            $$->addChild($2);
                            $$->addChild($3);
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
                                $$->addSibling($2);
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
                                $$->addSibling($2);
                            }
                        }
                        |
                        {
                            $$ = nullptr;
                        }
                        ;

selectStmtUnmatched     : IF simpleExp THEN stmt
                        {
                            $$ = new If($1->tokenLineNum);
                            $$->addChild($2);
                            $$->addChild($4);
                        }
                        | IF simpleExp THEN stmtMatched ELSE stmtUnmatched
                        {
                            $$ = new If($1->tokenLineNum);
                            $$->addChild($2);
                            $$->addChild($4);
                            $$->addChild($6);
                        }
                        ;

selectStmtMatched       : IF simpleExp THEN stmtMatched ELSE stmtMatched
                        {
                            $$ = new If($1->tokenLineNum);
                            $$->addChild($2);
                            $$->addChild($4);
                            $$->addChild($6);
                        }
                        ;

iterStmtUnmatched       : WHILE simpleExp DO stmtUnmatched
                        {
                            $$ = new While($1->tokenLineNum);
                            $$->addChild($2);
                            $$->addChild($4);
                        }
                        | FOR ID ASGN iterRange DO stmtUnmatched
                        {
                            $$ = new For($1->tokenLineNum);
                            Var *node = new Var($2->tokenLineNum, new Primitive(Primitive::Type::Int), $2->tokenContent);
                            $$->addChild(node);
                            $$->addChild($4);
                            $$->addChild($6);
                        }
                        ;

iterStmtMatched         : WHILE simpleExp DO stmtMatched
                        {
                            $$ = new While($1->tokenLineNum);
                            $$->addChild($2);
                            $$->addChild($4);
                        }
                        | FOR ID ASGN iterRange DO stmtMatched
                        {
                            $$ = new For($1->tokenLineNum);
                            Var *node = new Var($2->tokenLineNum, new Primitive(Primitive::Type::Int), $2->tokenContent);
                            $$->addChild(node);
                            $$->addChild($4);
                            $$->addChild($6);
                        }
                        ;

iterRange               : simpleExp TO simpleExp
                        {
                            $$ = new Range($1->getTokenLineNum());
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | simpleExp TO simpleExp BY simpleExp
                        {
                            $$ = new Range($1->getTokenLineNum());
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->addChild($5);
                        }
                        ;

returnStmt              : RETURN SEMICOLON
                        {
                            $$ = new Return($1->tokenLineNum);
                        }
                        | RETURN exp SEMICOLON
                        {
                            $$ = new Return($1->tokenLineNum);
                            $$->addChild($2);
                        }
                        ;

breakStmt               : BREAK SEMICOLON
                        {
                            $$ = new Break($1->tokenLineNum);
                        }
                        ;

exp                     : mutable assignop exp
                        {
                            $$ = $2;
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | mutable INC
                        {
                            $$ = new UnaryAsgn($1->getTokenLineNum(), UnaryAsgn::Type::Inc);
                            $$->addChild($1);
                        }
                        | mutable DEC
                        {
                            $$ = new UnaryAsgn($1->getTokenLineNum(), UnaryAsgn::Type::Dec);
                            $$->addChild($1);
                        }
                        | simpleExp
                        {
                            $$ = $1;
                        }
                        ;

assignop                : ASGN
                        {
                            $$ = new Asgn($1->tokenLineNum, Asgn::Type::Asgn);
                        }
                        | ADDASS
                        {
                            $$ = new Asgn($1->tokenLineNum, Asgn::Type::AddAsgn);
                        }
                        | SUBASS
                        {
                            $$ = new Asgn($1->tokenLineNum, Asgn::Type::SubAsgn);
                        }
                        | MULASS
                        {
                            $$ = new Asgn($1->tokenLineNum, Asgn::Type::MulAsgn);
                        }
                        | DIVASS
                        {
                            $$ = new Asgn($1->tokenLineNum, Asgn::Type::DivAsgn);
                        }
                        ;

simpleExp               : simpleExp OR andExp
                        {
                            $$ = new Binary($1->getTokenLineNum(), Binary::Type::Or);
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | andExp
                        {
                            $$ = $1;
                        }
                        ;

andExp                  : andExp AND unaryRelExp
                        {
                            $$ = new Binary($1->getTokenLineNum(), Binary::Type::And);
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | unaryRelExp
                        {
                            $$ = $1;
                        }
                        ;

unaryRelExp             : NOT unaryRelExp
                        {
                            $$ = new Unary($1->tokenLineNum, Unary::Type::Not);
                            $$->addChild($2);
                        }
                        | relExp
                        {
                            $$ = $1;
                        }
                        ;

relExp                  : sumExp relOp sumExp
                        {
                            $$ = $2;
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | sumExp
                        {
                            $$ = $1;
                        }
                        ;

relOp                   : LT
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::LT);
                        }
                        | LEQ
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::LEQ);
                        }
                        | GT
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::GT);
                        }
                        | GEQ
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::GEQ);
                        }
                        | EQ
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::EQ);
                        }
                        | NEQ
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::NEQ);
                        }
                        ;

sumExp                  : sumExp sumOp mulExp
                        {
                            $$ = $2;
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | mulExp
                        {
                            $$ = $1;
                        }
                        ;

sumOp                   : ADD
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::Add);
                        }
                        | SUB
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::Sub);
                        }
                        ;

mulExp                  : mulExp mulOp unaryExp
                        {
                            $$ = $2;
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                        | unaryExp
                        {
                            $$ = $1;
                        }
                        ;

mulOp                   : MUL
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::Mul);
                        }
                        | DIV
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::Div);
                        }
                        | MOD
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::Mod);
                        }
                        ;

unaryExp                : unaryOp unaryExp
                        {
                            $$ = $1;
                            $$->addChild($2);
                        }
                        | factor
                        {
                            $$ = $1;
                        }
                        ;

unaryOp                 : SUB
                        {
                            $$ = new Unary($1->tokenLineNum, Unary::Type::Chsign);
                        }
                        | MUL
                        {
                            $$ = new Unary($1->tokenLineNum, Unary::Type::Sizeof);
                        }
                        | QUESTION
                        {
                            $$ = new Unary($1->tokenLineNum, Unary::Type::Question);
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
                            $$ = new Id($1->tokenLineNum, $1->tokenContent);
                        }
                        | ID LBRACK exp RBRACK
                        {
                            $$ = new Binary($1->tokenLineNum, Binary::Type::Index);
                            Id *node = new Id($1->tokenLineNum, $1->tokenContent, true);
                            $$->addChild(node);
                            $$->addChild($3);
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
                            $$ = new Call($1->tokenLineNum, $1->tokenContent);
                            $$->addChild($3);
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
                            $$->addSibling($3);
                        }
                        | exp
                        {
                            $$ = $1;
                        }
                        ;

constant                : NUMCONST
                        {
                            $$ = new Const($1->tokenLineNum, Const::Type::Int, $1->tokenContent);
                        }
                        | BOOLCONST
                        {
                            $$ = new Const($1->tokenLineNum, Const::Type::Bool, $1->tokenContent);
                        }
                        | CHARCONST
                        {
                            $$ = new Const($1->tokenLineNum, Const::Type::Char, $1->tokenContent);
                        }
                        | STRINGCONST
                        {
                            $$ = new Const($1->tokenLineNum, Const::Type::String, $1->tokenContent);
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
    std::string fileName = compilerFlags.getFileName();

    //if the compiler flags object has an error, print the error and exit
    if (argc > 1) 
    {
        // if failed to open file
        if (!(yyin = fileName.c_str(), "r"))
        {
            //print error message
            std :: cout << "ERROR: failed to open \'" << fileName << "\'" << std :: endl;
            //exit with error
            exit(1);
        }
    }

    //parse the input
    yyparse();

    //if the the -p flag was passed, print the AST
    if(compilerFlags.getPrintFlag())
    {
        if(root != NULL)
        {
            root->printAST();
        }
    }

    //delete the tree root. Free the memory. 
    delete root;

    //close the file sent into the c- compiler
    fclose(yyin);


    //close the file and exit with success
    return 0;
}
