#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID) : Player(pID) {}

/*Move MCPlayer::move(void){
	const std::vector<Move>& lMoves = this->mCurrentState.validMoves();
	std::vector<int> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
//		std::packaged_task<int(Board::STATE,Board,int)> lDispatch(&MCPlayer::simulation);//Create Task
//		lResults.emplace_back(lDispatch.get_future());//Get Future
		Board lNewBoard = this->mCurrentState;//Copy Board
		lNewBoard.update(m);//Mutate Board
		int x = simulation(this->mGoal, lNewBoard, SIMULATIONS_PER_MOVE / lMoves.size());
		lResults.push_back(x);
//		std::thread(std::move(lDispatch), this->mGoal, lNewBoard, SIMULATIONS_PER_MOVE / lMoves.size()).detach();//Dispatch Simulation on new thread
	}
	#ifdef INFO
	std::cout << "Simulations Per Thread: " << SIMULATIONS_PER_MOVE / lMoves.size() << " | ";
	#endif
	int lMaxIndex = 0;
	int lMaxValue = 0;
	const uint32_t lResultsSize = lResults.size();
	for(uint32_t i = 0; i < lResultsSize; i++){
		const int lTemp = lResults[i];//.get();
		if(lTemp > lMaxValue){
			lMaxValue = lTemp;
			lMaxIndex = i;
		}
	}
	return lMoves[lMaxIndex];
}*/

Move MCPlayer::move(void){
	const std::vector<Move> lMoves = this->mCurrentState.validMoves();
	const uint32_t lThreads = THREADS < lMoves.size() ? THREADS : lMoves.size(); //std::max(THREADS , lMoves.size());
	const int lSegment = lMoves.size()/lThreads;
//	assert(lMoves.cbegin() + lThreads*lSegment == lMoves.cend());

	std::future<std::pair<Move,int>> lSplits[lThreads];
	const std::vector<Move>::const_iterator lBase = lMoves.cbegin();
	for(uint32_t i = 0; i < lThreads; i++){
		lSplits[i] = std::async(std::launch::async, split, lBase + i*lSegment, lBase + (i+1)*lSegment, this->mCurrentState, this->mGoal);
	}
	std::cout << "Rollouts: " << SIMULATIONS_PER_SPLIT / lSegment << " | ";
	int lMaxValue = 0;
	Move lMaxMove;
	for(uint32_t i = 0; i < lThreads; i++){
		const auto lTemp = lSplits[i].get();
		if(lTemp.second > lMaxValue){
			lMaxValue = lTemp.second;
			lMaxMove = lTemp.first;
		}
	}
	return lMaxMove;
}

std::pair<Move,int> MCPlayer::split(std::vector<Move>::const_iterator pStart, std::vector<Move>::const_iterator pEnd, const Board currentState, const Board::STATE pGoal){
	const int lSize = pEnd - pStart;
	int lMaxValue = 0;
	Move lMaxMove;
	for(;pStart != pEnd; pStart++){
		Board lNewBoard = currentState;//Copy Board
		lNewBoard.update(*pStart);//Mutate Board
		int x = simulation(pGoal, lNewBoard, SIMULATIONS_PER_SPLIT / lSize);
		if(x > lMaxValue){
			lMaxValue = x;
			lMaxMove = *pStart;
		}
	}
	return std::make_pair(lMaxMove,lMaxValue);
}

int MCPlayer::simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations){
	std::random_device lGen;
	int lWins = 0;
    for(int i = 0; i < pNumSimulations; i++){
		Board lTemp = pStartState;
		if(pGoalState == lTemp.rollout(lGen()))
			lWins++;
    }
	return lWins;
}