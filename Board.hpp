#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <queue>
#include <vector>
#include <random>
#include <cassert>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "Point.hpp"

struct Move;

class Board{
public:
    enum VALUE {WHITE, BLACK};
    enum STATE {EVEN, ODD};
private:
	std::unordered_map<Point, VALUE, PointHasher> mBoard;
//	std::map<Point,VALUE> mBoard;
public:
	void update(const Move&);
	std::vector<Point> getNeighboursOfSameColour(const Point& p) const;
	std::vector<Point> freeSpaces(void) const;
	std::vector<Move> validMoves(void) const;
	STATE boardState(void) const;
	STATE boardStateEnd(void) const;//Only use when we know there are no free spaces left, saves call to freeSpaces()
	STATE rollout(int pSeed);
	int connectedComponent(const Point&, std::unordered_set<Point, PointHasher>&) const;
	friend std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
};

std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
std::ostream& operator <<(std::ostream& pStream, const Move& pBoard);

struct Move{
	Point place;
	Board::VALUE colour;
	Move(const Point& p = Point(0,0), Board::VALUE v = Board::VALUE::WHITE) : place(p), colour(v) {}
	bool operator==(const Move& m) const{ return this->place == m.place && this->colour == m.colour;}
	bool operator!=(const Move& m) const{ return this->place != m.place || this->colour != m.colour;}
};

struct MoveHasher{
	size_t operator()(const Move& m) const{
		return (m.place.y ^ (m.place.x << 4)) + m.colour * 5;
	}
};
#endif