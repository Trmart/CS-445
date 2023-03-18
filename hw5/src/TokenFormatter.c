/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW5
Dr. Wilder
DUE: 4/2/2023

FILE: TokenFormatter.c
DESC: Defines functions from TokenFormatter.h for formatting strings and chars.
*/

#include "TokenFormatter.h"



// removeChar function removes all instances of a invalid char from a string.
void removeChar(char *str, char word)
{

    bool IsChar = false;
    char *start, *end;
   
    for(start = end = str; *str != '\0'; start++)
    {

        *end = *start;
      
        if(*end != word)
        {
            IsChar = false;
            end++;
        }
        else
        {
            if(IsChar)
            {
                IsChar = false;
                end++;           
            }
            else
            {
                IsChar = true;
            }
        }
        str++;
    }
    *end = '\0';
}

// UpperCase function changes all lower case chars to upper case.
void UpperCase(char *Letter)
{
    while(*Letter)
    {
        //use toupper function given in c type library
        *Letter = toupper((unsigned char) *Letter);
        Letter++;
    }

    return;
}

// Function gets length of string
int getStrLength (char *svalue)
{
    return strlen(svalue)-2;
}