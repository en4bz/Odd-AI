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
	static constexpr int SIMULATIONS_PER_DISPATCH = 400;
private:
	std::unordered_map<Move, int, MoveHasher> mSeen;
public:
	AMAF2(int, Board* const);
	Move move(void);
	int fetchAndUpdate(const Move&, int);
	std::future<int> dispatchSimulation(const Move& pAction, std::atomic<int>& pLowerBound);
	static int simulation(const Board pStart, const int pBoost, std::atomic<int>&, Board::STATE pState);
};
#endif