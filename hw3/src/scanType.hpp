/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
2/13/2023

FILE: scanType.hpp
DESC: Contains the TokenData struct Definition

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#ifndef SCANTYPE_H
#define SCANTYPE_H

#include <string>


struct TokenData 
{
    // The Line Number Within the File Where the Token Occurred
    int tokenLineNumber;     

    // The Token Information That Was Read
    std::string tokenInformation; 

};

#endif
