#ifndef MCP2_HPP
#define MCP2_HPP

#include <atomic>
#include <future>
#include <limits>
#include <thread>
#include <random>
#include <iostream>

#include "AMAF2.hpp"
#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"

class MCP2 : public Player{
public:
	static constexpr int SIMULATIONS_PER_MOVE = 50000;
public:
	MCP2(int);
	Move move(void);
};
#endif