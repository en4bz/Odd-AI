#ifndef RANDOMPLAYER_HPP
#define RANDOMPLAYER_HPP
#include <random>

#include "Point.hpp"
#include "Player.hpp"

class RandomPlayer : public Player{
private:
	std::mt19937 mRandom;
public:
    Point move(void);
};
#endif
