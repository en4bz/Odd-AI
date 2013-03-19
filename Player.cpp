#include "Player.hpp"

void Player::updateBoard(const Point& p, Board::VALUE v){
    this->mCurrentState[p] = v;
}
