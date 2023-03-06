/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: scanType.hs
DESC: Holds the token data structure
Based off Dr.Heckendorns Calculator example
*/


#ifndef SCANTYPE_H
#define SCANTYPE_H

#include <string>

struct TokenData
{
    
    // char *tokenStrprint; 
    // int idIndex;
    // int lineno;         // what line did this token occur on?
    // char *tokenstr;    
    // char cvalue;         
    // int nvalue;          
    // char *stringvalue;       
    // int strlength;

    std::string tokenString; // token string
    int identifierIndex; // index into the identifier table
    int tokenLineNumber;         //token line number occurance
    std::string tokenContent;    //token content
    char charValue;          
    int numValue;          
    std::string stringValue;       
    int stringLength;

};

#endif