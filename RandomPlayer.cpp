#include "RandomPlayer.hpp"


Move RandomPlayer::move(void){
    std::vector<Point> lMoves = this->mCurrentState.freeSpaces();
	if(lMoves.size() == 0){
		throw 33;
	}
    int lIndex = this->mRandom() % lMoves.size();
    return Move(lMoves[lIndex], Board::VALUE::BLACK);
}
