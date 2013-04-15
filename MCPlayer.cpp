#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID, Board* const pBoard) : Player(pID, pBoard) {}

Move MCPlayer::move(void){
	const std::vector<Move>& lMoves = this->mCurrentState->validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
//	std::cout << "Dispatching" << std::endl;
	for(const Move& m : lMoves){
		lResults.emplace_back(dispatchSimulation(m));
	}
//	std::cout << "Done Dispatching" << std::endl;
	int lMaxIndex = 0;
	int lMaxValue = 0;
	const uint32_t lResultsSize = lResults.size();
	for(uint32_t i = 0; i < lResultsSize; i++){
		const int lTemp = lResults[i].get();
//		std::cout << "Result:" << i << " = " << lTemp << std::endl;
		if(lTemp > lMaxValue){
			lMaxValue = lTemp;
			lMaxIndex = i;
		}
	}
	return lMoves[lMaxIndex];
}

std::future<int> MCPlayer::dispatchSimulation(const Move& pAction){
	std::packaged_task<int(Board::STATE,Board,int)> lDispatch(&MCPlayer::simulation);
	Board lNewBoard(*(this->mCurrentState));
	lNewBoard.update(pAction);
	std::future<int> lReturn = lDispatch.get_future();
	std::thread(std::move(lDispatch), this->mGoal, lNewBoard, this->mRound*5).detach();
	return lReturn;
}


int MCPlayer::simulation(const Board::STATE pGoal, const Board pStart, const int pBoost){
	std::random_device lGen;
	int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH + pBoost; i++){
		Board lTemp = pStart;
		for(const Move& m : lTemp.samplePath(lGen())){
			lTemp.update(m);
		}
		if(pGoal == lTemp.boardStateEnd()){
			lWins++;
		}
    }
	return lWins;
}

