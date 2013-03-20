#include "main.hpp"

using namespace std;
using namespace boost::asio;

static std::string name = "XYZ";

int main(int argc, char* argv[]){
	RandomPlayer lRand;
  	try{
		ip::tcp::iostream socket;
		socket.connect("localhost", "8123");
		socket << "START " << name << endl;
		cout << "Waiting to Start..." << endl;//Acknowledge
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
				//cout << "PLAY MOVE: " << lMessage << endl;
			        sendMove(socket, lPlayerID, lRand.move());
			}
			else if(lMessage == "GAMEOVER"){
				socket >> lMessage;
				socket >> lMessage;
				cout << "GAME OVER!" << endl << "Winner is: " << lMessage << endl;
				isOver = true;
				break;
			}
			else if(lMessage == "1"){
		                Move lLast = processMove(socket);
				lRand.updateBoard(lLast);
			}
			else if(lMessage  == "2"){
		                Move lLast = processMove(socket);
				lRand.updateBoard(lLast);
			}
		}
		socket.close();
  	}
  	catch (std::exception& e)
  	{
		cerr << e.what() << endl;
		return 1;
  	}
	cout << "Terminating..." << endl;
  	return 0;
}

Move processMove(ip::tcp::iostream& lStream){
	int x,y;
	std::string lColour;
	lStream >> lColour >> x >> y;
	x -= y;//Transate To My Coordinate System.
	if(lColour == "WHITE"){
		return Move(Point(x,y), Board::VALUE::WHITE);
	}
	else{
		return Move(Point(x,y), Board::VALUE::BLACK);
	}
}

void sendMove(ip::tcp::iostream& socket, int playerid, const Move& move){
	if(move.colour == Board::VALUE::WHITE){
		socket << playerid << " " << "WHITE" << " "  << move.place.x + move.place.y << " " << move.place.y << endl;
	}
	else{
		socket << playerid << " " << "BLACK" << " "  << move.place.x + move.place.y << " " << move.place.y << endl;
	}
	return;
}

