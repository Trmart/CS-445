/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/

#ifndef IOINIT_H
#define IOINIT_H

#include "symbolTable.h"
#include "AST.h"
#include "scanType.h"
#include "semantic.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

void setupIO();
#endif