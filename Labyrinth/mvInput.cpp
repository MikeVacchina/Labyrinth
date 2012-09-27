#include "mvInput.h"


mvInput::mvInput()
{
	lMouse = INVALID;
	rMouse = INVALID;
}


mvInput::~mvInput()
{
}

void mvInput::handleMouseFunc(int button, int state, int x, int y, mvMouseInput mouseInput)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			lMouse = DOWN;
			init_x = x;
			init_y = y;
			init_theda = mouseInput.theda;
			init_phi = mouseInput.phi;
		}
		else if(state == GLUT_UP)
		{
			lMouse = UP;
		}
	}
}


bool mvInput::handleMouseMotionFunc(int x, int y, mvMouseOutput &mouseOutput)
{
	if(lMouse == DOWN)
	{
		mouseOutput.theda = init_theda + (init_y - y)/15.0;
		mouseOutput.phi = init_phi + (x - init_x)/15.0;
		return true;
	}
	return false;
}