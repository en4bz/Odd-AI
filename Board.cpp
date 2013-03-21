#include "Board.hpp"

Board::Board(void){
	this->mBoard.reserve(61);
	for(int i = -4; i <= 4; i++){
		for(int j = -4; j <= 4; j++){
            if(abs(i + j) > 4 || abs(i) > 4 || abs(j) > 4)
				continue;
			else{
                this->mBoard.emplace(Point(i,j), Board::EMPTY);
			}
		}
	}
}

Board::VALUE& Board::at(int px, int py){
    if(abs(px + py) > 4 || abs(px) > 4 || abs(py) > 4){
        throw BoardBoundsException(px, py);
    }
    return this->mBoard[Point(px,py)];
}

Board::VALUE Board::at(int px, int py) const{
    if(abs(px + py) > 4 || abs(px) > 4 || abs(py) > 4){
        throw BoardBoundsException(px, py);
    }
    return (*this)[Point(px,py)];
}

Board::VALUE& Board::operator[](const Point& p){
    if(abs(p.x + p.y) > 4 || abs(p.x) > 4 || abs(p.y) > 4){
        throw BoardBoundsException(p.x, p.y);
    }
    return this->mBoard[p];
}

Board::VALUE Board::operator[](const Point& p) const{
    if(abs(p.x + p.y) > 4 || abs(p.x) > 4 || abs(p.y) > 4){
        throw BoardBoundsException(p.x, p.y);
    }
    return this->mBoard.find(p)->second;
}


std::vector<Point> Board::getNeighboursOfSameColour(const Point& p) const{
	const VALUE lColour= (*this)[p];
	std::vector<Point> lNeighbours = this->getNeighbours(p);
	auto lNewEnd = std::remove_if(lNeighbours.begin(), lNeighbours.end(), [this, &lColour](Point a){return !((*this)[a] == lColour);});
	lNeighbours.erase(lNewEnd, lNeighbours.end());
	return lNeighbours;
}

std::vector<Point> Board::getNeighbours(const Point& p){
    std::vector<Point> lReturn;
    if( abs(p.x - 1 + p.y) <= 4 && abs(p.x - 1) <= 4 && abs(p.y) <= 4)
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
    #ifdef _DEBUG_
    std::cout << "# of Neigbours for " << p << " = " lReturn.size() << std::endl;
    #endif
    return lReturn;
}


std::vector<Point> Board::freeSpaces(void) const{
    std::vector<Point> lFree;
    for(auto& kv : this->mBoard){
        if(kv.second == VALUE::EMPTY)
            lFree.emplace_back(kv.first);
    }
	return lFree;
}

Board::STATE Board::boardState(void) const{
	#ifdef _BENCHMARK_
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	#endif
	int lBlackGroups = 0;
	int lWhiteGroups = 0;
   	std::unordered_set<Point, PointHasher> lClosed;
	std::vector<Point> lFree = this->freeSpaces();
	lClosed.insert(lFree.begin(), lFree.end());
	for(int i = -4; i <= 4; i++){
		for(int j = -4; j <= 4; j++){
	        	if(abs(i + j) > 4 || abs(i) > 4 || abs(j) > 4){
				continue;
			}
			Point lCurrent (i,j);
			if(lClosed.find(lCurrent) != lClosed.end()){
				continue;
			}
			else{
				int lSize = bfs(lCurrent, lClosed);
				if(lSize >= 5){
					((*this)[lCurrent] == VALUE::BLACK) ? lBlackGroups++ : lWhiteGroups++;
				}
			}
		}
	}
	#ifdef _BENCHMARK_
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::cout << "boardState(void) Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << std::endl;
	#endif

	return (lBlackGroups + lWhiteGroups) % 2 ? STATE::ODD : STATE::EVEN;
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
		for(Point& p : getNeighboursOfSameColour(lCurrent)){
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

