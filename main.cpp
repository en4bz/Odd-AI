#include "main.hpp"

using namespace std;
using namespace boost::asio;


int main(int argc, char* argv[]){
  	try{
		const std::string lName = "XYZ";
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
		Board* const lGameBoard = new Board();
		#ifdef MONTECARLO
		MCPlayer lPlayer(lPlayerID, lGameBoard);
		#endif
		#ifdef UCB
		UCBPlayer lPlayer(lPlayerID);
		#endif
		#ifdef _AMAF_
		AMAFPlayer lPlayer(lPlayerID, lGameBoard);
		#endif
		#ifdef _AMAF2_
		AMAF2 lPlayer(lPlayerID, lGameBoard);
		#endif
		#ifdef HYBRIDPLAYER
		Hybrid lPlayer(lPlayerID, lGameBoard);
		#endif
		cout << "Playing as " << lPlayerName << endl;
		bool isOver = false;
		while( ! isOver){
			std::string lMessage;
			socket >> lMessage;
			#ifdef _DEBUG_
			cout << "Proccessing: " << lMessage << " |" << endl;
			#endif
			if(lMessage == "PLAY"){
				std::cout << " Move :" << lPlayer.movesLeft() <<  " | ";
				const Profiler lMoveTime("Executed Move in: ");
				sendMove(socket, lPlayerID, lPlayer.move());
				socket.ignore(16,' ');//Empty socket after playing.
				cout << lMoveTime;
			}
			else if(lMessage == "1" || lMessage == "2"){
				lPlayer.updateBoard(processMove(socket));
			}
			else if(lMessage == "GAMEOVER"){
				cout << lMessage << " ";
				socket >> lMessage;
				cout << lMessage << " ";
				socket >> lMessage;
				cout << lMessage << endl;
				if(lMessage == lPlayerName){
					cout << "Win" << endl;
				}
				else{
					cout << "Lose" << endl;
				}
				isOver = true;
			}
		}
		delete lGameBoard;
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
	if(lColour == "WHITE"){
		return Move(Point(x-y,y), Board::VALUE::WHITE);
	}
	else{
		return Move(Point(x-y,y), Board::VALUE::BLACK);
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

