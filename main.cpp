#include "main.hpp"

using namespace std;
using namespace boost::asio;


int main(int argc, char* argv[]){
  	try{
		std::string lName = "XYZ";
		ip::tcp::iostream socket;
		socket.connect("localhost", "8123");
		cout << "Waiting to Start..." << endl;//Acknowledge
		socket << "START " << lName << endl;
		int lPlayerID = -1;
		std::string lPlayerName;
		socket.ignore(16, ' ');
		socket >> lPlayerName;
		if(lPlayerName == "Player1"){
			lPlayerID = 1;
		}
		else if(lPlayerName == "Player2"){
			lPlayerID = 2;
		}
		else{
			std::cout << "Server Error" << std::endl;
			socket.close();
			return 1;
		}
		MCPlayer lRand(lPlayerID);
		cout << "Playing as Player " << lPlayerID << endl;
		bool isOver = false;
		while( ! isOver){
			std::string lMessage;
			socket >> lMessage;
			#ifdef _DEBUG_
			cout << "Proccessing: " << lMessage << " |" << endl;
			#endif
			if(lMessage == "PLAY"){
				Profiler lMoveTime("Executed Move in: ");
				sendMove(socket, lPlayerID, lRand.move());
				socket.ignore(16,' ');//Empty socket after playing.
				cout << lMoveTime << endl;
			}
			else if(lMessage == "1" || lMessage == "2"){
		        Move lLast = processMove(socket);
				lRand.updateBoard(lLast);
			}
			else if(lMessage == "GAMEOVER"){
				cout << lMessage << " ";
				socket >> lMessage;
				cout << lMessage;
				socket >> lMessage;
				cout << lMessage << " " << endl;
				if(lMessage == lPlayerName){
					cout << "Win" << endl;
				}
				else{
					cout << "Lose" << endl;
				}
				isOver = true;
			}
		}
		socket.close();
  	}
  	catch (std::exception& e){
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
		socket << playerid << " WHITE " << move.place.x + move.place.y << " " << move.place.y << endl;
	}
	else{
		socket << playerid << " BLACK " << move.place.x + move.place.y << " " << move.place.y << endl;
	}
	return;
}

