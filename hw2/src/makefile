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
CC = g++
SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.hpp
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
			$(CC) $(OBJS) TokenFormatter.cpp -o c- -std=c++17

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
				flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
							bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN).output $(BIN).tab.h $(BIN).tab.c lex.yy.c $(OBJS)

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile