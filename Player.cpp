#include "Player.hpp"

Player::Player(int pID) : mID(pID) {}

int Player::roundNumber(void) const{
	return this->mRound;
}

int Player::movesLeft(void) const{
	return 61 - this->mRound;
}

void Player::updateBoard(const Move& v){
    this->mRound++;
    this->mCurrentState[v.place] = v.colour;
}

Board::STATE Player::evaluateBoard(void) const{
	return this->mCurrentState.boardState();
}
