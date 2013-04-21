#ifndef AMAFPLAYER_HPP
#define AMAFPLAYER_HPP

#include <future>
#include <thread>
#include <random>
#include <utility>
#include <iostream>

#include <tbb/concurrent_hash_map.h>

#include "Board.hpp"
#include "Player.hpp"
#include "MCPlayer.hpp"

class AMAFPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_SPLIT = 30000;
public:
	AMAFPlayer(int);
	Move move(void);
	static std::pair<Move,int> split(std::vector<Move>::const_iterator pStart, std::vector<Move>::const_iterator pEnd, const Board, const Board::STATE);
	static int simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations);
};
#endif
