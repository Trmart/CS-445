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
    Primitive::Type primitiveType;
    TokenData *tokenData;
    Node *node;
}

%type <primitiveType> typeSpec
%token <tokenData> ID NUMCONST STRINGCONST CHARCONST BOOLCONST TOKEN KEYWORD
%token <tokenData> STATIC INT CHAR BOOL 
%token <tokenData> FOR WHILE BY DO 
%token <tokenData> IF ELSE THEN BEGIN END STEP 
%token <tokenData> RETURN BREAK
%token <tokenData> AND OR TRUE FALSE
%token <tokenData> INC DEC TO LEQ ASGN GEQ NEQ ADDASS
%token <tokenData> LCURLY RCURLY LPAREN RPAREN LBRACKET RBRACKET 
%token <tokenData> SEMICOLON COLON QUESTION COMMA
%token <tokenData> ASSIGN ADD SUB MUL DIV MOD NOT


%type <node> program declList decl varDecl scopedVarDecl varDeclList varDeclInit
%type <node> varDeclId funDecl parms parmList parmTypeList parmIdList parmId stmt
%type <node> stmtUnmatched stmtMatched expStmt compoundStmt localDecls stmtList
%type <node> selectStmtUnmatched selectStmtMatched iterStmtUnmatched iterStmtMatched iterRange
%type <node> returnStmt breakStmt exp assignop simpleExp andExp unaryRelExp relExp relOp sumExp
%type <node> sumOp mulExp mulOp unaryExp unaryOp factor mutable immutable call args argList constant


%%
program : declList
    {

    };
declList : declList decl
    {

    }
    | decl
    {

    }
    ;
decl : varDecl
    {

    }
    | funDecl
    {

    }
    ;
varDecl : typeSpec varDeclList SEMICOLON
    {

    }
    ;
scopedVarDecl : STATIC typeSpec varDeclList SEMICOLON
    {

    }
    ;
varDeclList : varDeclList COMMA varDeclInit
    {

    }
    | varDeclInit
    {

    }
    ;
varDeclInit : varDeclId
    {

    }
    | varDeclId COLON simpleExp
    {

    }
    ;
varDeclId : ID
    {

    }
    | ID LBRACKET NUMCONST RBRACKET
    {

    }
    ;

typeSpec : STATIC
    {

    }
    | INT
    {

    }
    | CHAR
    {

    }
    | BOOL
    {

    }
    ;
funDecl : typeSpec ID LPAREN parms RPAREN compoundStmt
    {
        
    }
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
