#include <set>
#include <iostream>

#include "Point.hpp"
#include "Exception.hpp"

int main(void){
	std::set<int> llll;
	for(int i = -4; i <= 4; i++){
		for(int j = -4; j <= 4; j++){
			try{
				Point x(i,j);
				int l = abs((i*593 + j*2)*(j*(i+1))+ i*j -i*i + j*j -31*j + 37*i% 61);
				if(llll.find(l) != llll.end()){
					std::cout << x;
				}
				else{
					llll.insert(l);
				}
			}
			catch(Odd::BoardBoundsException e){
				continue;
			}
		}
	}
	std::cout << llll.size() << std::endl;
	return 0;
}
