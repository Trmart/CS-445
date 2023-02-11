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
                            $$ = $1;
                            $$->addChildNode($3);
                        }
                        ;

varDeclId               : ID
                        {
                            $$ = new VariableNode($1->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::VOID), $1->tokenInformation);
                        }
                        | ID LBRACK NUMCONST RBRACK
                        {
                            $$ = new VariableNode($1->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::VOID, true), $1->tokenInformation);
                        }
                        ;

typeSpec                : INT
                        {
                            $$ = PrimitiveType::Type::INT;
                        }
                        | BOOL
                        {
                            $$ = PrimitiveType::Type::BOOL;
                        }
                        | CHAR
                        {
                            $$ = PrimitiveType::Type::CHAR;
                        }
                        ;

funDecl                 : typeSpec ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = new FunctionNode($2->tokenLineNumber, new PrimitiveType($1), $2->tokenInformation);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        | ID LPAREN parms RPAREN compoundStmt
                        {
                            $$ = new FunctionNode($1->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::Void), $1->tokenInformation);
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
                            ParameterNode *node = (ParameterNode *)$$;
                            node->setParameterType($1);
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
                            $$ = new ParameterNode($1->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::VOID), $1->tokenInformation);
                        }
                        | ID LBRACK RBRACK
                        {
                            $$ = new ParameterNode($1->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::VOID, true), $1->tokenInformation);
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
                            $$ = new CompoundNode($1->tokenLineNumber);
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
                            $$ = new IfNode($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                        }
                        | IF simpleExp THEN stmtMatched ELSE stmtUnmatched
                        {
                            $$ = new IfNode($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

selectStmtMatched       : IF simpleExp THEN stmtMatched ELSE stmtMatched
                        {
                            $$ = new IfNode($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

iterStmtUnmatched       : WHILE simpleExp DO stmtUnmatched
                        {
                            $$ = new WhileNode($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                        }
                        | FOR ID ASGN iterRange DO stmtUnmatched
                        {
                            $$ = new ForNode($1->tokenLineNumber);
                            VariableNode *node = new VariableNode($2->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::INT), $2->tokenInformation);
                            $$->addChildNode(node);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

iterStmtMatched         : WHILE simpleExp DO stmtMatched
                        {
                            $$ = new WhileNode($1->tokenLineNumber);
                            $$->addChildNode($2);
                            $$->addChildNode($4);
                        }
                        | FOR ID ASGN iterRange DO stmtMatched
                        {
                            $$ = new ForNode($1->tokenLineNumber);
                            VariableNode *node = new VariableNode($2->tokenLineNumber, new PrimitiveType(PrimitiveType::Type::INT), $2->tokenInformation);
                            $$->addChildNode(node);
                            $$->addChildNode($4);
                            $$->addChildNode($6);
                        }
                        ;

iterRange               : simpleExp TO simpleExp
                        {
                            $$ = new RangeNode($1->getTokenLineNumber());
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                        }
                        | simpleExp TO simpleExp BY simpleExp
                        {
                            $$ = new RangeNode($1->getTokenLineNumber());
                            $$->addChildNode($1);
                            $$->addChildNode($3);
                            $$->addChildNode($5);
                        }
                        ;

returnStmt              : RETURN SEMICOLON
                        {
                            $$ = new ReturnNode($1->tokenLineNumber);
                        }
                        | RETURN exp SEMICOLON
                        {
                            $$ = new ReturnNode($1->tokenLineNumber);
                            $$->addChildNode($2);
                        }
                        ;

breakStmt               : BREAK SEMICOLON
                        {
                            $$ = new BreakNode($1->tokenLineNumber);
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
                            $$ = new UnaryAssignmentNode($1->getTokenLineNumber(), UnaryAssignmentNode::Type::INC);
                            $$->addChildNode($1);
                        }
                        | mutable DEC
                        {
                            $$ = new UnaryAssignmentNode($1->getTokenLineNumber(), UnaryAssignmentNode::Type::DEC);
                            $$->addChildNode($1);
                        }
                        | simpleExp
                        {
                            $$ = $1;
                        }
                        ;

assignop                : ASGN
                        {
                            $$ = new AssignmentNode($1->tokenLineNumber, AssignmentNode::Type::ASGN);
                        }
                        | ADDASS
                        {
                            $$ = new AssignmentNode($1->tokenLineNumber, AssignmentNode::Type::ADDASS);
                        }
                        | SUBASS
                        {
                            $$ = new AssignmentNode($1->tokenLineNumber, AssignmentNode::Type::SUBASS);
                        }
                        | MULASS
                        {
                            $$ = new AssignmentNode($1->tokenLineNumber, AssignmentNode::Type::MULASS);
                        }
                        | DIVASS
                        {
                            $$ = new AssignmentNode($1->tokenLineNumber, AssignmentNode::Type::DIVASS);
                        }
                        ;

simpleExp               : simpleExp OR andExp
                        {
                            $$ = new BinaryNode($1->getTokenLineNumber(), BinaryNode::Type::OR);
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
                            $$ = new BinaryNode($1->getTokenLineNumber(), BinaryNode::Type::AND);
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
                            $$ = new UnaryNode($1->tokenLineNumber, UnaryNode::Type::NOT);
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
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::LT);
                        }
                        | LEQ
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::LEQ);
                        }
                        | GT
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::GT);
                        }
                        | GEQ
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::GEQ);
                        }
                        | EQ
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::EQ);
                        }
                        | NEQ
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::NEQ);
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
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::ADD);
                        }
                        | SUB
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::SUB);
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
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::MUL);
                        }
                        | DIV
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::DIV);
                        }
                        | MOD
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::MOD);
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
                            $$ = new UnaryNode($1->tokenLineNumber, UnUnaryNodeary::Type::CHSIGN);
                        }
                        | MUL
                        {
                            $$ = new UnaryNode($1->tokenLineNumber, UnaryNode::Type::SIZEOF);
                        }
                        | QUESTION
                        {
                            $$ = new UnaryNode($1->tokenLineNumber, UnaryNode::Type::QUESTION);
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
                            $$ = new IdentifierNode($1->tokenLineNumber, $1->tokenInformation);
                        }
                        | ID LBRACK exp RBRACK
                        {
                            $$ = new BinaryNode($1->tokenLineNumber, BinaryNode::Type::INDEX);
                            IdentifierNode *node = new IdentifierNode($1->tokenLineNumber, $1->tokenInformation, true);
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
                            $$ = new CallNode($1->tokenLineNumber, $1->tokenInformation);
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
                            $$ = new ConstantNode($1->tokenLineNumber, ConstantNode::Type::INT, $1->tokenInformation);
                        }
                        | BOOLCONST
                        {
                            $$ = new ConstantNode($1->tokenLineNumber, ConstantNode::Type::BOOL, $1->tokenInformation);
                        }
                        | CHARCONST
                        {
                            $$ = new ConstantNode($1->tokenLineNumber, ConstantNode::Type::CHAR, $1->tokenInformation);
                        }
                        | STRINGCONST
                        {
                            $$ = new ConstantNode($1->tokenLineNumber, ConstantNode::Type::STRING, $1->tokenInformation);
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
