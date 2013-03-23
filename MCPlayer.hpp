#ifndef MCPLAYER_HPP
#define MCPLAYER_HPP

#include <future>
#include <thread>
#include <random>
#include <ext/random>
#include <iostream>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"

class MCPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_DISPATCH = 150;
private:
	std::random_device mEntropy;
public:
	MCPlayer(int);
	Move move(void);
	std::future<int> dispatchSimulation(const Move& pAction);
	static int simulation(int pID, int pSeed, Board b);
	static Board::STATE simulateMatch(Board initial, __gnu_cxx::sfmt607&, std::uniform_int_distribution<int>& );
};
#endif
