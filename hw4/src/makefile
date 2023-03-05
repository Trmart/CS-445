##################################################
#Taylor Martin
#CS-445 Compiler Design
#University Of Idaho
#HW4
#Dr. Wilder
#DUE: 3/12/2023

#FILE: makefile
#DESC: makefile for c- compiler
#USAGE: make
###################################################

BIN = parser
CC = g++ -std=c++17 -g

SRCS = $(BIN).y $(BIN).l

CC_SRCS = AST.cpp CompilerFlags.cpp EmitDiagnostics.cpp Semantics.cpp
HDRS = TokenFormatter.hpp scanType.hpp AST.hpp CompilerFlags.hpp EmitDiagnostics.hpp Semantics.hpp

OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) $(CC_SRCS) -o c- 

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output test.out c-
	

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile