#ifndef MCPLAYER_HPP
#define MCPLAYER_HPP

#include <future>
#include <thread>
#include <random>
#include <iostream>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"

class MCPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_MOVE = 48000;
public:
	MCPlayer(int);
	Move move(void);
	static int simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations);
};
#endif
