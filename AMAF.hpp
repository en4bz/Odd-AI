#ifndef AMAF_HPP
#define AMAF_HPP

#include <future>
#include <thread>
#include <random>
#include <ext/random>
#include <iostream>
#include <unordered_map>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"

class AMAFPlayer : public Player{
public:
	static constexpr int MOVES_TO_PLAY_AMAF = 45;
	static constexpr int SIMULATIONS_PER_DISPATCH = 160;
private:
	std::random_device mEntropy;
	std::unordered_map<Move, int, MoveHasher> mSeen;
public:
	AMAFPlayer(int, Board* const);
	Move move(void);
	std::future<int> dispatchSimulation(const Move& pAction);
	int fetchAndUpdate(const Move&,int);
	static int simulation(const Board::STATE pGoal, int pSeed, Board b, int);
	static Board::STATE simulateMatch(Board initial, __gnu_cxx::sfmt607&, std::uniform_int_distribution<int>& );
};
#endif
