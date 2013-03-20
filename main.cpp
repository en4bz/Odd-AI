#include "main.hpp"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
	RandomPlayer lRand;
	std::string name = "XYZ";
  	try{
		boost::asio::ip::tcp::iostream socket;
		socket.connect("localhost", "8123");
		string acknowledge("START ");
		acknowledge += name;
		acknowledge += "\n";
		socket << acknowledge;
		cout << "Waiting to Start..." << endl;
		int lPlayerID = -1;
		string playerName;
		socket >> playerName;
		cout << playerName << endl;
		socket >> playerName;
		cout << playerName << endl;
		if(playerName.compare("Player1") == 0){
			lPlayerID = 1;
		}
		else{
			lPlayerID = 2;
		}
		cout << "Playing as Player " << lPlayerID << endl;
		bool isOver = false;
		cout << "Waiting for Server" << endl;
    		while( ! isOver){
			std::string lMessage;
			socket >> lMessage;
			cout << "Proccessing: " << lMessage << " |" << endl;
			if(boost::starts_with(lMessage,"PLAY")){
				socket >> lMessage;
				cout << "PLAY MOVE: " << lMessage << endl;
			        sendMove(socket, lPlayerID, lRand.move());
			}
			else if(boost::starts_with(lMessage, "GAMEOVER")){
				socket >> lMessage;
				socket >> lMessage;
				cout << "GAME OVER! Winner is: " << lMessage << endl;
				isOver = true;
				break;
			}
			else if(lMessage.compare("1") == 0){
		                Point last = processPoint(socket);
				lRand.updateBoard(last, Board::VALUE::WHITE);
			}
			else if(lMessage.compare("2") == 0){
		                Point last = processPoint(socket);
				lRand.updateBoard(last, Board::VALUE::BLACK);
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

Point processPoint(boost::asio::ip::tcp::iostream& lStream){
	int x,y;
	lStream >> x;
	lStream >> y;
	x -= y;//Transate To My Coordinate System.
	cout << "Processed Point: " << Point(x,y) << endl;
	return Point(x,y);
}

int sendMove(boost::asio::ip::tcp::iostream& socket, int playerid, const Point& p){
	std::stringstream lStream;
	lStream << noskipws << playerid << " " << p.x + p.y << " " << p.y << endl;
	string lOut = lStream.str();
	cout << "Transmiting: " << lOut;
	socket << lOut;
	return 0;
}
