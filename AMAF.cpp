#include "AMAF.hpp"

AMAFPlayer::AMAFPlayer(int pID, Board* const pBoard) : Player(pID, pBoard) {}

Move AMAFPlayer::move(void){
	const std::vector<Move>& lMoves = this->mCurrentState->validMoves();
	std::vector<std::future<int>> lResults;
	lResults.reserve(lMoves.size());
	for(const Move& m : lMoves){
		lResults.emplace_back(dispatchSimulation(m));
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

int AMAFPlayer::fetchAndUpdate(const Move& m, int inc){
	auto lEnd = this->mSeen.end();
	if(this->mSeen.find(m) == lEnd){
		this->mSeen.emplace(m,inc);
	}
	else{
		this->mSeen[m] += inc;
	}
	return this->mSeen[m];
}

std::future<int> AMAFPlayer::dispatchSimulation(const Move& pAction){
	std::packaged_task<int(Board::STATE,Board,int)> lDispatch(&MCPlayer::simulation);//MCPlayer static method.
	Board lNewBoard(*(this->mCurrentState));
	lNewBoard.update(pAction);
	std::future<int> lReturn = lDispatch.get_future();
	std::thread(std::move(lDispatch), this->mGoal, lNewBoard, this->mRound*5).detach();
	return lReturn;
}
