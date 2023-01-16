/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW1
Dr. Wilder
1/14/2023

FILE: TokenFormatter.cpp
DESC: Defines Functions to Format the TokenData contained string value for output

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#include "TokenFormatter.hpp"
#include <algorithm>

std::string TokenFormatter::toUpperCase(const std::string &str)
{
   std::string upperStr = str;
   std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
   return upperStr;
}

char TokenFormatter::parseLeftmostCharacter(const std::string &str)
{
   if (str.length() == 1)
   {
      return str[0];
   }

   char parsedChar;
   if (str[0] == '\\')
   {
      if (str[1] == 'n')
      {
         return '\n';
      }
      else if (str[1] == '0')
      {
         return '\0';
      }
      else
      {
         return str[1];
      }
   }
   return str[0];
}

std::string TokenFormatter::deleteLeftmostAndRightmostCharacters(const std::string &str)
{
   return str.substr(1, str.length() - 2);
}

std::string TokenFormatter::parseCharacters(const std::string &str)
{
   std::string unparsedChars = str;
   std::string parsedChars;
   while (unparsedChars.length() > 0)
   {
      char currChar = unparsedChars[0];
      parsedChars += parseLeftmostCharacter(unparsedChars);
      if (currChar == '\\' && unparsedChars.length() >= 2)
      {
         unparsedChars = unparsedChars.substr(2);
      }
      else
      {
         unparsedChars = unparsedChars.substr(1);
      }
   }
   return parsedChars;
}