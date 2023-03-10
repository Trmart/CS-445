/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: scanType.h
DESC: Holds the struct for the token data
*/


#ifndef SCANTYPE_H
#define SCANTYPE_H

struct TokenData
{
    
    char *tokenStrprint; 
    int idIndex;
    int lineno;         // what line did this token occur on?
    char *tokenstr;    
    char cvalue;         
    int nvalue;          
    char *stringvalue;       
    int strlength;

};

#endif