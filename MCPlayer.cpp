#include "MCPlayer.hpp"

std::future<int> MCPlayer::simulateGames(){
    std::packaged_task<int(void)> lDispatch;
    return lDispatch.get_future();
}

int MCPlayer::simulationTask(){
    std::mt19937 rd(seed);
    int lWins = 0;
    for(int i = 0; i < SIMULATIONS_PER_DISPATCH; i++){

    }
}

//Push onto stack so we can mutate board.
Board::VALUE MCPlayer::simulateSingeMatch(Board initial) const{
    std::vector<Point> lMoves;
    while((lMoves = initial.freeSpaces()).size() > 0)){
        int index = rd() % lMoves.size();//Not Valid
        Point p = lMoves[index];
        Board[p] =  (rd() % 2) ? Board::BLACK : Board::WHITE;
    }
    return initial.boardState();
}
