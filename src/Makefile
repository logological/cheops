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
