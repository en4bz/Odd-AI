#ifndef MOVE_HPP
#define MOVE_HPP

#include "Point.hpp"
#include "Board.hpp"

struct Move{
	Point place;
	Board::VALUE colour;
	Move(const Point& p, Board::VALUE v) : place(p), colour(v) {}
};
#endif
