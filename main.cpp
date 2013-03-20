#include "main.hpp"

using namespace std;
using namespace boost::asio;

int main(int argc, char* argv[]){
	RandomPlayer lRand;
	std::string name = "XYZ";
  	try{
		ip::tcp::iostream socket;
		socket.connect("localhost", "8123");
		std::string acknowledge = "START " + name + "\n";
		socket << acknowledge;
		cout << "Waiting to Start..." << endl;
		int lPlayerID = -1;
		std::string playerName;
		socket.ignore(16, ' ');
		socket >> playerName;
		if(playerName == "Player1"){
			lPlayerID = 1;
		}
		else{
			lPlayerID = 2;
		}
		cout << "Playing as Player " << lPlayerID << endl;
		cout << "Waiting for Server" << endl;
		bool isOver = false;
    		while( ! isOver){
			std::string lMessage;
			socket >> lMessage;
			//cout << "Proccessing: " << lMessage << " |" << endl;
			if(lMessage == "PLAY"){
				socket >> lMessage;
				cout << "PLAY MOVE: " << lMessage << endl;
			        sendMove(socket, lPlayerID, lRand.move(), Board::VALUE::BLACK);
			}
			else if(lMessage == "GAMEOVER"){
				socket >> lMessage;
				socket >> lMessage;
				cout << "GAME OVER!" << endl << "Winner is: " << lMessage << endl;
				isOver = true;
				break;
			}
			else if(lMessage == "1"){
		                Move last = processMove(socket);
				lRand.updateBoard(last.place, Board::VALUE::BLACK);
			}
			else if(lMessage  == "2"){
		                Move last = processMove(socket);
				lRand.updateBoard(last.place, Board::VALUE::BLACK);
			}
		}
		socket.close();
  	}
  	catch (std::exception& e)
  	{
		cerr << e.what() << endl;
  	}
	cout << "Terminating..." << endl;
  	return 0;
}

Move processMove(boost::asio::ip::tcp::iostream& lStream){
	std::string lColour;
	lStream >> lColour;
	int x,y;
	lStream >> x;
	lStream >> y;
	x -= y;//Transate To My Coordinate System.
	if(lColour == "WHITE"){
		return Move(Point(x,y), Board::VALUE::WHITE);
	}
	else{
		return Move(Point(x,y), Board::VALUE::BLACK);
	}
}

Point processPoint(boost::asio::ip::tcp::iostream& lStream){
	int x,y;
	lStream >> x;
	lStream >> y;
	x -= y;//Transate To My Coordinate System.
	cout << "Processed Point: " << Point(x,y) << endl;
	return Point(x,y);
}

void sendMove(ip::tcp::iostream& socket, int playerid, const Point& p, Board::VALUE colour){
	socket << playerid << " " << "BLACK" << " "  << p.x + p.y << " " << p.y << endl;
	return;
}
