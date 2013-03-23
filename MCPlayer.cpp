#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID) : Player(pID) {}

Move MCPlayer::move(void){
	std::vector<Move> lMoves;
	std::vector<Point> lFree = this->mCurrentState.freeSpaces();//Pointer is faster
	std::vector<std::future<int>> lResults;
	lMoves.reserve(lFree.size() << 2);
	lResults.reserve(lFree.size() << 2);
	for(const Point& p : lFree){
		lMoves.emplace_back(Move(p, Board::VALUE::WHITE));
		lResults.emplace_back( dispatchSimulation(lMoves.back()));
		lMoves.emplace_back(Move(p, Board::VALUE::BLACK));
		lResults.emplace_back( dispatchSimulation(lMoves.back()));
	}
	#ifdef _DEBUG_
	std::cout << "Completed Displatches " << std::endl;
	#endif
	int lMaxIndex = 0;
	int lMaxValue = 0;
	for(uint32_t i = 0; i < lResults.size(); i++){
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

std::future<int> MCPlayer::dispatchSimulation(Move pAction){
	std::packaged_task<int(int,int,Board)> lDispatch(&MCPlayer::simulation);
	Board lNewBoard = this->mCurrentState;
	lNewBoard[pAction.place] = pAction.colour;
	#ifdef _DEBUG_
	std::cout << "Displatching " << std::endl;
	#endif
	std::future<int> lReturn = lDispatch.get_future();
	std::thread(std::move(lDispatch), this->mID, this->mEntropy(), lNewBoard).detach();
	return lReturn;
}


int MCPlayer::simulation(int pID, int pSeed, Board pStart){
	Board::STATE lGoal;
	if(pID == 1)
		lGoal = Board::STATE::ODD;
	else
		lGoal = Board::STATE::EVEN;

	__gnu_cxx::sfmt607 lGen(pSeed);
	std::uniform_int_distribution<int> lSelector(0,1);
//	std::mt19937 lGen(seed);
	int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH; i++){
		if(lGoal == simulateMatch(pStart, lGen, lSelector)){
			lWins++;
		}
    }
	#ifdef _DEBUG_
	std::cout << "Completed Simulation" << std::endl;
	#endif
	return lWins;
}

//Push onto stack so we can mutate board.
Board::STATE MCPlayer::simulateMatch(Board initial, __gnu_cxx::sfmt607& pRandom, std::uniform_int_distribution<int>& pSelector){
	std::vector<Point> lMoves;
	while((lMoves = initial.freeSpaces()).size() > 0){
		uint32_t lIndex = pRandom() % lMoves.size();//Not Valid
		Point p = lMoves[lIndex];
		initial[p] = pSelector(pRandom) ?  Board::BLACK : Board::WHITE;
	}
	return initial.boardStateEnd();//We know there are no free spaces at this point.
}
