#ifndef MCPLAYER_HPP
#define MCPLAYER_HPP

#include <future>
#include <thread>
#include <random>
#include <iostream>

#include "Player.hpp"
#include "Point.hpp"
#include "Board.hpp"

class MCPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_DISPATCH = 10;
private:
	std::random_device mEntropy;
public:
	MCPlayer(int);
	Move move(void);
	std::future<int> dispatchSimulation(const Move& pAction);
	static int simulation(int pID, int pSeed, Board b);
	static Board::STATE simulateMatch(Board initial, std::mt19937&);
};
#endif
