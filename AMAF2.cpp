#include "AMAF2.hpp"

AMAF2::AMAF2(int pID) : Player(pID) {}

Move AMAF2::move(void){
	std::atomic<int> lLowerBound(std::numeric_limits<int>::max());//Set Lower Bound to infinity.
	const std::vector<Move>& lMoves = this->mCurrentState.validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){//Dispatch Simulations
		Board lNewBoard = this->mCurrentState;
		lNewBoard.update(m);
		std::packaged_task<int(Board::STATE,Board,int,std::atomic<int>&)> lDispatch(&AMAF2::simulation);
		lResults.emplace_back(lDispatch.get_future());
		std::thread(std::move(lDispatch), this->mGoal, lNewBoard, SIMULATIONS_PER_MOVE / lMoves.size(), std::ref(lLowerBound)).detach();
	}
	std::cout << "Simulations Per Thread: " << SIMULATIONS_PER_MOVE / lMoves.size() << " | ";
	int lMaxIndex = 0;
	int lMaxValue = 0;
	const uint32_t lFutureSize = lResults.size();
	for(uint32_t i = 0; i < lFutureSize; i++){
		if(this->movesLeft() >= MOVES_TO_PLAY_AMAF){
			this->mSeen[lMoves[i]] += lResults[i].get();
			const int lTemp = this->mSeen[lMoves[i]];
			if(lTemp > lMaxValue){
				lMaxValue = lTemp;
				lMaxIndex = i;
			}
		}
		else{
			const int lTemp = lResults[i].get();
			if(lTemp == 0){
				std::cout << "Can't win with move: " << lMoves[i] << std::endl;
			}
			if(lTemp > lMaxValue){
				lMaxValue = lTemp;
				lMaxIndex = i;
			}
		}
	}
	return lMoves[lMaxIndex];
}

int AMAF2::simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations, std::atomic<int>& pLowerBound){
	std::random_device lGen;
	int lWins = 0;
	int lLosses = 0;
    for(int i = 0; i < pNumSimulations; i++){
		if(lLosses > pLowerBound.load()){
			return lWins;
		}
		Board lTemp = pStartState;
		if(pGoalState == lTemp.sim(lGen()))
			lWins++;
		else
			lLosses++;
    }
	int lLower;
	do{
		lLower = pLowerBound.load();
	}while(lLower > lLosses && pLowerBound.compare_exchange_strong(lLower, lLosses));
	return lWins;
}
