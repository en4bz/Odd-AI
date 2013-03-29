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
	std::random_device lGen;
	int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH; i++){
		if(pGoal == MCPlayer::simulateMatch(pStart, lGen())){
			lWins++;
		}
    }
	return lWins;
}

Board::STATE MCPlayer::simulateMatch(Board initial, int pSeed){
	const std::vector<Move> lMoves =  initial.samplePath(pSeed);
	for(const Move& m : lMoves){
		initial.update(m);
	}
	return initial.boardStateEnd();
}

