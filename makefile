CC = g++
STD = -std=c++11
OPT = -O3 -march=native
CC_FLAGS = -Wall -DNDEBUG
LINK = -lboost_system -lboost_timer -pthread
CORES := $(shell nproc)

PreemptiveMCPlayer : main.hpp main.cpp PreemptiveMC.o
	$(CC) -o PreemptiveMCPlayer $(STD) $(OPT) $(CC_FLAGS) -D_PREEMPTIVE_MC_ \
	main.cpp Board.o Point.o Player.o PreemptiveMC.o $(LINK)

HP_AMAFPlayer : main.hpp main.cpp HP_AMAF.o MCPlayer.o
	$(CC) -o HP_AMAFPlayer $(STD) $(OPT) $(CC_FLAGS) -D_HP_AMAF_ \
	main.cpp Board.o Point.o MCPlayer.o Player.o HP_AMAF.o $(LINK)

HP_MCPlayer : main.hpp main.cpp MCPlayer.o HPMC.o
	$(CC) -o HP_MCPlayer $(STD) $(OPT) $(CC_FLAGS) -D_HP_MC_ \
	main.cpp Board.o Point.o MCPlayer.o Player.o HPMC.o $(LINK)

MCPlayer : main.hpp main.cpp MCPlayer.o
	$(CC) -o MCPlayer $(STD) $(OPT) $(CC_FLAGS) -D_MONTECARLO_ main.cpp Board.o Point.o Player.o MCPlayer.o $(LINK)

PreemptiveMC.o : PreemptiveMC.hpp PreemptiveMC.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) PreemptiveMC.cpp

HP_AMAF.o : HP_AMAF.hpp HP_AMAF.cpp Player.o MCPlayer.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) HP_AMAF.cpp

HPMC.o : HPMC.hpp HPMC.cpp Player.o
	$(CC) -c $(STD) $(OPT) $(CC_FLAGS) -DTHREADS=$(CORES) HPMC.cpp

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
