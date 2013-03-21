STD = -std=c++11
OPT = -O0
CC_FLAGS = -Wall -g -msse2 
LINK = -lboost_system -pthread
ENABLE_DEBUG =-D_DEBUG_

Main : main.hpp main.cpp Board.o RandomPlayer.o
	g++ -o Main $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) main.cpp Board.o Point.o RandomPlayer.o Player.o $(LINK)

RandomPlayer.o : RandomPlayer.hpp RandomPlayer.cpp Player.o
	g++ -c $(STD) $(OPT) $(CC_FLAGS) RandomPlayer.cpp

Player.o : Player.hpp Player.cpp Board.o Move.hpp
	g++ -c $(STD) $(OPT) $(CC_FLAGS) Player.cpp

Board.o : Board.hpp Board.cpp Point.o
	g++ -c $(STD) $(OPT) $(CC_FLAGS) Board.cpp

Point.o : Point.hpp Point.cpp
	g++ -c $(STD) $(OPT) $(CC_FLAGS) Point.cpp

clean :
	rm *\.o
