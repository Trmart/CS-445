%{

/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: parser.y
DESC: Holds the grammar for the c- language. 
*/

#include "scanType.h"  
#include "tree.h"
#include "semantic.h"
#include "IOinit.h"

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

static TreeNode *ROOT;

extern SymbolTable symbolTable;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
  std::cout << "ERROR(" << line << "): " << msg << std::endl;
  numErrors++;
}

%}


%union 
{
  ExpType type;           
  TokenData *tokenData; 
  TreeNode *tree;        
}

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST 
%token <tokenData> ASGN ADDASGN SUBASS INC DEC GEQ LEQ NEQ MULASS DIVASS 
%token <tokenData> INT IF OR NOT BY ELSE THEN FOR BREAK RETURN BOOL CHAR STATIC AND 
%token <tokenData> BEGN FINISH DO WHILE TO BOOLCONST
%token <tokenData> QUESTION LESS GREAT PLUS EQUAL MULT DIV MOD COMMA OBRACKET CBRACKET 
%token <tokenData> MINUS COLON SEMICOLON OPAREN CPAREN 

%type <tree> declarationList declaration funDeclaration varDeclaration scopedtypespecificer vardeclarationList
%type <type> typespec
%type <tree> varDeclarationInit varDeclarationId  parameters parameterList parameterTypeList
%type <tree> parameterIdList parameterId statement matched unmatched statementEnd expstatement compoundstatement 
%type <tree> localdeclaration statementList iterRange returnstatement breakstatement exp asgnop
%type <tree> simpleExp andExp unaryRelExp relExp operator sumExp sumop mulExp mulop
%type <tree> unaryExp unaryop factor mutable immutable call args argList constant

%%
// note program isn't declared, its a bison cmd. 
// Pass root as treenode, declarationlist to be read last.
program       : declarationList                                  { ROOT = $1;}
              ;

declarationList
              : declarationList declaration                      { $$ = addSibling($1, $2); }
              | declaration                                      { $$ = $1; }
              ;

declaration   : funDeclaration                                   { $$ = $1; }
              | varDeclaration                                   { $$ = $1; }
              ;

varDeclaration
              : typespec vardeclarationList SEMICOLON         { $$ = $2; setType($$, $1); }
              ;

scopedtypespecificer 
              : STATIC typespec vardeclarationList SEMICOLON   { $$ = $3; 
                                                                   $$->isStatic = true; 
                                                                   setType($$, $2);
                                                                  }

              | typespec vardeclarationList SEMICOLON          { $$ = $2; setType($$, $1);}
              ;

vardeclarationList   
              : vardeclarationList COMMA varDeclarationInit      { $$ = addSibling($1, $3);}
              | varDeclarationInit                               { $$ = $1; }
              ;

varDeclarationInit   
              : varDeclarationId                                 { $$ = $1; }
              | varDeclarationId COLON simpleExp                 { $$ = $1; $1->child[0] = $3;}
              ;

