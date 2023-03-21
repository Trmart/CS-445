
# Taylor Martin
# CS-445 Compiler Design
# University Of Idaho
# HW5
# Dr. Wilder
# DUE: 4/2/2023

# FILE: makefile
# DESC: makefile for the compiler

BIN = parser
CC = g++ -std=c++17 -g

FILES = AST.c symbolTable.cpp semantic.cpp IOinit.cpp TokenFormatter.c yyerror.cpp
SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.h AST.h symbolTable.h semantic.h IOinit.h TokenFormatter.h yyerror.h
OBJS = lex.yy.o $(BIN).tab.o 

$(BIN) : $(OBJS)
	$(CC) $(OBJS) $(FILES) -o c-

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDRS)
	flex $(BIN).l 

$(BIN).tab.h $(BIN).tab.c : $(BIN).y 
	bison -v -t -d $(BIN).y 

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output c-

tar:
	tar -cvf hw5.tar $(HDRS) $(SRCS) $(FILES) makefile