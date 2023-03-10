%{
    
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: parer.l
DESC: This file is the lexer for the compiler. It will take in a file and parse it for tokens. 
      It will then return the tokens to the parser.
*/

#include "scanType.h"  
#include "AST.h"  
#include "parser.tab.h"  

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <iostream>
#include "TokenFormatter.h"

int line = 1;
int numErrors;    
int tokenLength;
int i;




static int setValue(int lineno, int tokenClass,  char *svalue)
{
    yylval.tokenData = new TokenData;

    yylval.tokenData->lineno = lineno;
    yylval.tokenData->tokenstr = strdup(svalue);

    switch(tokenClass)
    {

        case ID:
            {
                yylval.tokenData->tokenStrprint = strdup("ID");
                yylval.tokenData->idIndex = svalue[0] - 'a';
            }
            break;

        case BOOLCONST:
                    {
                        yylval.tokenData->tokenStrprint = strdup("BOOLCONST");

                        if(strcmp(svalue, "false") == 0)
                        {
                            yylval.tokenData->nvalue = 0;
                        }
                        else
                        {
                            yylval.tokenData->nvalue = 1;
                        }
                    }
                    break;
       
        case NUMCONST:
                    {
                        yylval.tokenData->tokenStrprint = strdup("NUMCONST");
                        yylval.tokenData->nvalue = atoi(svalue);
                    }
                    break;

        case CHARCONST:
                    {
                        tokenLength = strlen(svalue);

            
                        if(tokenLength == 3)
                        {
                            yylval.tokenData->cvalue = svalue[1];
                        }

                        if(tokenLength > 3)
                        {
                        
                            // check for \ escape (92), n is (110), 0 is (48). 
                            if(svalue[1] == 92 && svalue[2] != 110 && svalue[2] != 48)
                            {
                                yylval.tokenData->cvalue = svalue[2];
                            }
                        
                            else if(svalue[1] == 92 && svalue[2] != 110 && svalue[2] == 48)
                            {
                                yylval.tokenData->cvalue = '\0';
                            }
                            
                            else if(svalue[1] == 92 && svalue[2] == 110 && svalue[2] != 48)
                            {
                                yylval.tokenData->cvalue = '\n';
                            }
                                        
                            else if(svalue[1] != 92)
                            {
                                std::cout << "WARNING(" << line << "): character is " << (tokenLength-2) << " characters long and not a single character: \'" << svalue << "\'. The first char will be used." << std::endl;
                                yylval.tokenData->cvalue = svalue[1];
                            }
                        }

                        yylval.tokenData->tokenStrprint = strdup("CHARCONST");
                    }
                    break;
            
        case STRINGCONST:
                    {
                        // parse and remove escape characters and newline characters
                        for(i = 0; i <= strlen(svalue); i++)
                        {
                            if(svalue[1] == 92 && svalue[2] == 110 && svalue[2] != 48){

                                svalue[2] = '\n';       
                            }

                        }
                        
                        removeChar(svalue, '\\');

                        yylval.tokenData->tokenStrprint = strdup("STRINGCONST");
                        
                        yylval.tokenData->stringvalue = strdup(svalue);
                        
                        yylval.tokenData->strlength = getStrLength(svalue);
                    
                    }
                    break;
      
        case GEQ:
                {
                    yylval.tokenData->tokenStrprint = strdup("GEQ");
                }
                break;

        case INC:
                {
                    yylval.tokenData->tokenStrprint = strdup("INC");
                }
                break;

        case DEC:
                {
                    yylval.tokenData->tokenStrprint = strdup("DEC");
                }
                break;

        case NEQ:
                {
                    yylval.tokenData->tokenStrprint = strdup("NEQ");
                }
                break;
        
        case LEQ:
                {
                    yylval.tokenData->tokenStrprint = strdup("LEQ");
                }
                break;

        case ASGN:
                {
                    yylval.tokenData->tokenStrprint = strdup("ASGN");
                }
                break;

        case ADDASGN:
        {
            yylval.tokenData->tokenStrprint = strdup("ADDASGN");
        }
        break;
       
    }
        
    return tokenClass;
}

%}

