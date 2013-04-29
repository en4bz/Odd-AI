#include "MCPlayer.hpp"

MCPlayer::MCPlayer(int pID) : Player(pID) {}

Move MCPlayer::move(void){
	const std::vector<Move> lMoves = this->mCurrentState.validMoves();
	const int lThreads = THREADS < lMoves.size() ? THREADS : lMoves.size();
	const int lSegment = lMoves.size()/lThreads;

	assert(lMoves.cbegin() + lThreads*lSegment == lMoves.cend());
	std::future<std::pair<Move,int>> lSplits[lThreads];
	const std::vector<Move>::const_iterator lBase = lMoves.cbegin();
	int i = 0;
	for(; i < lThreads-1; i++){
		//Lauch on new thread
		lSplits[i] = std::async(std::launch::async, split, lBase + i*lSegment, lBase + (i+1)*lSegment, this->mCurrentState, this->mGoal);
	}
	lSplits[i] = std::async(std::launch::async, split, lBase + i*lSegment, lMoves.cend(), this->mCurrentState, this->mGoal);
	std::cout << "Rollouts: " << SIMULATIONS_PER_SPLIT / lSegment << " | ";
	int lMaxValue = -1;
	Move lMaxMove;
	for(int i = 0; i < lThreads; i++){
		const auto lTemp = lSplits[i].get();
		if(lTemp.second > lMaxValue){
			lMaxValue = lTemp.second;
			lMaxMove = lTemp.first;
		}
	}
	return lMaxMove;
}

std::pair<Move,int> MCPlayer::split(std::vector<Move>::const_iterator pStart, std::vector<Move>::const_iterator pEnd, const Board currentState, const Board::STATE pGoal){
	const int lSize = distance(pStart,pEnd);
	int lMaxValue = -1;
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