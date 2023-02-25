%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/26/2023

FILE: parser.l
DESC: scanner for the c- language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

// The order of includes is mandatory
#include "CompilerFlags.hpp"
#include "scanType.hpp"
#include "AST/AST.hpp"

#include <string>
#include <iostream>

#include "parser.tab.h"

int lineCount = 1;
int errorCount;

static int setValue(unsigned tokenLineNum, int tokenClass, char *sValue)
{
    // Create the pass-back data space
    yylval.tokenData = new TokenData;

    // Fill it up
    yylval.tokenData->tokenLineNumber = tokenLineNum;
    yylval.tokenData->tokenInformation = std::string(sValue);

    return tokenClass;
}

%}

%option noyywrap

%%

\#\#.*\n                    { lineCount++; }                 // Ignore comments
[ \t]                       { }                 // Ignore whitespace
"\n"                        { lineCount++; }    // Newlines

"int"                       { return INT; }
"bool"                      { return BOOL; }
"char"                      { return CHAR; }
"static"                    { return setValue(lineCount, STATIC, yytext); }

"if"                        { return setValue(lineCount, IF, yytext); }
"then"                      { return setValue(lineCount, THEN, yytext); }
"else"                      { return setValue(lineCount, ELSE, yytext); }
"while"                     { return setValue(lineCount, WHILE, yytext); }
"for"                       { return setValue(lineCount, FOR, yytext); }
".."                        { return setValue(lineCount, TO, yytext); }
"by"                        { return setValue(lineCount, BY, yytext); }
"step"                        { return setValue(lineCount, BY, yytext); }
"do"                        { return setValue(lineCount, DO, yytext); }

"return"                    { return setValue(lineCount, RETURN, yytext); }
"break"                     { return setValue(lineCount, BREAK, yytext); }

"and"                       { return setValue(lineCount, AND, yytext); }
"or"                        { return setValue(lineCount, OR, yytext); }
"not"                       { return setValue(lineCount, NOT, yytext); }

"begin"                     { return setValue(lineCount, T_BEGIN, yytext); }
"end"                       { return setValue(lineCount, T_END, yytext); }
"("                         { return setValue(lineCount, LPAREN, yytext); }
")"                         { return setValue(lineCount, RPAREN, yytext); }
"["                         { return setValue(lineCount, LBRACK, yytext); }
"]"                         { return setValue(lineCount, RBRACK, yytext); }

"*"                         { return setValue(lineCount, MUL, yytext); }
"/"                         { return setValue(lineCount, DIV, yytext); }
"%"                         { return setValue(lineCount, MOD, yytext); }
"+"                         { return setValue(lineCount, ADD, yytext); }
"-"                         { return setValue(lineCount, SUB, yytext); }
"++"                        { return setValue(lineCount, INC, yytext); }
"--"                        { return setValue(lineCount, DEC, yytext); }

"+="                        { return setValue(lineCount, ADDASGN, yytext); }
"-="                        { return setValue(lineCount, SUBASGN, yytext); }
"*="                        { return setValue(lineCount, MULASGN, yytext); }
"/="                        { return setValue(lineCount, DIVASGN, yytext); }
"<="                         { return setValue(lineCount, ASGN, yytext); }

"="                        { return setValue(lineCount, EQ, yytext); }
"!="                        { return setValue(lineCount, NEQ, yytext); }
"<"                         { return setValue(lineCount, LT, yytext); }
"!>"                        { return setValue(lineCount, LEQ, yytext); }
">"                         { return setValue(lineCount, GT, yytext); }
"!<"                        { return setValue(lineCount, GEQ, yytext); }

";"                         { return setValue(lineCount, SEMICOLON, yytext); }
":"                         { return setValue(lineCount, COLON, yytext); }
","                         { return setValue(lineCount, COMMA, yytext); }
"?"                         { return setValue(lineCount, QUESTION, yytext); }

"true"|"false"              { return setValue(lineCount, BOOLCONST, yytext); }

[a-zA-Z][a-zA-Z0-9]*        { return setValue(lineCount, ID, yytext); }             // Variable names (the id)
[0-9]+                      { return setValue(lineCount, NUMCONST, yytext); }       // Number literals
\"((\\\")|([^\n\"]))*\"     { return setValue(lineCount, STRINGCONST, yytext); }    // String literals
\'((\\\')|([^\n\']))*\'     { return setValue(lineCount, CHARCONST, yytext); }      // Char literals

. { std::cout << "ERROR(" << lineCount << "): Invalid or misplaced input character: '" << yytext[0] << "'. Character Ignored." << std::endl; errorCount++; }  // Any error-causing inputs

%%
