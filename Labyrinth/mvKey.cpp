#include "mvKey.h"

mvKey::mvKey()
{
	pressed = false;
	downTime = 0.0;
}

mvKey::~mvKey()
{
}

bool mvKey::isDown()
{
	return pressed;
}

double mvKey::timeDown()
{
	if(pressed)
		return stopwatch.resetTime();
	else
	{
		double rtn = downTime;
		downTime = 0.0;
		return rtn;
	}
}

void mvKey::setPressed(bool down)
{
	if(pressed != down)
	{
		pressed = down;
		if(pressed)
			stopwatch.startTime();
		else
			downTime = stopwatch.stopTime();
	}
}