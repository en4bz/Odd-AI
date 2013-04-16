#include "AMAF2.hpp"

AMAF2::AMAF2(int pID, Board* const pBoard) : Player(pID, pBoard) {}

Move AMAF2::move(void){
	std::atomic<int> lLowerBound(std::numeric_limits<int>::max());
	const std::vector<Move>& lMoves = this->mCurrentState->validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
		Board lNewBoard = *(this->mCurrentState);
		lNewBoard.update(m);
		std::packaged_task<int(Board,int,std::atomic<int>&,Board::STATE)> lDispatch(&AMAF2::simulation);
		lResults.emplace_back(lDispatch.get_future());
		std::thread(std::move(lDispatch), lNewBoard, this->mRound*5, std::ref(lLowerBound), this->mGoal).detach();
	}
	int lMaxIndex = 0;
	int lMaxValue = 0;
	const uint32_t lFutureSize = lResults.size();
	for(uint32_t i = 0; i < lFutureSize; i++){
		if(this->movesLeft() >= MOVES_TO_PLAY_AMAF){
			const int lTemp = this->fetchAndUpdate(lMoves[i], lResults[i].get());
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

int AMAF2::fetchAndUpdate(const Move& m, int inc){
	auto lEnd = this->mSeen.end();
	if(this->mSeen.find(m) == lEnd){
		this->mSeen.emplace(m,inc);

	}
	else{
		this->mSeen[m] += inc;
	}
	return this->mSeen[m];
}

std::future<int> AMAF2::dispatchSimulation(const Move& pAction, std::atomic<int>& pLowerBound){
//	std::packaged_task<int(Board,int,std::atomic<int>&,Board::STATE)> lDispatch(&AMAF2::simulation);
	Board lNewBoard = *(this->mCurrentState);
	lNewBoard.update(pAction);
//	std::future<int> lReturn = lDispatch.get_future();
//	std::thread(std::move(lDispatch), lNewBoard, this->mRound*5, std::ref(pLowerBound), this->mGoal).detach();
//	return lReturn;
	return std::async(std::launch::async, &AMAF2::simulation, lNewBoard, this->mRound*5, std::ref(pLowerBound), this->mGoal);

}

int AMAF2::simulation(const Board pStart, const int pBoost, std::atomic<int>& pLowerBound, const Board::STATE pGoal){
	std::random_device lGen;
	int lWins = 0;
	int lLosses = 0;
    for(int i = 0; i < AMAF2::SIMULATIONS_PER_DISPATCH + pBoost; i++){
		if(lLosses > pLowerBound.load()){
			return lWins;
		}
		Board lTemp = pStart;
		for(const Move& m : lTemp.samplePath(lGen()))
			lTemp.update(m);
		if(pGoal == lTemp.boardStateEnd())
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
