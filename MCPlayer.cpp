#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID) : Player(pID) {}

Move MCPlayer::move(void){
	std::vector<Move> lMoves;
	std::vector<Point> lFree = this->mCurrentState.freeSpaces();//Pointer is faster
	std::vector<std::future<int>> lResults;
	lMoves.reserve(lFree.size());//Possibly Broken Under GCC 4.7
	lResults.reserve(lFree.size());
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
	for(unsigned int i = 0; i < lResults.size(); i++){
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
	return initial.boardStateEnd();//We know there are no free spaces at this point.
}
