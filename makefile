CC = g++-4.8
STD = -std=c++11
OPT = -O1 -march=native
CC_FLAGS = -Wall
LINK = -lboost_system -lboost_timer -pthread
#ENABLE_DEBUG =-D_DEBUG_ -g
#ENABLE_BENCH =-D_BENCHMARK_


HybridPlayer : main.hpp main.cpp Board.o MCPlayer.o NegaScout.o
	$(CC) -o Hybrid $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -DHYBRIDPLAYER \
	main.cpp Hybrid.cpp Board.o Point.o Profiler.o Player.o MCPlayer.o NegaScout.o $(LINK)

AMAFPlayer : main.hpp main.cpp AMAF.o MCPlayer.o
	$(CC) -o AMAFPlayer $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -D_AMAF_ \
	 main.cpp Board.o Point.o Profiler.o MCPlayer.o Player.o AMAF.o $(LINK)

MCPlayer : main.hpp main.cpp Board.o MCPlayer.o
	$(CC) -o MCPlayer $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) -DMONTECARLO \
	 main.cpp Board.o Point.o Profiler.o Player.o MCPlayer.o $(LINK)

#Hybrid.o : Hybrid.hpp Hybrid.cpp Player.o MCPlayer.o NegaScout.o
#	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Hybrid.cpp Player.o

AMAF.o : AMAF.hpp AMAF.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) AMAF.cpp

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
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Profiler.cpp $(LINK)

Point.o : Point.hpp Point.cpp
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) $(ENABLE_DEBUG) Point.cpp

clean :
	rm *\.o
