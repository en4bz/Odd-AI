#include "PreemptiveMC.hpp"

MCP2::MCP2(int pID) : Player(pID) {}

Move MCP2::move(void){
	std::atomic<int> lLowerBound(std::numeric_limits<int>::max());
	const std::vector<Move>& lMoves = this->mCurrentState.validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
		std::packaged_task<int(Board::STATE,Board,int,std::atomic<int>&)> lDispatch(&MCP2::simulation);//Create Task
		lResults.emplace_back(lDispatch.get_future());//Get Future
		Board lNewBoard = this->mCurrentState;//Copy Board
		lNewBoard.update(m);//Mutate Board
		std::thread(std::move(lDispatch), this->mGoal, lNewBoard, SIMULATIONS_PER_MOVE / lMoves.size(), std::ref(lLowerBound)).detach();
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

int MCP2::simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations, std::atomic<int>& pLowerBound){
	std::random_device lGen;
	int lLosses = 0;
    for(int i = 0; i < pNumSimulations; i++){
		if(lLosses > pLowerBound.load()){
			return i - lLosses;
		}
		Board lTemp = pStartState;
		if(pGoalState != lTemp.rollout(lGen()))
			lLosses++;
    }
	int lLower;
	do{
		lLower = pLowerBound.load();
	}while(lLower > lLosses && ! pLowerBound.compare_exchange_weak(lLower, lLosses));
	return pNumSimulations - lLosses;
}