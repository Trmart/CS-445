/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW6
Dr. Wilder
DUE: 4/16/2023

FILE: yyerror.h
DESC: This file contains the error handling functions for the compiler. 
        Used in conjunction with the bison parser.
        Based on yyerror.h code from Dr. Wilder's CS445 Compiler Design course.
*/

#ifndef _YYERROR_H_
#define _YYERROR_H_


// write a nice error message
#define YYERROR_VERBOSE

// NOTE: make sure these variables interface with your code!!!
extern int line;        // line number of last token scanned in your scanner (.l)
extern char* yytext; // last token scanned in your scanner (connect to your .l)
extern int numErrors;   // number of errors

void initErrorProcessing();    // WARNING: MUST be called before any errors occur (near top of main)!
void yyerror(const char* msg); // error routine called by Bison


#endif /* _YYERROR_H_ */