#ifndef BOARD_HPP
#define BOARD_HPP

#ifdef _BENCHMARK_
#include "Profiler.hpp"
#endif

#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


#include "Point.hpp"
#include "BoardBoundsException.hpp"

class Board{
public:
    enum VALUE {EMPTY, WHITE, BLACK};
    enum STATE {EVEN, ODD};
private:
    std::unordered_map<Point, VALUE, PointHasher> mBoard;
public:
	Board(void);
	VALUE  at(int px, int py) const;
	VALUE& at(int px, int py);
	VALUE  operator[](const Point& p) const;
	VALUE& operator[](const Point& p);
	std::vector<Point> getNeighboursOfSameColour(const Point& p) const;
	static std::vector<Point> getNeighbours(const Point& p);
	std::vector<Point> freeSpaces(void) const;
	STATE boardState(void) const;
	int bfs(const Point&, std::unordered_set<Point, PointHasher>&) const;
	friend std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
};

std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
#endif
