#include "RandomPlayer.hpp"


Point RandomPlayer::move(void){
    std::vector<Point> lMoves = this->mCurrentState.freeSpaces();
    int lIndex = this->mRandom() % lMoves.size();
    return lMoves[lIndex];
}
