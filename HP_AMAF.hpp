#ifndef HP_AMAF_HPP
#define HP_AMAF_HPP

#include <future>
#include <thread>
#include <random>
#include <iostream>
#include <unordered_map>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "MCPlayer.hpp"

class HP_AMAFPlayer : public Player{
public:
	static constexpr int MOVES_TO_PLAY_AMAF = 40;
	static constexpr int SIMULATIONS_PER_MOVE = 48000;
private:
	std::unordered_map<Move, int, MoveHasher> mSeen;
public:
	HP_AMAFPlayer(int);
	Move move(void);
};
#endif