%option noyywrap

%%



"int"                               {return setValue(line, INT, yytext);}
"bool"                              {return setValue(line, BOOL, yytext);}
"char"                              {return setValue(line, CHAR, yytext);}
"static"                            {return setValue(line, STATIC, yytext);}

"if"                                {return setValue(line, IF, yytext);}
"or"                                {return setValue(line, OR, yytext);}
"not"                               {return setValue(line, NOT, yytext);}
"by"                                {return setValue(line, BY, yytext);}
"else"                              {return setValue(line, ELSE, yytext);}
"then"                              {return setValue(line, THEN, yytext);}
"for"                               {return setValue(line, FOR, yytext);}
"break"                             {return setValue(line, BREAK, yytext);}
"return"                            {return setValue(line, RETURN, yytext);}
"and"                               {return setValue(line, AND, yytext);}
"begin"                             {return setValue(line, BEGN, yytext);}
"end"                               {return setValue(line, FINISH, yytext);}
"do"                                {return setValue(line, DO, yytext);}
"while"                             {return setValue(line, WHILE, yytext);}
"to"                                {return setValue(line, TO, yytext);}
"true"                              {return setValue(line, BOOLCONST, yytext);}
"false"                             {return setValue(line, BOOLCONST, yytext);}
"step"                              {return setValue(line, BY, yytext);}



"+="                                {return setValue(line, ADDASGN, yytext);}
"--"                                {return setValue(line, DEC, yytext);}
"<="                                {return setValue(line, ASGN, yytext);}
".."                                {return setValue(line, TO, yytext);}
"++"                                {return setValue(line, INC, yytext);}
"!<"                                {return setValue(line, GEQ, yytext);}
"!>"                                {return setValue(line, LEQ, yytext);}
"!="                                {return setValue(line, NEQ, yytext);}
"-="                                {return setValue(line, SUBASS, yytext);}
"/="                                {return setValue(line, DIVASS, yytext);}
"*="                                {return setValue(line, MULASS, yytext);}

"?"                                 {return setValue(line, QUESTION, yytext);}
"<"                                 {return setValue(line, LESS, yytext);}
">"                                 {return setValue(line, GREAT, yytext);}
"+"                                 {return setValue(line, PLUS, yytext);}
"="                                 {return setValue(line, EQUAL, yytext);}
"*"                                 {return setValue(line, MULT, yytext);}
"/"                                 {return setValue(line, DIV, yytext);}
"%"                                 {return setValue(line, MOD, yytext);}
","                                 {return setValue(line, COMMA, yytext);}
"["                                 {return setValue(line, OBRACKET, yytext);}
"]"                                 {return setValue(line, CBRACKET, yytext);}
"-"                                 {return setValue(line, MINUS, yytext);}
":"                                 {return setValue(line, COLON, yytext);}
";"                                 {return setValue(line, SEMICOLON, yytext);}
"("                                 {return setValue(line, OPAREN, yytext);}
")"                                 {return setValue(line, CPAREN, yytext);}

\'(\\.|[^\n\'])*\'                  {return setValue(line, CHARCONST, yytext);}
\"(\\.|[^\\\n\"])*\"                {return setValue(line, STRINGCONST, yytext);} 

[a-zA-Z]([a-zA-Z]|[0-9])*           {return setValue(line, ID, yytext);}
[0-9]+                              {return setValue(line, NUMCONST, yytext);}

[ \t]+
"##".*
\n                                  {line++;}

.                                   {std::cout << "ERROR(" << line << "): Invalid or misplaced input character: '" << yytext[0] << "'. Character Ignored." << std::endl; numErrors++;}


%%
