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

Board::VALUE& Board::at(const Point& p){
    if(abs(p.x + p.y) > 4 || abs(p.x) > 4 || abs(p.y) > 4){
        throw BoardBoundsException(p.x, p.y);
    }
    return this->mBoard[p];
}

Board::VALUE& Board::operator[](const Point& p){
    if(abs(p.x + p.y) > 4 || abs(p.x) > 4 || abs(p.y) > 4){
        throw BoardBoundsException(p.x, p.y);
    }
    return this->mBoard[p];
}

std::vector<Point> Board::getNeighbours(const Point& p) const{
    std::vector<Point> lReturn;
	try{
        lReturn.emplace_back(Point(p.x - 1, p.y));
	}
    catch(BoardBoundsException e){}
	try{
        lReturn.emplace_back(Point(p.x, p.y - 1));
	}
    catch(BoardBoundsException e){}
	try{
        lReturn.emplace_back(Point(p.x + 1, p.y));
	}
    catch(BoardBoundsException e){}
	try{
        lReturn.emplace_back(Point(p.x, p.y + 1));
	}
    catch(BoardBoundsException e){}
	try{
        lReturn.emplace_back(Point(p.x + 1, p.y - 1));
	}
    catch(BoardBoundsException e){}
	try{
        lReturn.emplace_back(Point(p.x - 1, p.y + 1));
	}
    catch(BoardBoundsException e){}
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
//	int lBlackGroups = 0;
//	int lWhiteGroups = 0;

    std::unordered_set<Point, PointHasher> lClosed;
	std::deque<Point> lOpen;
	lOpen.emplace_back(Point(0,0));
	int i = 0;
	while( ! lOpen.empty() ){
		Point lCurrent = lOpen.front();
		lOpen.pop_front();
		lClosed.emplace(lCurrent);
		for(const Point& p : this->getNeighbours(lCurrent)){
			if(lClosed.find(p) == lClosed.end()){
				lOpen.emplace_back(p);
				lClosed.emplace(p);
				//std::cout << p << i++;
			}
		}
	}
    return STATE::ODD;
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

