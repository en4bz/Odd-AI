#ifndef BOARD_HPP
#define BOARD_HPP

#ifdef _BENCHMARK_
#include "Profiler.hpp"
#endif

#include <cassert>
#include <queue>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>

#include "Point.hpp"
#include "BoardBoundsException.hpp"

struct Move;

class Board{
public:
    enum VALUE {EMPTY, WHITE, BLACK};
    enum STATE {EVEN, ODD};
private:
    std::unordered_map<Point, VALUE, PointHasher> mBoard;
public:
	Board(void);
	void update(const Move&);
	void update(const Point&, VALUE);
	std::vector<Point> getNeighboursOfSameColour(const Point& p) const;
	static std::vector<Point> getNeighbours(const Point& p);
	std::vector<Point> freeSpaces(void) const;
	std::vector<Move> samplePath(int) const;
	std::vector<Move> validMoves(void) const;
	STATE boardState(void) const;
	STATE boardStateEnd(void) const;//Only use when we know there are no free spaces left, saves call to freeSpaces()
	int connectedComponent(const Point&, std::unordered_set<Point, PointHasher>&) const;
	int load(void) const;
	friend std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
};

std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);

struct Move{
	Point place;
	Board::VALUE colour;
	Move(const Point& p, Board::VALUE v) : place(p), colour(v) {}
	bool operator==(const Move& m) const{ return this->place == m.place && this->colour == m.colour;}
	bool operator!=(const Move& m) const{ return this->place != m.place || this->colour != m.colour;}
};

struct MoveHasher{
	size_t operator()(const Move& m) const{
		return (m.place.y ^ (m.place.x << 4)) + m.colour * 5;
	}
};
#endif