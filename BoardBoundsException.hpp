#ifndef BOARDBOUNDSEXCEPTION_HPP
#define BOARDBOUNDSEXCEPTION_HPP
struct BoardBoundsException{
    int x, y;
    BoardBoundsException(int px, int py) : x(px), y(py) {}
};
#endif
