#ifndef MCPLAYER_HPP
#define MCPLAYER_HPP

#include <future>
#include <thread>
#include <random>

#include "Board.hpp"

class MCPlayer : Player{
public:
    static int SIMULATIONS_PER_DISPATCH = 1000;
    std::future<int> simulateGames(const Board& initialState, VALUE winningState, long seed);
    Board::VALUE simulateSingleMatch(Board initial) const;
};

#endif
