#include "Player.hpp"

int Player::roundNumber(void) const{
    return this->mRound;
}

void Player::updateBoard(const Move& v){
    this->mRound++;
    this->mCurrentState[v.place] = v.colour;
}

Board::STATE Player::evaluateBoard(void) const{
	return this->mCurrentState.boardState();
}
