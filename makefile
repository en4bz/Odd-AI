CC = g++-4.7
STD = -std=c++11
OPT = -O0
CC_FLAGS = -Wall -msse2
LINK = -lboost_system -pthread
#ENABLE_DEBUG =-D_DEBUG_ -g
ENABLE_BENCH =-D_BENCHMARK_

Main : main.hpp main.cpp Board.o RandomPlayer.o
	$(CC) -o Main $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) main.cpp Board.o Point.o RandomPlayer.o Player.o $(LINK)

RandomPlayer.o : RandomPlayer.hpp RandomPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) RandomPlayer.cpp

Player.o : Player.hpp Player.cpp Board.o Move.hpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Player.cpp

Board.o : Board.hpp Board.cpp Point.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) $(ENABLE_BENCH) Board.cpp

Point.o : Point.hpp Point.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Point.cpp

clean :
	rm *\.o Main
