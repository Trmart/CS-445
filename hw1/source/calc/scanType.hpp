/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW1
Dr. Wilder
1/14/2023

FILE: scanType.hpp
DESC: Contains the TokenData struct

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#ifndef SCANTYPE_H
#define SCANTYPE_H

#include <string>


struct TokenData 
{
    // The Line Number Within the File Where the Token Occurred
    int tokenLineNumber;     

    // The Token That Was Read
    std::string tokenData;  
    
    // True if length of character > 1
    bool isCharLengthGreaterThan1 = false; 
    
    // The Value of the Token Data Types
    
    //int values
    int numValue; 
    
    //string values
    std::string stringValue;
    
    //char values
    char charValue;
    
};

#endif