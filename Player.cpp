#include "Player.hpp"

int Player::roundNumber(void) const{
    return this->mRound;
}

void Player::updateBoard(const Move& v){
    this->mRound++;
    this->mCurrentState[v.place] = v.colour;
}

void Player::updateBoard(const Point& p, Board::VALUE v){
    this->mRound++;
    this->mCurrentState[p] = v;
}
