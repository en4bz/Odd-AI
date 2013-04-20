#ifndef MCPLAYER_HPP
#define MCPLAYER_HPP

#define THREADS 4

#include <utility>
#include <future>
#include <thread>
#include <random>
#include <iostream>
#include <algorithm>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"

class MCPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_SPLIT = 30000;
public:
	MCPlayer(int);
	Move move(void);
	static std::pair<Move,int> split(std::vector<Move>::const_iterator pStart, std::vector<Move>::const_iterator pEnd, const Board, const Board::STATE);
	static int simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations);
};
#endif
