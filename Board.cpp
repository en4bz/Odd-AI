#include "Board.hpp"

void Board::update(const Move& pNewMove){
	this->mBoard[pNewMove.place] = pNewMove.colour;
}

void Board::update(const Point& pPlace, VALUE pColour){
	this->mBoard[pPlace] = pColour;
}

std::vector<Point> Board::getNeighboursOfSameColour(const Point& p) const{
	/*Possible Optimization:
		Since we never insert out of bounds elements we can assume
		that we don't need to check the bounds. Then we can just
		call find on the element.
	*/
    std::vector<Point> lReturn;
	const VALUE lColour = this->mBoard.find(p)->second;
	if(abs(p.x - 1 + p.y) <= 4 && abs(p.x - 1) <= 4 && abs(p.y) <= 4)
		if(this->mBoard.find(Point(p.x - 1, p.y))->second == lColour)
	        lReturn.emplace_back(Point(p.x - 1, p.y));
	if(abs(p.x + p.y - 1) <= 4 && abs(p.x) <= 4 && abs(p.y - 1) <= 4)
		if(this->mBoard.find(Point(p.x, p.y - 1))->second == lColour)
	        lReturn.emplace_back(Point(p.x, p.y - 1));
	if(abs(p.x + 1 + p.y) <= 4 && abs(p.x + 1) <= 4 && abs(p.y) <= 4)
		if(this->mBoard.find(Point(p.x + 1, p.y))->second == lColour)
	        lReturn.emplace_back(Point(p.x + 1, p.y));
	if(abs(p.x + p.y + 1) <= 4 && abs(p.x) <= 4 && abs(p.y + 1) <= 4)
		if(this->mBoard.find(Point(p.x, p.y + 1))->second  == lColour)
	        lReturn.emplace_back(Point(p.x, p.y + 1));
	if(abs(p.x + p.y) <= 4 && abs(p.x + 1) <= 4 && abs(p.y - 1) <= 4)
		if(this->mBoard.find(Point(p.x + 1, p.y - 1))->second == lColour)
	        lReturn.emplace_back(Point(p.x + 1, p.y - 1));
	if(abs(p.x + p.y) <= 4 && abs(p.x - 1) <= 4 && abs(p.y + 1) <= 4)
		if(this->mBoard.find(Point(p.x - 1, p.y + 1))->second == lColour)
	        lReturn.emplace_back(Point(p.x - 1, p.y + 1));
    return lReturn;
}

std::vector<Point> Board::getNeighbours(const Point& p){
    std::vector<Point> lReturn;
    if(abs(p.x - 1 + p.y) <= 4 && abs(p.x - 1) <= 4 && abs(p.y) <= 4)
        lReturn.emplace_back(Point(p.x - 1, p.y));
    if(abs(p.x + p.y - 1) <= 4 && abs(p.x) <= 4 && abs(p.y - 1) <= 4)
        lReturn.emplace_back(Point(p.x, p.y - 1));
    if(abs(p.x + 1 + p.y) <= 4 && abs(p.x + 1) <= 4 && abs(p.y) <= 4)
        lReturn.emplace_back(Point(p.x + 1, p.y));
    if(abs(p.x + p.y + 1) <= 4 && abs(p.x) <= 4 && abs(p.y + 1) <= 4)
        lReturn.emplace_back(Point(p.x, p.y + 1));
    if(abs(p.x + p.y) <= 4 && abs(p.x + 1) <= 4 && abs(p.y - 1) <= 4)
        lReturn.emplace_back(Point(p.x + 1, p.y - 1));
    if(abs(p.x + p.y) <= 4 && abs(p.x - 1) <= 4 && abs(p.y + 1) <= 4)
        lReturn.emplace_back(Point(p.x - 1, p.y + 1));
    return lReturn;
}


std::vector<Point> Board::freeSpaces(void) const{
    std::vector<Point> lFree;
    for(int i = -4; i <= 4; i++){
        for(int j = -4; j <= 4; j++){
			if(abs(i + j) > 4 || abs(i) > 4 || abs(j) > 4){
                continue;
            }
			Point p = Point(i,j);
			if(this->mBoard.find(p) == this->mBoard.end()){
				lFree.emplace_back(p);
			}
		}
    }
	return lFree;
}

std::vector<Move> Board::validMoves(void) const{
    std::vector<Move> lMoves;
    for(int i = -4; i <= 4; i++){
        for(int j = -4; j <= 4; j++){
			if(abs(i + j) > 4 || abs(i) > 4 || abs(j) > 4){
                continue;
            }
			Point p = Point(i,j);
			if(this->mBoard.find(p) == this->mBoard.end()){
				lMoves.emplace_back(Move(p, VALUE::BLACK));
				lMoves.emplace_back(Move(p, VALUE::WHITE));
			}
		}
    }
	return lMoves;
}

Board::STATE Board::boardStateEnd(void) const{
    #ifdef _BENCHMARK_
    Profiler lTimer("boardStateEnd(void): ");
    #endif
    int lBlackGroups = 0;
    int lWhiteGroups = 0;
    std::unordered_set<Point, PointHasher> lClosed;
	for(const auto& kv : this->mBoard){
		if(lClosed.find(kv.first) != lClosed.end()){
			continue;
		}
		else{
			int lSize = bfs(kv.first, lClosed);
			if(lSize >= 5){
				(kv.second == VALUE::BLACK) ? lBlackGroups++ : lWhiteGroups++;
			}
		}
    }
    #ifdef _BENCHMARK_
    std::cout << lTimer << std::endl;
    #endif
    return (lBlackGroups + lWhiteGroups) & 0x00000001 ? STATE::ODD : STATE::EVEN;
}

Board::STATE Board::boardState(void) const{
	#ifdef _BENCHMARK_
	Profiler lTimer("boardState(void): ");
	#endif
    int lBlackGroups = 0;
    int lWhiteGroups = 0;
   	std::unordered_set<Point, PointHasher> lClosed;
	std::vector<Point> lFree = this->freeSpaces();
	lClosed.insert(lFree.begin(), lFree.end());
    for(const auto& kv : this->mBoard){
        if(lClosed.find(kv.first) != lClosed.end()){
            continue;
        }
        else{
            int lSize = bfs(kv.first, lClosed);
            if(lSize >= 5){
                (kv.second == VALUE::BLACK) ? lBlackGroups++ : lWhiteGroups++;
            }
        }
    }
    #ifdef _BENCHMARK_
    std::cout << lTimer << std::endl;
    #endif
    return (lBlackGroups + lWhiteGroups) & 0x00000001 ? STATE::ODD : STATE::EVEN;
}

int Board::bfs(const Point& origin, std::unordered_set<Point, PointHasher>& pClosed) const{
	int lSize = 0;
	std::queue<Point> lOpen;
	lOpen.push(origin);
	while(! lOpen.empty()){
		lSize++;
		Point lCurrent = lOpen.front();
		lOpen.pop();
		pClosed.insert(lCurrent);
		for(const Point& p : getNeighboursOfSameColour(lCurrent)){
			if(pClosed.find(p) == pClosed.end()){
				lOpen.push(p);
				pClosed.insert(p);
			}
		}
	}
	return lSize;
}

std::ostream& operator<< (std::ostream& pStream, const Board& pBoard){
    for(int i = -4; i <= 4; i++){
        for(int j = -4; j <= 4; j++){
            if(abs(i + j) > 4 || abs(i) > 4 || abs(j) > 4)
                std::cout << "(X,X)";
            else{
                std::cout << Point(i,j);
            }
        }
        std::cout << std::endl;
    }
	return pStream;
}