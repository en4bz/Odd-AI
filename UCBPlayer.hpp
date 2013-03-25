#ifndef UCBPLAYER_HPP
#define UCBPLAYER_HPP

#include <future>
#include <thread>
#include <random>
#include <ext/random>
#include <iostream>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "MCPlayer.hpp"

struct UCBNode{
	const Move move;
	double reward;
	UCBNode(const Move& pMove) : move(pMove), reward(0) {}
};

class UCBPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_DISPATCH = 10;
private:
	std::random_device mEntropy;
public:
	UCBPlayer(int);
	Move move(void);
	std::future<int> dispatchSimulation(const Move& pAction);
};
#endif
