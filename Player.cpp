#include "Player.hpp"

Player::Player(int pID) : mID(pID), mGoal(pID == 1 ? Board::STATE::ODD : Board::STATE::EVEN) {}

int Player::roundNumber(void) const{
	return this->mRound;
}

int Player::movesLeft(void) const{
	return 61 - this->mRound;
}

void Player::updateBoard(const Move& v){
    this->mRound++;
    this->mCurrentState.update(v);
}