#include "Point.hpp"
#include "Board.hpp"

struct Move{
	Point place;
	VALUE colour;
	Move(const Point& p, VALUE colour);
};
