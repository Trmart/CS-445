##################################################
#Taylor Martin
#CS-445 Compiler Design
#University Of Idaho
#HW2
#Dr. Wilder
#1/30/2023

#FILE: makefile
#DESC: makefile for c- compiler

#Based off CS445 - Calculator Example Program by Robert Heckendorn
###################################################

BIN = parser
CC = g++ -std=c++17 -g

SRCS = $(BIN).y $(BIN).l

# CC_SRCS = */*.cpp */*/*.cpp
# HDRS = *.hpp */*.hpp */*/*.hpp

CC_SRCS = TokenFormatter.cpp AST/*.cpp CompilerFlags.cpp ourgetopt/ourgetopt.cpp Emit/*.cpp Semantics/*.cpp
HDRS = TokenFormatter.hpp scanType.hpp AST/*.hpp CompilerFlags.hpp ourgetopt/ourgetopt.h Emit/*.hpp Semantics/*.hpp

OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) $(CC_SRCS) -o c- $(CC_ARGS)

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output test.out
	

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile
