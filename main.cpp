#include "main.hpp"

using namespace boost::asio;

int main(int argc, char* argv[]){
	std::string host("localhost");
	std::string port("8123");
	if(argc > 1){
		host = argv[1];
		if(argc > 2){
			port = argv[2];
		}
	}
  	try{
		ip::tcp::iostream socket;
		socket.connect(host, port);
		std::cout << "Waiting to Start..." << std::endl;
		socket << "START " << "NAME" << std::endl;
		int lPlayerID;
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
			std::cout << "Server Error!" << std::endl;
			socket.close();
			return 1;
		}
		#ifdef _MONTECARLO_
		MCPlayer lPlayer(lPlayerID);
		#endif
		#ifdef _MCP2_
		MCP2 lPlayer(lPlayerID);
		#endif
		#ifdef _AMAF_
		AMAFPlayer lPlayer(lPlayerID);
		#endif
		#ifdef _AMAF2_
		AMAF2 lPlayer(lPlayerID);
		#endif
		std::cout << "Playing as " << lPlayerName << std::endl;
		bool isOver = false;
		while( !isOver){
			std::string lMessage;
			socket >> lMessage;
			if(lMessage == "PLAY"){
				std::cout << " Move :" << lPlayer.movesLeft() <<  " | ";
				const Profiler lMoveTime("Executed Move in: ");
				sendMove(socket, lPlayerID, lPlayer.move());
//				socket.ignore(16,' ');//Empty socket after playing. Why?
				std::cout << lMoveTime;
			}
			else if(lMessage == "1" || lMessage == "2"){
				lPlayer.updateBoard(processMove(socket));
			}
			else if(lMessage == "GAMEOVER"){
				std::cout << lMessage << " ";
				socket >> lMessage;
				std::cout << lMessage << " ";
				socket >> lMessage;
				std::cout << lMessage << std::endl;
				if(lMessage == lPlayerName){
					std::cout << "Win" << std::endl;
				}
				else{
					std::cout << "Lose" << std::endl;
				}
				isOver = true;
			}
		}
		socket.close();
  	}
  	catch (std::exception& e){
		std::cerr << e.what() << std::endl;
		return 1;
  	}
	std::cout << "Terminating..." << std::endl;
  	return 0;
}

Move processMove(ip::tcp::iostream& lStream){
	int x,y;
	std::string lColour;
	lStream >> lColour >> x >> y;
	if(lColour == "WHITE")
		return Move(Point(x-y,y), Board::VALUE::WHITE);
	else
		return Move(Point(x-y,y), Board::VALUE::BLACK);
}

void sendMove(ip::tcp::iostream& socket, int playerid, const Move& move){
	if(move.colour == Board::VALUE::WHITE)
		socket << playerid << " WHITE " << move.place.x + move.place.y << " " << move.place.y << std::endl;
	else
		socket << playerid << " BLACK " << move.place.x + move.place.y << " " << move.place.y << std::endl;
	return;
}

