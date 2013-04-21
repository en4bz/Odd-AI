#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <string>
#include <iostream>
#include <boost/timer/timer.hpp>

class Profiler{
private:
	const std::string mMessage;
	boost::timer::auto_cpu_timer t;
public:
	Profiler(const std::string toDisplay) : mMessage(toDisplay) {}
	~Profiler(){
		std::cout << this->mMessage;
	}
};
#endif


