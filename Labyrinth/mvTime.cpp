#include "mvTime.h"


mvTime::mvTime()
{
	started=false;
}


mvTime::~mvTime()
{
}

void mvTime::startTime()
{
	started = true;
	t1 = std::clock();//std::chrono::high_resolution_clock::now();
}

double mvTime::resetTime()
{
	if(started)
	{
		t2 = std::clock();//std::chrono::high_resolution_clock::now();
		started = false;
		double rtn = double(t2-t1)/CLOCKS_PER_SEC;
		startTime();
		return rtn;
	}
	return -1.0;
}

double mvTime::lapTime()
{
	if(started)
	{
		t2 = std::clock();
		return double(t2-t1)/CLOCKS_PER_SEC;
	}
	return -1.0;
}

double mvTime::stopTime()
{
	if(started)
	{
		t2 = std::clock();
		started = false;
		return double(t2-t1)/CLOCKS_PER_SEC;
	}
}