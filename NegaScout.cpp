#include "NegaScout.hpp"

Move NegaScout::move(void){
	return Move(Point(0,0),Board::VALUE::BLACK);
}

int NegaScout::negaScout(Board::STATE pGoal, int alpha, int beta, Board pCurrentState){
	std::vector<Move> lMoves = pCurrentState.validMoves();
	if(lMoves.size() == 0){
		return (pGoal == pCurrentState.boardStateEnd()) ? 1 : -1;
	}
	for(const Move& m : lMoves){
		Board lNew = pCurrentState;
		lNew.update(m);
//		int value = negaScout(! pMaxPlayer, -alpha, -beta, lNew);
	}

	return 0;
}