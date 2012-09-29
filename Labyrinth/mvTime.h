#ifndef MVTIME
#define MVTIME

//#include <chrono>
#include <ctime>

class mvTime
{
public:
	mvTime();
	~mvTime();

	void startTime();
	double resetTime();
	double lapTime();
	double stopTime();

private:
	std::clock_t t1, t2;
	bool started;
};

#endif //MVTIME