varDeclarationId     
              : ID                                               { $$ = newDeclNode(VarK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
                                                                 
              | ID OBRACKET NUMCONST CBRACKET                    { $$ = newDeclNode(VarK, $1);       
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->isArray = true;
                                                                   $$->thisTokenData = $1; 
                                                                   $$->expType = UndefinedType;
                                                                 }
              ;
//make sure to add typespecifiers for the parameters/etc!
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
              ;

parameters    : parameterList                                    { $$ = $1; }
              | %empty                                           { $$ = NULL; }
              ;


parameterList     
              : parameterList SEMICOLON parameterTypeList        { $$ = addSibling($1, $3); }
              | parameterTypeList                                { $$ = $1; }
              ;

parameterTypeList 
              : typespec parameterIdList                      { $$ = $2; setType($$, $1); }
              ;

parameterIdList   
              : parameterIdList COMMA parameterId                { $$ = addSibling($1, $3); }
              | parameterId                                      { $$ = $1; }
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
//Dangling else statement fix using matching/unmatching. 
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
              | FOR ID LEQ iterRange DO matched                  { $$ = newStmtNode(ForK, $1);
                                                                   $$->child[0] = newDeclNode(VarK, $2);
                                                                   $$->child[0]->expType = Integer;
                                                                   $$->attr.name = $3->tokenstr;
                                                                   $$->child[1] = $4;
                                                                   $$->child[2] = $6;
                                                                   
                                                                 }                                                    
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

              ;

expstatement  : exp SEMICOLON                                    { $$ = $1; }
              | SEMICOLON                                        { $$ = NULL; }
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
              ;

returnstatement    
              : RETURN SEMICOLON                                 { $$ = newStmtNode(ReturnK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              | RETURN exp SEMICOLON                             { $$ = newStmtNode(ReturnK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = $2->expType;
                                                                 }
              ;

breakstatement    
              : BREAK SEMICOLON                                  { $$ = newStmtNode(BreakK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              ;
//adding in lessequals, etc. 
asgnop        : ASGN                                             { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   //$$->expType = Integer;
                                                                 }
              | ADDASGN                                          { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   //$$->expType = Integer;
                                                                 }
              | SUBASS                                           { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   //$$->expType = Integer;
                                                                 }
              | MULASS                                           { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   //$$->expType = Integer;
                                                                 }
              | DIVASS                                           { $$ = newExpNode(AssignK, $1);
                                                                   $$->attr.name = $1->tokenstr;
                                                                   //$$->expType = Integer;
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

              ;

simpleExp     : simpleExp OR andExp                              { $$ = newExpNode(OpK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | andExp                                           { $$ = $1; }
             
              ;

andExp        : andExp AND unaryRelExp                           { $$ = newExpNode(OpK, $2);
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                   $$->attr.name = $2->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | unaryRelExp                                      { $$ = $1; }
              ;

relExp        : sumExp operator sumExp                              { $$ = $2; 
                                                                   $$->child[0] = $1;
                                                                   $$->child[1] = $3;
                                                                 }
              | sumExp                                           { $$ = $1; }
              ;

unaryRelExp   : NOT unaryRelExp                                  { $$ = newExpNode(OpK, $1);
                                                                   $$->child[0] = $2;
                                                                   $$->attr.name = $1->tokenstr;
                                                                   $$->expType = Boolean;
                                                                 }
              | relExp                                           { $$ = $1; }
              ;
//add in my basic operators. 
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

immutable     : OPAREN exp CPAREN                                { $$ = $2; }
              | call                                             { $$ = $1; }
              | constant                                         { $$ = $1; }
              ;

factor        : mutable                                          { $$ = $1; }
              | immutable                                        { $$ = $1; }
              ;


call          : ID OPAREN args CPAREN                            { $$ = newExpNode(CallK, $1);
                                                                   $$->child[0] = $3;
                                                                   $$->attr.name = $1->tokenstr;
                                                                 }
              ;

args          : argList                                          { $$ = $1; }
              | %empty                                           { $$ = NULL; }
              ;

argList       : argList COMMA exp                                { $$ = addSibling($1, $3); }
              | exp                                              { $$ = $1; }

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
                                                                 }
              ;                                                             
%%

extern int yydebug;
int main(int argc, char *argv[])
{
  int compilerFlag = 0;
  bool printAST = 0;
  numErrors = 0;
  numWarnings = 0;

  while((compilerFlag = getopt(argc, argv, "dDpPh")) != -1)
  {

    switch(compilerFlag)
    {

        case 'p':
            {
              printAST = true;
              isPrintingTreeTypes = false;
            }
            break;
    
        case 'P':
              {
                printAST = true;
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

        case 'h':
              {
                std::cout << "usage: c- [options] [sourcefile]" << std::endl;
                std::cout << "options:" << std::endl;
                std::cout << "-d     - turn on parser debugging" << std::endl;
                std::cout << "-D     - turn on symbol table debugging" << std::endl;
                std::cout << "-h     - print this usage message" << std::endl;
                std::cout << "-p     - print the abstract syntax tree" << std::endl;
                std::cout << "-P     - print the abstract syntax tree plus type information" << std::endl;
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

  yyparse();

  if(printAST && !isPrintingTreeTypes)
  {
    printTree(ROOT, 0, isPrintingTreeTypes);
  }
  else if(printAST && isPrintingTreeTypes)
  {
    setupIO();
    semanticAnalysis(ROOT, numErrors, numWarnings);

    if(numErrors < 1)
    {  
      printTree(ROOT, 0, isPrintingTreeTypes);
    }
  }

  std::cout << "Number of warnings: " << numWarnings << std::endl;
  std::cout << "Number of errors: " << numErrors << std::endl;

  return 0;
}