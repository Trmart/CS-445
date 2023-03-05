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

#include "scanType.h"  // my header.
#include "AST.h"  // Tree Struct 
#include "parser.tab.h"  // flex/Bison header
#include "TokenFormatter.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int lineCount = 1;
int errorCount;
int wordLength;
int index;
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
                        std::string tempString = tokenFormatter.stringSize(constantValue);
                        
                        //parse the tempString and assign the char value to m_tokenData.charValue
                        charValue = tokenFormatter.parseLeftmostCharacter(tempString);

                        if(tempString.length() > 1 && tempString[0] != '\\')
                        {
                            //throw error flag
                            std::cout << "WARNING(" << lineCount << "): character is " << tempString.length() - 1 << " characters long and not a single character: \'" << tempString << "\'. The first char will be used." << std::endl;
                            yylval.tokenData->charValue = svalue[1];
                        }
                    }
                    break; 

            // WrdLength = strlen(svalue);

            //  // if str length is 3 assign it to svalue first index. 
            // if(WrdLength == 3){
            //     yylval.tokenData->charValue = svalue[1];
            // }

            // if(WrdLength > 3){
			
            //     // check for \ escape (92), n is (110), 0 is (48). 
            //     if(svalue[1] == 92 && svalue[2] != 110 && svalue[2] != 48){
            //         yylval.tokenData->charValue = svalue[2];
            //     }
               
			//     else if(svalue[1] == 92 && svalue[2] != 110 && svalue[2] == 48){
            //         yylval.tokenData->charValue = '\0';
            //     }
				
            //     else if(svalue[1] == 92 && svalue[2] == 110 && svalue[2] != 48){
            //         yylval.tokenData->charValue = '\n';
            //     }
                            
            //     else if(svalue[1] != 92){
            //          printf("WARNING(%d): character is %d characters long and not a single character: \'%s\'. The first char will be used.\n", line, (WrdLength-2), svalue);
            //          yylval.tokenData->charValue = svalue[1];
            //     }
            // }

            // yylval.tokenData->tokenString = strdup("CHARCONST");
            // break;
            
        case STRINGCONST:
                    {
                        stringValue = tokenFormatter.parseCharacters(m_tokenFormatter.deleteLeftmostAndRightmostCharacters(constantValue));

                    }
                    break; 

            // // use simple for loop to parse for \n newline
            // for(i = 0; i <= strlen(svalue); i++){
  		    //     if(svalue[1] == 92 && svalue[2] == 110 && svalue[2] != 48){

  			//         svalue[2] = '\n';       
 		    //     }
    
	        // }
            
            // removeChar(svalue, '\\');

            // yylval.tokenData->tokenString = strdup("STRINGCONST");
            // yylval.tokenData->stringValue = strdup(svalue);
            // yylval.tokenData->stringLength = StrLength(svalue);
          
            // break;
      
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





/* [ \t]+
"##".*
\n                                  {line++;}


"int"                               {return setValue(line, INT, yytext);}
"if"                                {return setValue(line, IF, yytext);}
"or"                                {return setValue(line, OR, yytext);}
"not"                               {return setValue(line, NOT, yytext);}
"by"                                {return setValue(line, BY, yytext);}
"else"                              {return setValue(line, ELSE, yytext);}
"then"                              {return setValue(line, THEN, yytext);}
"for"                               {return setValue(line, FOR, yytext);}
"break"                             {return setValue(line, BREAK, yytext);}
"return"                            {return setValue(line, RETURN, yytext);}
"bool"                              {return setValue(line, BOOL, yytext);}
"char"                              {return setValue(line, CHAR, yytext);}
"static"                            {return setValue(line, STATIC, yytext);}
"and"                               {return setValue(line, AND, yytext);}
"begin"                             {return setValue(line, BEGN, yytext);}
"end"                               {return setValue(line, FINISH, yytext);}
"do"                                {return setValue(line, DO, yytext);}
"while"                             {return setValue(line, WHILE, yytext);}
"to"                                {return setValue(line, TO, yytext);}
"true"                              {return setValue(line, BOOLCONST, yytext);}
"false"                             {return setValue(line, BOOLCONST, yytext);}
"step"                              {return setValue(line, BY, yytext);}

\'(\\.|[^\n\'])*\'                  {return setValue(line, CHARCONST, yytext);}
\"(\\.|[^\\\n\"])*\"                {return setValue(line, STRINGCONST, yytext);} 

[a-zA-Z]([a-zA-Z]|[0-9])*           {return setValue(line, ID, yytext);}
[0-9]+                              {return setValue(line, NUMCONST, yytext);}

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

.                                   {printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++;}

%% */ 
