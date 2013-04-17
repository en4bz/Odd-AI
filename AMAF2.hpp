#ifndef AMAF2_HPP
#define AMAF2_HPP

#include <atomic>
#include <future>
#include <thread>
#include <random>
#include <limits>
#include <iostream>
#include <unordered_map>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Profiler.hpp"

class AMAF2 : public Player{
public:
	static constexpr int MOVES_TO_PLAY_AMAF = 40;
	static constexpr int SIMULATIONS_PER_MOVE = 48000;
private:
	std::unordered_map<Move, int, MoveHasher> mSeen;
public:
	AMAF2(int, Board* const);
	Move move(void);
	int fetchAndUpdate(const Move&, int);
	static int simulation(const Board::STATE pGoalState, const Board pStartState, const int pNumSimulations, std::atomic<int>& pLowerBound);
};
#endif