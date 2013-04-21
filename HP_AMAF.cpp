#include "HP_AMAF.hpp"

HP_AMAFPlayer::HP_AMAFPlayer(int pID) : Player(pID) {}

Move HP_AMAFPlayer::move(void){
	const std::vector<Move>& lMoves = this->mCurrentState.validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
		std::packaged_task<int(Board::STATE,Board,int)> lDispatch(&MCPlayer::simulation);//MCPlayer static method.
		lResults.emplace_back(lDispatch.get_future());
		Board lNewBoard = this->mCurrentState;
		lNewBoard.update(m);
		std::thread(std::move(lDispatch), this->mGoal, lNewBoard, SIMULATIONS_PER_MOVE / lMoves.size()).detach();
	}
	std::cout << "Simulations Per Thread: " << SIMULATIONS_PER_MOVE / lMoves.size() << " | ";
	int lMaxIndex = 0;
	int lMaxValue = -1;
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