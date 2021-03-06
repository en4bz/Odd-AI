#ifndef PREEMPTIVE_MC_HPP
#define PREEMPTIVE_MC_HPP

#include <atomic>
#include <future>
#include <limits>
#include <thread>
#include <random>
#include <iostream>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"

class MCP2 : public Player{
public:
	static constexpr int SIMULATIONS_PER_MOVE = 50000;
public:
	MCP2(int);
	Move move(void);
	static int simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations, std::atomic<int>& pLowerBound);
};
#endif