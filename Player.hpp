#ifndef PLAYER_HPP
#define PLAYER_HPP

//#include "Move.hpp"
#include "Point.hpp"
#include "Board.hpp"

class Player{
protected:
	const int mID;
	const Board::STATE mGoal;
	int mRound;
	Board mCurrentState;
public:
	Player(int);
    int roundNumber(void) const;
    int movesLeft(void) const;
    void updateBoard(const Move& m);
    virtual Move move(void) = 0;
};
#endif
