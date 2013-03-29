#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <string>
#include <iostream>
#include <boost/timer/timer.hpp>

class Profiler{
private:
	const std::string mMessage;
	boost::timer::auto_cpu_timer t;
public:
	Profiler(const std::string);
	friend std::ostream& operator<< (std::ostream&, const Profiler&);
};
#endif


