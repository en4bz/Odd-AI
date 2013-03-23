#ifndef POINT_HPP
#define POINT_HPP

#include <cstdlib>
#include <ostream>

#include "BoardBoundsException.hpp"

struct Point{
	int x,y;
	Point(int px, int py);
	bool operator== (const Point& pToCompare) const;
	bool operator!= (const Point& pToCompare) const;
};

std::ostream& operator<< (std::ostream& pStream, const Point& pPoint);

struct PointHasher{
	long operator() (const Point& pPoint) const{
		return pPoint.y * 37 + pPoint.x * 787;
	}
};
#endif
