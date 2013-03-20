#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <iostream>
#include <boost/asio.hpp>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"

int 	sendMove(boost::asio::ip::tcp::iostream&, int , const Point&);
Point 	processPoint(boost::asio::ip::tcp::iostream&);
#endif
