#include "HPMC.hpp"

HP_MCPlayer::HP_MCPlayer(int pID) : Player(pID) {}

Move HP_MCPlayer::move(void){
	const std::vector<Move>& lMoves = this->mCurrentState.validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
		std::packaged_task<int(Board::STATE,Board,int)> lDispatch(&MCPlayer::simulation);//Create Task
		lResults.emplace_back(lDispatch.get_future());//Get Future
		Board lNewBoard = this->mCurrentState;//Copy Board
		lNewBoard.update(m);//Mutate Board
		std::thread(std::move(lDispatch), this->mGoal, lNewBoard, SIMULATIONS_PER_MOVE / lMoves.size()).detach();//Dispatch Simulation on new thread
	}
	std::cout << "Simulations Per Thread: " << SIMULATIONS_PER_MOVE / lMoves.size() << " | ";
	int lMaxIndex = 0;
	int lMaxValue = -1;
	const uint32_t lResultsSize = lResults.size();
	for(uint32_t i = 0; i < lResultsSize; i++){
		const int lTemp = lResults[i].get();
		if(lTemp > lMaxValue){
			lMaxValue = lTemp;
			lMaxIndex = i;
		}
	}
	return lMoves[lMaxIndex];
}