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
   // copy the string to a new string
   std::string upperStr = str;
   
   // transform the string to upper case
   std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
   
   // return the new string
   return upperStr;
}

char TokenFormatter::parseLeftmostCharacter(const std::string &str)
{
   // if the string is empty, return a null char
   if (str.length() == 1)
   {
      return str[0];
   }

   char parsedChar;

   // if the string is a newline or null char, return the appropriate char
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
   //return the newly shortened string. Deleting the first and last characters
   return str.substr(1, str.length() - 2);
}

std::string TokenFormatter::parseCharacters(const std::string &str)
{
   //copy the string to a new string
   std::string unparsedChars = str;

   //create temporary string to hold the parsed characters
   std::string parsedChars;

   //while the string is not empty, parse the leftmost character and add it to the parsed string
   while (unparsedChars.length() > 0)
   {
      char currChar = unparsedChars[0];

      parsedChars += parseLeftmostCharacter(unparsedChars);
      
      //remove '\\' from unparsedChars
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