
# Taylor Martin
# CS-445 Compiler Design
# University Of Idaho
# HW4
# Dr. Wilder
# DUE: 3/12/2023

# FILE: makefile
# DESC: makefile for the compiler

BIN = parser
CC = g++ -std=c++17

FLES = AST.c symbolTable.cpp semantic.cpp IOinit.cpp TokenFormatter.c
SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.h AST.h symbolTable.h semantic.h IOinit.h TokenFormatter.h
OBJS = lex.yy.o $(BIN).tab.o 

$(BIN) : $(OBJS)
	$(CC) $(OBJS) $(FLES) -o c-

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDRS)
	flex $(BIN).l 

$(BIN).tab.h $(BIN).tab.c : $(BIN).y 
	bison -v -t -d $(BIN).y 

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output c-

tar:
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) $(FLES) makefile