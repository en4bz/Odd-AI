#ifndef NEGASCOUT_HPP
#define NEGASCOUT_HPP

#include <limits>
#include <thread>
#include <future>
#include <iostream>

#include "Board.hpp"
#include "Player.hpp"

class NegaScout : public Player{
public:
	NegaScout(int, Board* const);
	Move move(void);
	static int negaMax(Board::STATE, Board);
};
#endif