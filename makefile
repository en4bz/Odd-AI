CC = g++-4.8
STD = -std=c++11
OPT = -O1 -msse2 -ffast-math -march=native
CC_FLAGS = -Wall
LINK = -lboost_system -pthread
#ENABLE_DEBUG =-D_DEBUG_ -g
#ENABLE_BENCH =-D_BENCHMARK_

Main : main.hpp main.cpp Board.o RandomPlayer.o MCPlayer.o #UCBPlayer.o #NegaScout.o
	$(CC) -o Main $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) main.cpp \
	Board.o Point.o Profiler.o Player.o MCPlayer.o RandomPlayer.o $(LINK)

NegaScout.o : NegaScout.hpp NegaScout.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) NegaScout.cpp

UCBPlayer.o : UCBPlayer.hpp UCBPlayer.cpp MCPlayer.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) UCBPlayer.cpp

MCPlayer.o : MCPlayer.hpp MCPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) MCPlayer.cpp

RandomPlayer.o : RandomPlayer.hpp RandomPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) RandomPlayer.cpp

Player.o : Player.hpp Player.cpp Board.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Player.cpp

Board.o : Board.hpp Board.cpp Point.o Profiler.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) $(ENABLE_BENCH) Board.cpp

Profiler.o : Profiler.hpp Profiler.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Profiler.cpp

Point.o : Point.hpp Point.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Point.cpp

clean :
	rm *\.o Main
