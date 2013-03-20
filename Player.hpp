#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Move.hpp"
#include "Point.hpp"
#include "Board.hpp"

class Player{
protected:
	int mRound;
	Board mCurrentState;
public:
    int roundNumber(void) const;
    void updateBoard(const Point& newPoint, Board::VALUE);
    void updateBoard(const Move& m);
    virtual Point move(void) = 0;
};
#endif
