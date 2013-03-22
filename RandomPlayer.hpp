#ifndef RANDOMPLAYER_HPP
#define RANDOMPLAYER_HPP
#include <random>

#include "Point.hpp"
#include "Player.hpp"

class RandomPlayer : public Player{
private:
	std::mt19937 mRandom;
	std::uniform_int_distribution<int> mColour;
public:
	RandomPlayer(int pID);
   	Move move(void);
};
#endif
