#include "main.hpp"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

static int sPro = 0;

int main(int argc, char* argv[]){
    RandomPlayer lRand;
    std::string name = "XYZ"
  	try{
    		io_service io_service;
		tcp::resolver resolver(io_service);
    		tcp::resolver::query query("localhost", "8123");
    		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(io_service);
    		connect(socket, endpoint_iterator);
//		socket.non_blocking(false);
		string acknowledge("START ");
		acknowledge += name;
		acknowledge += "\n";
		socket.send(buffer(acknowledge));
		cout << "Waiting to Start..." << endl;
		int lPlayerID = -1;{
		      	std::array<char, 24> buf;
    			boost::system::error_code error;
			int len = socket.read_some(buffer(buf), error);
			if (error == error::eof)
				return 0; // Connection closed cleanly by peer.
			else if (error)
			        throw boost::system::system_error(error); // Some other error.
			else if (len == 0){
				cerr << "No Respone from server" << endl;
			}
			string playerName =  processHeader(string(buf.data(),len));
			if(playerName.compare("Player1") == 0){
				lPlayerID = 1;
			}
			else{
				lPlayerID = 2;
			}
		}
		cout << "Playing as Player " << lPlayerID << endl;
		bool isOver = false;
		cout << "Waiting for Server" << endl;
		boost::asio::streambuf buf;
    		while( ! isOver){
      			boost::system::error_code error;
			size_t len = read_until(socket, buf, '\n');

			if (error == error::eof)
				break;
			else if (error)
			        throw boost::system::system_error(error); // Some other error.
			if(len == 0){
				continue;
			}

			const char* data = boost::asio::buffer_cast<const char*>(buf.data());
			std::string lMessage(data, sizeof(data));
			boost::algorithm::trim(lMessage);
			cout << "Proccessing: " << lMessage << " |" << endl;
			if(boost::starts_with(lMessage,"PLAY")){
				cout << "PLAY MOVE: ";
			        sendMove(socket, lPlayerID, lRand.move());
				buf.consume(12);
			}
			else if(boost::starts_with(lMessage, "GAMEOVER")){
				cout << "GAME OVER" << endl;
				isOver = true;
				break;
			}
			else if(lMessage.size() > 0){
		                Point last = processPoint(lMessage);
		                if(boost::starts_with(lMessage, "1")){
                		    lRand.updateBoard(last, Board::VALUE::BLACK);
                		}
		                else{
                		    lRand.updateBoard(last, Board::VALUE::WHITE);
                		}
				buf.consume(sPro);
			}
		}
		boost::system::error_code error;
		socket.close(error);
  	}
  	catch (std::exception& e)
  	{
		cerr << e.what() << endl;
  	}
	cout << "Terminating..." << endl;
  	return 0;
}

std::string processHeader(const std::string& toProcess){
	std::stringstream lStream;
	lStream << toProcess;
	std::string result;
	lStream.ignore(8,' ');
	lStream >> result;
	return result;
}

Point processPoint(const std::string& pStr){
	std::stringstream lStream;
	lStream << pStr;
	lStream.ignore(2,' ');
	int x,y;
	lStream >> x;
	lStream >> y;
	x -= y;//Transate To My Coordinate System.
	cout << "Processed Point: " << Point(x,y) << endl;
	return Point(x,y);
}

int sendMove(tcp::socket& socket, int playerid, const Point& p){
	std::stringstream lStream;
	lStream << noskipws << playerid << " " << p.x + p.y << " " << p.y << endl;
	string lOut = lStream.str();
	cout << "Transmiting: " << lOut;
	socket.write_some(buffer(lOut));
	return 0;
}
