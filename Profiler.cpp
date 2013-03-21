#include "Profiler.hpp"

Profiler::Profiler(const std::string toDisplay) : mMessage(toDisplay), mStart(std::chrono::high_resolution_clock::now()) {}

std::ostream& operator<< (std::ostream& pStream, const Profiler& pro){
	std::chrono::high_resolution_clock::time_point lNow = std::chrono::high_resolution_clock::now();
       	return pStream << pro.mMessage << std::chrono::duration_cast<std::chrono::nanoseconds>(lNow - pro.mStart).count();
}
