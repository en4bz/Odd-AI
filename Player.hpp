#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Point.hpp"
#include "Board.hpp"

class Player{
protected:
	const int mID;
	const Board::STATE mGoal;
	int mRound;
	Board* const mCurrentState;
public:
	Player(int);
	Player(int, Board* const);
    int roundNumber(void) const;
    int movesLeft(void) const;
    void updateBoard(const Move&);
    virtual Move move(void) = 0;
};
#endif
