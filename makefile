CC = g++-4.8
STD = -std=c++11
OPT = -Ofast -march=native #-fomit-frame-pointer -ffast-math -faggressive-loop-optimizations
CC_FLAGS = -Wall
LINK = -lboost_system -lboost_timer -pthread
#ENABLE_DEBUG =-D_DEBUG_ -g
#ENABLE_BENCH =-D_BENCHMARK_

MCP2 : main.hpp main.cpp MCP2.o
	$(CC) -o MCP2 $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -D_MCP2_ \
	 main.cpp Board.o Point.o Profiler.o Player.o MCP2.o AMAF2.o $(LINK)

AMAF2 : main.hpp main.cpp AMAF2.o
	$(CC) -o AMAF2 $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -D_AMAF2_ \
	 main.cpp Board.o Point.o Profiler.o Player.o AMAF2.o $(LINK)

AMAFPlayer : main.hpp main.cpp AMAF.o MCPlayer.o 
	$(CC) -o AMAFPlayer $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -D_AMAF_ \
	 main.cpp Board.o Point.o Profiler.o MCPlayer.o Player.o AMAF.o $(LINK)

MCPlayer : main.hpp main.cpp MCPlayer.o
	$(CC) -o MCPlayer $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -D_MONTECARLO_ \
	 main.cpp Board.o Point.o Profiler.o Player.o MCPlayer.o $(LINK)

MCP2.o : MCP2.hpp MCP2.cpp Player.o AMAF2.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) MCP2.cpp

AMAF2.o : AMAF2.hpp AMAF2.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) AMAF2.cpp

AMAF.o : AMAF.hpp AMAF.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) AMAF.cpp
	
NegaScout.o : NegaScout.hpp NegaScout.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) NegaScout.cpp

MCPlayer.o : MCPlayer.hpp MCPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) MCPlayer.cpp

Player.o : Player.hpp Player.cpp Board.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Player.cpp

Board.o : Board.hpp Board.cpp Point.o Profiler.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) $(ENABLE_BENCH) Board.cpp

Profiler.o : Profiler.hpp Profiler.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Profiler.cpp $(LINK)

Point.o : Point.hpp Point.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Point.cpp

clean :
	rm *\.o
