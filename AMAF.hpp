#ifndef AMAF_HPP
#define AMAF_HPP

#include <future>
#include <thread>
#include <random>
#include <iostream>
#include <unordered_map>

#include "Point.hpp"
#include "Board.hpp"
#include "Profiler.hpp"
#include "Player.hpp"
#include "MCPlayer.hpp"

class AMAFPlayer : public Player{
public:
	static constexpr int MOVES_TO_PLAY_AMAF = 40;
	static constexpr int SIMULATIONS_PER_MOVE = 45000;
private:
	std::unordered_map<Move, int, MoveHasher> mSeen;
public:
	AMAFPlayer(int, Board* const);
	Move move(void);
	int fetchAndUpdate(const Move&, int);
};
#endif
