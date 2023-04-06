/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW6
Dr. Wilder
DUE: 4/16/2023

FILE: TokenFormatter.h
DESC: Declares functions for TokenFormatter.c. for formatting strings and chars.
*/


#ifndef TOKENFORMATER_H
#define TOKENFORMATER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// function for removing invalid chars from a string
void removeChar(char *str, char word);

// Function converts all lower case chars to upper case.
void UpperCase(char *Letter);

// Function gets length of string
int getStrLength (char *svalue);

#endif  // TOKENFORMATER_H