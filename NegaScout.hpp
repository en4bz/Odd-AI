#ifndef NEGASCOUT_HPP
#define NEGASCOUT_HPP

#include "Board.hpp"
#include "Player.hpp"

class NegaScout : public Player{
public:
	Move move(void);
	int negaScout(Board::STATE, int alpha, int beta, Board);
};
#endif