#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID) : Player(pID) {}

Move MCPlayer::move(void){
	std::vector<Move> lMoves;
	lMoves.reserve(2*this->movesLeft());
	for(Point& p : this->mCurrentState.freeSpaces()){
		lMoves.emplace_back(Move(p, Board::VALUE::WHITE));
		lMoves.emplace_back(Move(p, Board::VALUE::BLACK));
	}
	int lNumMoves = lMoves.size();//Should equal 2*movesLeft(). Replace for optimization.
	std::future<int> lResults[lNumMoves];
	for(int i = 0; i < lNumMoves; i++){
		#ifdef _DEBUG_
//		static int xyz = 0;
//		std::cout << "Displatched " << ++xyz << " States." << std::endl;
		#endif
		lResults[i] = dispatchSimulation(lMoves[i]);
	}
	#ifdef _DEBUG_
	std::cout << "Completed Displatches " << std::endl;
	#endif
	int lMaxIndex = 0;
	int lMaxValue = 0;
	for(int i = 0; i < lNumMoves; i++){
		#ifdef _DEBUG_
		std::cout << "Searching" << std::endl;
		#endif
		int lTemp = lResults[i].get();
		if(lTemp > lMaxValue){
			lMaxValue = lTemp;
			lMaxIndex = i;
		}
	}
	return lMoves[lMaxIndex];
}

std::future<int> MCPlayer::dispatchSimulation(const Move& pAction){
	auto lDispatch = new std::packaged_task<int(int,int,Board)>(&MCPlayer::simulation);
	Board lNewBoard = this->mCurrentState;//Place on Heap?
	lNewBoard[pAction.place] = pAction.colour;
	std::future<int> lReturn = lDispatch->get_future();
	#ifdef _DEBUG_
	std::cout << "Displatching " << std::endl;
	#endif
	std::thread(std::move(*lDispatch), this->mID, this->mEntropy(), lNewBoard).detach();
	return lReturn;
}


int MCPlayer::simulation(int pID, int seed, Board pStart){
	Board::STATE lGoal;
	if(pID == 1)
		lGoal = Board::STATE::ODD;
	else
		lGoal = Board::STATE::EVEN;
	std::mt19937 lGen(seed);
	int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH; i++){
		if(lGoal == simulateMatch(pStart, lGen)){
			lWins++;
		}
    }
	#ifdef _DEBUG_
	std::cout << "Completed Simulation" << std::endl;
	#endif
	return lWins;
}

//Push onto stack so we can mutate board.
Board::STATE MCPlayer::simulateMatch(Board initial, std::mt19937& pRandom){
	std::vector<Point> lMoves;
	while((lMoves = initial.freeSpaces()).size() > 0){
		int index = pRandom() % lMoves.size();//Not Valid
		Point p = lMoves[index];
		initial[p] = (pRandom() % 2) ? Board::BLACK : Board::WHITE;
	}
	return initial.boardState();
}
