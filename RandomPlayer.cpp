#include "RandomPlayer.hpp"


Move RandomPlayer::move(void){
    std::vector<Point> lMoves = this->mCurrentState.freeSpaces();
    int lIndex = this->mRandom() % lMoves.size();
    return Move(lMoves[lIndex], Board::VALUE::BLACK);
}
