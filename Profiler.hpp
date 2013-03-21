#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <string>
#include <iostream>

class Profiler{
private:
	const std::string mMessage;
	const std::chrono::high_resolution_clock::time_point mStart;
public:
	Profiler(const std::string);
	friend std::ostream& operator<< (std::ostream&, const Profiler&);
};
#endif


