#ifndef HP_MCPLAYER_HPP
#define HP_MCPLAYER_HPP

#include <future>
#include <thread>
#include <random>
#include <iostream>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "MCPlayer.hpp"

class HP_MCPlayer : public Player{
public:
	static constexpr int SIMULATIONS_PER_MOVE = 48000;
public:
	HP_MCPlayer(int);
	Move move(void);
};
#endif
