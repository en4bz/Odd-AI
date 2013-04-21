CC = g++-4.7
STD = -std=c++11
OPT = -Ofast -march=native
CC_FLAGS = -Wall
LINK = -lboost_system -lboost_timer -pthread
CORES := $(shell nproc)

MCP2 : main.hpp main.cpp MCP2.o
	$(CC) -o MCP2 $(STD) $(OPT) $(CC_FLAGS) -D_MCP2_ \
	main.cpp Board.o Point.o Player.o MCP2.o AMAF2.o $(LINK)

HP_AMAFPlayer : main.hpp main.cpp HP_AMAF.o MCPlayer.o
	$(CC) -o HP_AMAFPlayer $(STD) $(OPT) $(CC_FLAGS) -D_HP_AMAF_ \
	main.cpp Board.o Point.o MCPlayer.o Player.o AMAF.o $(LINK)

AMAFPlayer : main.hpp main.cpp AMAFPlayer.o MCPlayer.o
	$(CC) -o AMAFPlayer $(STD) $(OPT) $(CC_FLAGS) -D_AMAF_ \
	main.cpp Board.o Point.o MCPlayer.o Player.o AMAFPlayer.o $(LINK)

MCPlayer : main.hpp main.cpp MCPlayer.o
	$(CC) -o MCPlayer $(STD) $(OPT) $(CC_FLAGS) -D_MONTECARLO_ \
	main.cpp Board.o Point.o Player.o MCPlayer.o $(LINK)

MCP2.o : MCP2.hpp MCP2.cpp Player.o AMAF2.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) MCP2.cpp

AMAFPlayer.o : AMAFPlayer.hpp AMAFPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) AMAFPlayer.cpp
	
MCPlayer.o : MCPlayer.hpp MCPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) MCPlayer.cpp

Player.o : Player.hpp Player.cpp Board.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Player.cpp

Board.o : Board.hpp Board.cpp Point.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Board.cpp

Point.o : Point.hpp Point.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Point.cpp

clean :
	rm *\.o
