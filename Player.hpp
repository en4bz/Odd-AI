#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Point.hpp"
#include "Board.hpp"

class Player{
protected:
	Board mCurrentState;
public:
    void updateBoard(const Point& newPoint, Board::VALUE);
    virtual Point move(void) = 0;
};
#endif
