#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID, Board* const pBoard) : Player(pID, pBoard) {}

Move MCPlayer::move(void){
	const std::vector<Move>& lMoves = this->mCurrentState->validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
		lResults.emplace_back(dispatchSimulation(m));
	}
	int lMaxIndex = 0;
	int lMaxValue = 0;
	for(uint32_t i = 0; i < lResults.size(); i++){
		const int lTemp = lResults[i].get();
		if(lTemp > lMaxValue){
			lMaxValue = lTemp;
			lMaxIndex = i;
		}
	}
	return lMoves[lMaxIndex];
}

std::future<int> MCPlayer::dispatchSimulation(const Move& pAction){
	std::packaged_task<int(Board::STATE,int,Board)> lDispatch(&MCPlayer::simulation);
	Board lNewBoard(*(this->mCurrentState));
	lNewBoard.update(pAction);
	std::future<int> lReturn = lDispatch.get_future();
	std::thread(std::move(lDispatch), this->mGoal, this->mEntropy(), lNewBoard).detach();
	return lReturn;
}


int MCPlayer::simulation(const Board::STATE pGoal, int pSeed, Board pStart){
	__gnu_cxx::sfmt607 lGen(pSeed);
	std::uniform_int_distribution<int> lSelector(0,1);
//	std::mt19937 lGen(seed);
	int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH; i++){
		if(pGoal == MCPlayer::simulateMatch(pStart, lGen, lSelector)){
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
	while((lMoves = (initial.freeSpaces())).size() > 0){
		const Point& p = lMoves[pRandom() % lMoves.size()];//Not Uniform?
		initial.update(p, pSelector(pRandom) == 0 ? Board::BLACK : Board::WHITE);
	}
	return initial.boardStateEnd();//We know there are no free spaces at this point.
}
