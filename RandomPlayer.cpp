#include "RandomPlayer.hpp"


Point RandomPlayer::move(void){
    std::vector<Point> lMoves = this->mCurrentState.freeSpaces();
	if(lMoves.size() == 0){
		throw 33;
	}
    int lIndex = this->mRandom() % lMoves.size();
    return lMoves[lIndex];
}
