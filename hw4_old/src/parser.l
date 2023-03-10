%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: parser.l
DESC: Lex file for the parser
USAGE: lex parser.l
*/

#include "scanType.hpp"  // my header.
#include "AST.hpp"  // Tree Struct 
#include "parser.tab.h"  // flex/Bison header
#include "TokenFormatter.hpp"

#include <iostream>
#include <string>
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include <stdbool.h>

int lineCount = 1;
int errorCount;
int wordLength;
// int index;
TokenFormatter tokenFormatter;


static int setValue(int lineNumber, int tokenClass,  char *svalue)
{
    yylval.tokenData = new TokenData;

    yylval.tokenData->tokenLineNumber = lineNumber;
    yylval.tokenData->tokenContent = strdup(svalue);

    switch(tokenClass)
    {

        case ID:
            {
                yylval.tokenData->tokenString = "ID";
                yylval.tokenData->identifierIndex = svalue[0] - 'a';
            }
            break;

        case BOOLCONST:
                    {
                        yylval.tokenData->tokenString = "BOOLCONST";

                        if(strcmp(svalue, "false") == 0)
                        {
                            yylval.tokenData->numValue = 0;
                        }
                        else
                        {
                            yylval.tokenData->numValue = 1;
                        }
                    }
                    break;
       
        case NUMCONST:
                    {
                        yylval.tokenData->tokenString = "NUMCONST";
                        yylval.tokenData->numValue = atoi(svalue);
                    }
                    break;

        case CHARCONST:
                    {
                        //create new temp string and concatenate the first and last character of the constantValue string
                        std::string tempString = tokenFormatter.stringSize(yylval.tokenData->tokenContent);
                        
                        //parse the tempString and assign the char value to m_tokenData.charValue
                        yylval.tokenData->charValue = tokenFormatter.parseLeftmostCharacter(tempString);

                        yylval.tokenData->tokenString = "CHARCONST"; 
                        
                        if(tempString.length() > 1 && tempString[0] != '\\')
                        {
                            //throw error flag
                            std::cout << "WARNING(" << lineCount << "): character is " << tempString.length() - 1 << " characters long and not a single character: \'" << tempString << "\'. The first char will be used." << std::endl;
                            yylval.tokenData->charValue = svalue[1];
                        }
                    }
                    break; 
            
        case STRINGCONST:
                    {
                        yylval.tokenData->stringValue = tokenFormatter.parseCharacters(tokenFormatter.stringSize(yylval.tokenData->tokenContent));
                        yylval.tokenData->tokenString = "STRINGCONST";
                        yylval.tokenData->stringLength = yylval.tokenData->stringValue.length();
                    }
                    break; 
      
        case GEQ:
            {
                yylval.tokenData->tokenString = "GEQ";
            }
            break;

        case INC:
            {
                yylval.tokenData->tokenString = "INC";
            }
            break;

        case DEC:
            {
                yylval.tokenData->tokenString = "DEC";
            }
            break;

        case NEQ:
            {
                yylval.tokenData->tokenString = "NEQ";
            }
            break;
        
        case LEQ:
            {
                yylval.tokenData->tokenString = "LEQ";
            }
            break;

        case ASGN:
            {
                yylval.tokenData->tokenString = "ASGN";
            }
            break;

        case ADDASGN:
            {
                yylval.tokenData->tokenString = "ADDASGN";
            }
            break;
       
    }
        
    return tokenClass;
}

%}

%option noyywrap

%%


\#\#.*\n                    { lineCount++; }                 // Ignore comments
[ \t]                       { }                 // Ignore whitespace
"\n"                        { lineCount++; }    // Newlines

"int"                       { return setValue(lineCount,INT,yytext); }
"bool"                      { return setValue(lineCount,BOOL,yytext); }
"char"                      { return setValue(lineCount,CHAR,yytext); }
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