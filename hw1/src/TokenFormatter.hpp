/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW1
Dr. Wilder
1/14/2023

FILE: TokenFormatter.hpp
DESC: Defines Function Prototypes to Format the TokenData contained string value for output

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#ifndef TOKENFORMATTER_H
#define TOKENFORMATTER_H

#include <string>

class TokenFormatter
{
   public:
   
      // Formats the TokenData contained string value to UpperCase Letters
      static std::string toUpperCase(const std::string &str);

      // identifies if the leftmost char is the beginning of a newline or null char
      static char parseLeftmostCharacter(const std::string &str);

      // deletes the leftmost and rightmost characters of a string
      static std::string deleteLeftmostAndRightmostCharacters(const std::string &str);

      // parses the characters of a string
      static std::string parseCharacters(const std::string &str);
};    

#endif