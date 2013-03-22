#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <iostream>
#include <boost/asio.hpp>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "MCPlayer.hpp"
#include "RandomPlayer.hpp"

void 	sendMove(boost::asio::ip::tcp::iostream&, int , const Move&);
Move 	processMove(boost::asio::ip::tcp::iostream&);
Point	processPoint(boost::asio::ip::tcp::iostream&);
#endif
