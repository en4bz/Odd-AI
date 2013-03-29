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
	for(uint32_t i = 0; i < lResults.size(); i++){
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
				std::cout << "Can't win with move: " << lMoves[i].place << std::endl;
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
	std::packaged_task<int(Board::STATE,int,Board,int)> lDispatch(AMAFPlayer::simulation);
	Board lNewBoard(*(this->mCurrentState));
	lNewBoard.update(pAction);
	std::future<int> lReturn = lDispatch.get_future();
	std::thread(std::move(lDispatch), this->mGoal, this->mEntropy(), lNewBoard, 0/* this->mRound*5*/).detach();
	return lReturn;
}

int AMAFPlayer::simulation(const Board::STATE pGoal, int pSeed, Board pStart, int boost){
	__gnu_cxx::sfmt607 lGen(pSeed);
	std::uniform_int_distribution<int> lSelector(0,1);
//	std::mt19937 lGen(seed);
	int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH + boost; i++){
		if(pGoal == AMAFPlayer::simulateMatch(pStart, lGen, lSelector)){
			lWins++;
		}
    }
	#ifdef _DEBUG_
	std::cout << "Completed Simulation" << std::endl;
	#endif
	return lWins;
}

//Push onto stack so we can mutate board.
Board::STATE AMAFPlayer::simulateMatch(Board initial, __gnu_cxx::sfmt607& pRandom, std::uniform_int_distribution<int>& pSelector){
	std::vector<Point> lMoves;
	while((lMoves = (initial.freeSpaces())).size() > 0){
		const Point& p = lMoves[pRandom() % lMoves.size()];//Not Uniform?
		initial.update(p, pSelector(pRandom) == 0 ? Board::BLACK : Board::WHITE);
	}
	return initial.boardStateEnd();//We know there are no free spaces at this point.
}
