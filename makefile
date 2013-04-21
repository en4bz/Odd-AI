CC = g++-4.7
STD = -std=c++11
OPT = -Ofast -march=native
CC_FLAGS = -Wall
LINK = -lboost_system -lboost_timer -pthread
CORES := $(shell grep -c "processor" /proc/cpuinfo)

MCP2 : main.hpp main.cpp MCP2.o
	$(CC) -o MCP2 $(STD) $(OPT) $(CC_FLAGS) -D_MCP2_ \
	 main.cpp Board.o Point.o Profiler.o Player.o MCP2.o AMAF2.o $(LINK)

AMAF2 : main.hpp main.cpp AMAF2.o
	$(CC) -o AMAF2 $(STD) $(OPT) $(CC_FLAGS) -D_AMAF2_ \
	 main.cpp Board.o Point.o Profiler.o Player.o AMAF2.o $(LINK)

AMAFPlayer : main.hpp main.cpp AMAF.o MCPlayer.o 
	$(CC) -o AMAFPlayer $(STD) $(OPT) $(CC_FLAGS) -D_AMAF_ \
	 main.cpp Board.o Point.o Profiler.o MCPlayer.o Player.o AMAF.o $(LINK)

MCPlayer : main.hpp main.cpp MCPlayer.o
	$(CC) -o MCPlayer $(STD) $(OPT) $(CC_FLAGS) -D_MONTECARLO_ \
	 main.cpp Board.o Point.o Profiler.o Player.o MCPlayer.o $(LINK)

MCP2.o : MCP2.hpp MCP2.cpp Player.o AMAF2.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) MCP2.cpp

AMAF2.o : AMAF2.hpp AMAF2.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) AMAF2.cpp

AMAF.o : AMAF.hpp AMAF.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) AMAF.cpp
	
MCPlayer.o : MCPlayer.hpp MCPlayer.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) MCPlayer.cpp

Player.o : Player.hpp Player.cpp Board.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Player.cpp

Board.o : Board.hpp Board.cpp Point.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Board.cpp

Profiler.o : Profiler.hpp Profiler.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Profiler.cpp

Point.o : Point.hpp Point.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) Point.cpp

clean :
	rm *\.o
