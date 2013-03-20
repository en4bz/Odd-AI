#ifndef BOARD_HPP
#define BOARD_HPP

#include <list>
#include <deque>
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
    VALUE& at(int px, int py);
    VALUE& at(const Point& p);
    VALUE& operator[](const Point& p);
    std::vector<Point> getNeighboursOfColour(const Point& p, VALUE colour);
    std::vector<Point> getNeighbours(const Point& p) const;
    std::vector<Point> freeSpaces(void) const;
    STATE boardState(void) const;

	friend std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
};

std::ostream& operator <<(std::ostream& pStream, const Board& pBoard);
#endif
