#include "Point.hpp"

Point::Point(int px, int py) : x(px), y(py){
	#ifndef RELEASE
	if(abs(px + py) > 4 || abs(px) > 4 || abs(py) > 4){
		throw BoardBoundsException(px,py);
	}
	#endif
}

bool Point::operator < (const Point& pToCompare) const{
    return (this->x < pToCompare.x) || ((this->x == pToCompare.x) && (this->y < pToCompare.y));
}

bool Point::operator== (const Point& pToCompare) const{
	return x == pToCompare.x && y == pToCompare.y;
}

bool Point::operator!= (const Point& pToCompare) const{
	return x != pToCompare.x || y != pToCompare.y;
}

std::ostream& operator<< (std::ostream& pStream, const Point& pPoint){
    return  (pStream << "(" << pPoint.x << "," << pPoint.y << ")");
}
