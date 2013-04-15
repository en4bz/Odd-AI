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
	static constexpr int SIMULATIONS_PER_DISPATCH = 384;
public:
	MCPlayer(int, Board* const);
	Move move(void);
	std::future<int> dispatchSimulation(const Move& pAction);
	static int simulation(const Board::STATE pGoal, const Board pStart, const int pBoost);
};
#endif
