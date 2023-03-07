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
    // token string for printing
    std::string tokenString; 
    // index into the identifier table
    int identifierIndex;
    //token line number
    int tokenLineNumber;         
    // token content, whats in the token
    std::string tokenContent;    
    
    //char value
    char charValue;
    //number value          
    int numValue;    
    //string value      
    std::string stringValue; 
    //string length      
    int stringLength;
};

#endif