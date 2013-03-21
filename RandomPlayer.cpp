#include "RandomPlayer.hpp"

RandomPlayer::RandomPlayer(){
	this->mColour = std::uniform_int_distribution<int>(0,1);
}

Move RandomPlayer::move(void){
    	std::vector<Point> lMoves = this->mCurrentState.freeSpaces();
    	int lIndex = this->mRandom() % lMoves.size();
    	if(mColour(this->mRandom)){
    		return Move(lMoves[lIndex], Board::VALUE::BLACK);
	}
    	else{
    		return Move(lMoves[lIndex], Board::VALUE::WHITE);
	}
}
