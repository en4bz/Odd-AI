#include "NegaScout.hpp"

NegaScout::NegaScout(int pID, Board* const pBoard) : Player(pID, pBoard) {}

Move NegaScout::move(void){
	std::vector<Move> lMoves = std::move(this->mCurrentState->validMoves());
	std::cout << "Moves Processed: ";
	std::vector<std::future<int>> lResults;
	int i = 0;
	for(const Move& m : lMoves){
		std::cout << ++i << " ";
		std::packaged_task<int(Board::STATE,Board)> lDispatch(&NegaScout::negaMax);
		lResults.emplace_back(lDispatch.get_future());
		Board lNewBoard = *(this->mCurrentState);
		lNewBoard.update(m);
		std::thread(std::move(lDispatch), this->mGoal, lNewBoard).detach();
	}
	int lMax = std::numeric_limits<int>::min();
	int lMaxIndex = 0;
	for(uint32_t i = 0; i < lResults.size(); i++){
		int lTemp = lResults[i].get();
		if(lTemp > lMax){
			lMax = lTemp;
			lMaxIndex = i;
		}
	}
	return lMoves[lMaxIndex];
}

int NegaScout::negaMax(Board::STATE pGoal, Board pCurrentState){
	std::vector<Move> lMoves = pCurrentState.validMoves();
	if(lMoves.size() == 2){
		int lValue = 0;
		Board lNewBoard = pCurrentState;
		lNewBoard.update(lMoves[0]);
		if(pGoal == lNewBoard.boardStateEnd())
			lValue++;
		else
			lValue--;
		pCurrentState.update(lMoves[1]);
		if(pGoal == pCurrentState.boardStateEnd())
			lValue++;
		else
			lValue--;
		return lValue;
	}
	int lSum = 0;
	for(const Move& m : lMoves){
		Board lNewBoard = pCurrentState;
		lNewBoard.update(m);
		lSum += negaMax(pGoal, lNewBoard);
	}
	return lSum;
}