#ifndef MVKEY
#define MVKEY

#include "mvTime.h"

class mvKey
{
public:
	mvKey();

	~mvKey();

	bool isDown();

	double timeDown();

	void setPressed(bool down);

private:
	mvTime stopwatch;
	bool pressed;
	double downTime;
};

#endif //MVKEY