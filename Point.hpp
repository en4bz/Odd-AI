#ifndef POINT_HPP
#define POINT_HPP

#include <cstdlib>
#include <ostream>

struct BoardBoundsException{
    int x, y;
    BoardBoundsException(int px, int py) : x(px), y(py) {}
};

struct Point{
	int x,y;
	Point(int px, int py);
	bool operator < (const Point& pToCompare) const;
	bool operator== (const Point& pToCompare) const;
	bool operator!= (const Point& pToCompare) const;
};

std::ostream& operator<< (std::ostream& pStream, const Point& pPoint);

struct PointHasher{
	size_t operator() (const Point& pPoint) const{
		return pPoint.y ^ (pPoint.x << 4);
	}
};
#endif
