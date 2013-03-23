#include "Point.hpp"

Point::Point(int px, int py){
	if((abs(px + py)) > 4 || (abs(px)) > 4 || (abs(py)) > 4){
		throw BoardBoundsException(px,py);
	}
	else{
		this->x = px;
		this->y = py;
	}
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
