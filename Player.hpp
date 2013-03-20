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
    void updateBoard(const Move& m);
    virtual Move move(void) = 0;
};
#endif
