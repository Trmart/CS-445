/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW5
Dr. Wilder
DUE: 4/2/2023

FILE: scanType.h
DESC: Holds the struct for the token data
*/


#ifndef SCANTYPE_H
#define SCANTYPE_H

struct TokenData
{
    char* tokenStrprint; 
    int idIndex;
    int lineno;
    char* tokenstr;    
    char cvalue;         
    int nvalue;          
    char* stringvalue;       
    int strlength;
};

#endif