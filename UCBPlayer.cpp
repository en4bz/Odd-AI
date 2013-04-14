#include "UCBPlayer.hpp"

UCBPlayer::UCBPlayer(int pID, Board* const pBoard) : Player(pID, pBoard) {}

Move UCBPlayer::move(void){
//	std::vector<UCBNode> lNodes;
	boost::heap::fibonacci_heap<UCBNode> lNodes
	std::vector<std::future<int>> lResults;
	for(const Move& m : this->mCurrentState->validMoves()){
		lNodes.emplace_back(UCBNode(m));
		lResults.emplace_back(dispatchSimulation(m));
	}
	return Move(Point(0,0),Board::VALUE::WHITE);
}

std::future<int> UCBPlayer::dispatchSimulation(const Move& pAction){
	std::packaged_task<int(Board::STATE,Board)> lDispatch(&MCPlayer::simulation);
	Board lNewBoard = *(this->mCurrentState);
	lNewBoard.update(pAction.place, pAction.colour);
	#ifdef _DEBUG_
	std::cout << "Dispatching " << std::endl;
	#endif
	std::future<int> lReturn = lDispatch.get_future();
	std::thread(std::move(lDispatch), this->mGoal, lNewBoard).detach();
	return lReturn;
}