# $Id: Makefile,v 1.2 2003-11-24 21:11:52 psy Exp $

CC = g++
CFLAGS = -ansi -pedantic -O3
OBJS = ChessBoard.cpp ComputerPlayer.cpp HumanPlayer.cpp move.cpp Player.cpp StdAfx.cpp cheops.cpp
LIBS = -lstdc++ -lm
RM = rm -rf

all: cheops

cheops:	$(OBJS)
	$(CC) $(CFLAGS) -ocheops $(OBJS) $(LIBS)

clean:
	$(RM) core
	$(RM) *.o
	$(RM) cheops
