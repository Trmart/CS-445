%{

/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW6
Dr. Wilder
DUE: 4/16/2023

FILE: parser.y
DESC: Holds the grammar for the c- language. 
*/

#include "scanType.h"  
#include "AST.h"
#include "semantic.h"
#include "IOinit.h"
#include "yyerror.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>  
#include <getopt.h>
#include <iostream>
#include <string>

extern int yylex();
extern FILE *yyin;
extern int line;       
extern int numErrors;  
int numWarnings;       
bool isPrintingTreeTypes = false;

//memeory information
bool isPrintingMemoryOffset = false;
bool isPrintingMemorySize = false;
extern int globalOffset;


static TreeNode* ROOT;

extern SymbolTable symbolTable;

// #define YYERROR_VERBOSE

%}

%define parse.error verbose
%union 
{
  ExpType type;           
  TokenData* tokenData; 
  TreeNode* node;        
}

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST 
%token <tokenData> ASGN ADDASGN SUBASS INC DEC GEQ LEQ NEQ MULASS DIVASS 
%token <tokenData> INT IF OR NOT BY ELSE THEN FOR BREAK RETURN BOOL CHAR STATIC AND 
%token <tokenData> BEGN FINISH DO WHILE TO BOOLCONST
%token <tokenData> QUESTION LESS GREAT PLUS EQUAL MULT DIV MOD COMMA OBRACKET CBRACKET 
%token <tokenData> MINUS COLON SEMICOLON OPAREN CPAREN 

%type <type> typespec

%type <node> declarationList declaration funDeclaration varDeclaration scopedtypespecificer vardeclarationList
%type <node> varDeclarationInit varDeclarationId  parameters parameterList parameterTypeList
%type <node> parameterIdList parameterId statement matched unmatched statementEnd expstatement compoundstatement 
%type <node> localdeclaration statementList iterRange returnstatement breakstatement exp asgnop
%type <node> simpleExp andExp unaryRelExp relExp operator sumExp sumop mulExp mulop
%type <node> unaryExp unaryop factor mutable immutable call args argList constant

%%

program       : declarationList                                  { ROOT = $1;}
              ;

declarationList
              : declarationList declaration                      { $$ = addSibling($1, $2); }
              | declaration                                      { $$ = $1; }
              ;

declaration   : funDeclaration                                   { $$ = $1; }
              | varDeclaration                                   { $$ = $1; }
              | error                                            { $$ = NULL; }
              ;

varDeclaration
              : typespec vardeclarationList SEMICOLON         { $$ = $2; setType($$, $1); yyerrok;}
              | error vardeclarationList SEMICOLON            { $$ = NULL; yyerrok;}
              | typespec error SEMICOLON                      { $$ = NULL; yyerrok;}
              ;

scopedtypespecificer 
              : STATIC typespec vardeclarationList SEMICOLON    {   
                                                                  $$ = $3; 
                                                                  $$->isStatic = true; 
                                                                  setType($$, $2);
                                                                  yyerrok;
                                                                }

              | typespec vardeclarationList SEMICOLON          { $$ = $2; setType($$, $1); yyerrok;}
              ;

vardeclarationList   
              : vardeclarationList COMMA varDeclarationInit      { $$ = addSibling($1, $3); yyerrok;}
              | vardeclarationList COMMA error                  { $$ = NULL;}
              | varDeclarationInit                               { $$ = $1; }
              | error                                            { $$ = NULL;}
              ;

varDeclarationInit   
              : varDeclarationId                                 { $$ = $1; }
              | varDeclarationId COLON simpleExp                 { $$ = $1; $1->child[0] = $3;}
              | error COLON simpleExp                            { $$ = NULL; yyerrok;}
              ;

varDeclarationId     
              : ID                                               { $$ = newDeclNode(VarK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
                                                                 
              | ID OBRACKET NUMCONST CBRACKET                    { $$ = newDeclNode(VarK, $1);       
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->isArray = true;
                                                                   $$->arraySize = $3->nvalue;
                                                                   $$->thisTokenData = $1; 
                                                                   $$->expType = UndefinedType;
                                                                 }
              | ID OBRACKET error                              { $$ = NULL;}
              | error CBRACKET                                  { $$ = NULL; yyerrok;}
              ;

typespec    : INT                                             { $$ = Integer; }
              | CHAR                                             { $$ = Char; }
              | BOOL                                             { $$ = Boolean;}
                                                                   
              ;


funDeclaration       
              : typespec ID OPAREN parameters 
                CPAREN compoundstatement
                                                                 { $$ = newDeclNode(FuncK, $2);     
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->child[0] = $4;
                                                                   $$->child[1] = $6;
                                                                   $$->expType = $1;
                                                                 }
                                                                 
              | ID OPAREN parameters CPAREN compoundstatement    { $$ = newDeclNode(FuncK, $1);   
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->child[0] = $3;
                                                                   $$->child[1] = $5;
                                                                 }
              | typespec error                                   { $$ = NULL;}
              | typespec ID OPAREN error                         { $$ = NULL;}
              | ID OPAREN error                                  { $$ = NULL;}
              | ID OPAREN parameters CPAREN error                { $$ = NULL;}
              ;

parameters    : parameterList                                    { $$ = $1; }
              | %empty                                           { $$ = NULL; }
              ;


parameterList     
              : parameterList SEMICOLON parameterTypeList        { $$ = addSibling($1, $3); }
              | parameterTypeList                                { $$ = $1; }
              | parameterList SEMICOLON error                    { $$ = NULL;}
              | error                                            { $$ = NULL;}
              ;

parameterTypeList 
              : typespec parameterIdList                      { $$ = $2; setType($$, $1); }
              | typespec error                                { $$ = NULL;}
              ;

parameterIdList   
              : parameterIdList COMMA parameterId                { $$ = addSibling($1, $3); yyerrok; }
              | parameterId                                      { $$ = $1; }
              | parameterIdList COMMA error                      { $$ = NULL;}
              | error                                            { $$ = NULL;}
              ;

parameterId   : ID                                               { $$ = newDeclNode(ParamK, $1);
                                                                   $$->attr.name = $1->tokenstr; 
                                                                 }
              | ID OBRACKET CBRACKET                             { $$ = newDeclNode(ParamK, $1);
                                                                   $$->isArray = true;
                                                                   $$->attr.name = $1->tokenstr; 
                                                                 }
              ;

statement     : matched                                          { $$ = $1; }   
              | unmatched                                        { $$ = $1; }
              ;

matched       : statementEnd                                     { $$ = $1; }
              | IF simpleExp THEN matched ELSE matched           { $$ = newStmtNode(IfK, $1); 
                                                                   $$->child[0] = $2;
                                                                   $$->child[1] = $4;
                                                                   $$->child[2] = $6;
                                                                 } 
              | WHILE simpleExp DO matched                       { $$ = newStmtNode(WhileK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->child[1] = $4;
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              | FOR ID ASGN iterRange DO matched                 { $$ = newStmtNode(ForK, $1);
                                                                   $$->child[0] = newDeclNode(VarK, $2);
                                                                   $$->child[0]->expType = Integer;
                                                                   $$->attr.name = $3->tokenstr;
                                                                   $$->child[1] = $4;
                                                                   $$->child[2] = $6;
                                                                   
                                                                 }                                                   
            | IF error                                          { $$ = NULL;}
            | IF error ELSE matched                             { $$ = NULL; yyerrok;}
            | IF error THEN matched ELSE matched                { $$ = NULL; yyerrok;}
            | WHILE error DO matched                            { $$ = NULL; yyerrok;}
            | WHILE error                                       { $$ = NULL;}
            | FOR ID ASGN error DO matched                      { $$ = NULL; yyerrok;}
            | FOR error                                         { $$ = NULL; }
              ;

unmatched     : IF simpleExp THEN matched ELSE unmatched         { $$ = newStmtNode(IfK, $1); 
                                                                   $$->child[0] = $2;
                                                                   $$->child[1] = $4;
                                                                   $$->child[2] = $6; 
                                                                 } 
              | IF simpleExp THEN statement                      { $$ = newStmtNode(IfK, $1);              
                                                                   $$->child[0] = $2;
                                                                   $$->child[1] = $4; 
                                                                 }                                                                 
              | WHILE simpleExp DO unmatched                     { $$ = newStmtNode(WhileK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->child[1] = $4;
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              | FOR ID ASGN iterRange DO unmatched               { $$ = newStmtNode(ForK, $1);
                                                                   $$->child[0] = newDeclNode(VarK, $2);
                                                                   $$->child[0]->expType = Integer;
                                                                   $$->attr.name = $3->tokenstr;
                                                                   $$->child[1] = $4;
                                                                   $$->child[2] = $6;
                                                                   
                                                                 }
              | IF error THEN statement                          { $$ = NULL; yyerrok;} 
              | IF error THEN matched ELSE unmatched             { $$ = NULL; yyerrok;} 
              ;

expstatement  : exp SEMICOLON                                    { $$ = $1; }
              | SEMICOLON                                        { $$ = NULL; }
              | error SEMICOLON                                  { $$ = NULL; yyerrok;}
              ;

statementEnd  : expstatement                                     { $$ = $1; }
              | compoundstatement                                { $$ = $1; }
              | breakstatement                                   { $$ = $1; }
              | returnstatement                                  { $$ = $1; }

              ;

compoundstatement  
              : BEGN localdeclaration statementList FINISH       { $$ = newStmtNode(CompoundK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->child[1] = $3;
                                                                   yyerrok;
                                                                 }
              ;

localdeclaration    
              : localdeclaration scopedtypespecificer         { $$ = addSibling($1, $2); }
              | %empty                                           { $$ = NULL; }
              ;

statementList : statementList statement                          { $$ = addSibling($1, $2); }
              | %empty                                           { $$ = NULL; }
              ;

iterRange     : simpleExp TO simpleExp                           { $$ = newStmtNode(RangeK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                 }
              | simpleExp TO simpleExp BY simpleExp              { $$ = newStmtNode(RangeK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                   $$->child[2] = $5;
                                                                 }
              | simpleExp TO error                              { $$ = NULL;}
              | error BY error                                  { $$ = NULL; yyerrok;}
              | simpleExp TO simpleExp BY error                 { $$ = NULL;}

returnstatement    
              : RETURN SEMICOLON                                 { $$ = newStmtNode(ReturnK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              | RETURN exp SEMICOLON                             { $$ = newStmtNode(ReturnK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = $2->expType;
                                                                   yyerrok;
                                                                 }
              | RETURN error SEMICOLON                           { $$ = NULL; yyerrok;}
              ;

breakstatement    
              : BREAK SEMICOLON                                  { $$ = newStmtNode(BreakK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              ;

asgnop        : ASGN                                             { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   
                                                                 }
              | ADDASGN                                          { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   
                                                                 }
              | SUBASS                                           { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   
                                                                 }
              | MULASS                                           { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   
                                                                 }
              | DIVASS                                           { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   
                                                                 }
              ;

exp           : mutable asgnop exp                               { $$ = $2; 
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                 }

              | simpleExp                                        { $$ = $1; }

              | mutable INC                                      { $$ = newExpNode(AssignK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | mutable DEC                                      { $$ = newExpNode(AssignK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | error asgnop exp                                 { $$ = NULL; yyerrok;}
              | mutable asgnop error                             { $$ = NULL;}
              | error INC                                        { $$ = NULL; yyerrok;}
              | error DEC                                        { $$ = NULL; yyerrok;}
              ;

simpleExp     : simpleExp OR andExp                              { $$ = newExpNode(OpK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | andExp                                           { $$ = $1; }
              | simpleExp OR error                               { $$ = NULL;}
              ;

andExp        : andExp AND unaryRelExp                           { $$ = newExpNode(OpK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | unaryRelExp                                      { $$ = $1; }
              | andExp AND error                                 { $$ = NULL;}
              ;

relExp        : sumExp operator sumExp                              { $$ = $2; 
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                 }
              | sumExp operator error                            { $$ = NULL;}
              | sumExp                                           { $$ = $1; }
              ;

unaryRelExp   : NOT unaryRelExp                                  { $$ = newExpNode(OpK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | relExp                                           { $$ = $1; }
              | NOT error                                       { $$ = NULL;}
              ;

operator      : GREAT                                            { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | GEQ                                              { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }

              | LESS                                             { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | LEQ                                              { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }

              | EQUAL                                            { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | NEQ                                              { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              ;

sumExp        : sumExp sumop mulExp                              { $$ = $2; 
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                 }
              | mulExp                                           { $$ = $1; }
              | sumExp sumop error                               { $$ = NULL;}
              ;

sumop         : PLUS                                             { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | MINUS                                            { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              ;

mulExp        : mulExp mulop unaryExp                            { $$ = $2; 
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                 }
              | unaryExp                                         { $$ = $1; }
              | mulExp mulop error                               { $$ = NULL;}
              ;

mulop         : MULT                                             { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | DIV                                              { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | MOD                                              { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              ;

unaryExp      : unaryop unaryExp                                 { $$ = $1; 
                                                                   $$->child[0] = $2;
                                                                 }
              | factor                                           { $$ = $1; }
              | unaryop error                                    { $$ = NULL;}
              ;

unaryop       : MINUS                                            { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | MULT                                             { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              | QUESTION                                         { $$ = newExpNode(OpK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Integer;
                                                                 }
              ;

mutable       : ID                                               { $$ = newExpNode(IdK, $1);
                                                                   $$->attr.name = $1->tokenstr;    
                                                                 }
              | ID OBRACKET exp CBRACKET                         { $$ = newExpNode(OpK, $2);  
                                                                  $$->child[0] = newExpNode(IdK, $1);
                                                                  $$->child[0]->attr.name = $1->tokenstr;
                                                                  $$->child[0]->isArray = true;
                                                                  $$->child[1] = $3; 
                                                                  $$->attr.name = $2->tokenstr;
                                                                 }
              ;

immutable     : OPAREN exp CPAREN                                { $$ = $2; yyerrok; }
              | call                                             { $$ = $1; }
              | constant                                         { $$ = $1; }
              | OPAREN error                                     { $$ = NULL;}
              ;

factor        : mutable                                          { $$ = $1; }
              | immutable                                        { $$ = $1; }
              ;


call          : ID OPAREN args CPAREN                            { $$ = newExpNode(CallK, $1);
                                                                   $$->child[0] = $3;
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              | error OPAREN                                   { $$ = NULL; yyerrok; }
              ;

args          : argList                                          { $$ = $1; }
              | %empty                                           { $$ = NULL; }
              ;

argList       : argList COMMA exp                                { $$ = addSibling($1, $3); yyerrok; }
              | exp                                              { $$ = $1; }
              | argList COMMA error                              { $$ = NULL;}

constant      : NUMCONST                                         { $$ = newExpNode(ConstantK, $1);
                                                                   $$->attr.value = $1->nvalue; 
                                                                   $$->expType = Integer;
                                                                 }
              | CHARCONST                                        { $$ = newExpNode(ConstantK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->thisTokenData = $1; 
                                                                   $$->expType = Char;
                                                                 }
              | BOOLCONST                                        { $$ = newExpNode(ConstantK, $1);
                                                                   $$->attr.value = $1->nvalue; 
                                                                   $$->expType = Boolean;
                                                                   $$->attr.name = $1->tokenstr;
                                                                   
                                                                 }
              | STRINGCONST                                      { $$ = newExpNode(ConstantK, $1);
                                                                   $$->attr.string = $1->stringvalue;
                                                                   $$->isArray = true;
                                                                   $$->expType = CharInt;
                                                                   $$->arraySize = $1->strlength;
                                                                 }
              ;                                                             
%%

extern int yydebug;
int main(int argc, char *argv[])
{
  int compilerFlag = 0;
  bool isPrintingAST = 0;
  numErrors = 0;
  numWarnings = 0;

  while((compilerFlag = getopt(argc, argv, "dDpPhM")) != -1)
  {

    switch(compilerFlag)
    {

        case 'p':
            {
              isPrintingAST = true;
              isPrintingTreeTypes = false;
            }
            break;
    
        case 'P':
              {
                isPrintingAST = true;
                isPrintingTreeTypes = true;
              }
              break;

        case 'd':
              {
                yydebug = 1;
              }
              break;           
        
        case 'D':
              {
                symbolTable.debug(1);
              }  
              break;

        case 'M':
              {
                isPrintingAST = true;
                isPrintingTreeTypes = true;
                isPrintingMemoryOffset = true;
                isPrintingMemorySize = true;
              }
              break; 

        case 'h':
              {
                std::cout << "usage: c- [options] [sourcefile]" << std::endl;
                std::cout << "options:" << std::endl;
                std::cout << "-d     - turn on parser debugging" << std::endl;
                std::cout << "-D     - turn on symbol table debugging" << std::endl;
                std::cout << "-h     - print this usage message" << std::endl;
                std::cout << "-p     - print the abstract syntax tree" << std::endl;
                std::cout << "-P     - print the abstract syntax tree plus type information" << std::endl;
                std::cout << "-M     - print the abstract syntax tree plus type information and memory offsets" << std::endl;
              }
              break;

        default:
              {
                exit(1);
              }
    }
  }
  
  std::string fileName = argv[argc-1];
  
  if(argc >1 && !(yyin = fopen(fileName.c_str(), "r")))
  {
    // failed to open file
    std::cout << "ERROR(ARGLIST): source file \"" << argv[1] << "\" could not be opened." << std::endl;
    numErrors++;
    std::cout << "Number of warnings: " << numWarnings << std::endl;
    std::cout << "Number of errors: " << numErrors << std::endl;
    exit(1);
  }

  initErrorProcessing(); 

  // remove line 623 before submission. Just For testing
  /* std::cout << "====================================" << std::endl; */

  yyparse();

  if(isPrintingAST && !isPrintingTreeTypes && numErrors == 0 && ROOT != NULL)
  {
    printAST(ROOT, 0, isPrintingTreeTypes);
  }
  else if(isPrintingAST && isPrintingTreeTypes && numErrors == 0 && ROOT != NULL)
  {
    initializeIO();
    
    semanticAnalysis(ROOT, numErrors, numWarnings);

    if(numErrors < 1)
    {  
      printAST(ROOT, 0, isPrintingTreeTypes);

      if(isPrintingMemoryOffset)
      {
        // print memory offsets
        std:: cout << "Offset for end of global space: " << globalOffset << std::endl;
      }
    }
  }
  
  // remove line 644 before submission. Just For testing
  /* std::cout << "FILE: " << fileName.substr(fileName.find_last_of("/\\") + 1) << std::endl; */
  
  std::cout << "Number of warnings: " << numWarnings << std::endl;
  std::cout << "Number of errors: " << numErrors << std::endl;

  return 0;
}