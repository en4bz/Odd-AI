#ifndef MAIN_HPP
#define MAIN_HPP

#include <array>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "Point.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "RandomPlayer.hpp"

int sendMove(boost::asio::ip::tcp::iostream&, int , const Point&);
Point processPoint(boost::asio::ip::tcp::iostream&);
#endif
