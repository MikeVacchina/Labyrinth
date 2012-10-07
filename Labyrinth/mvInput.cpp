#include "mvInput.h"


mvInput::mvInput()
{
	lMouse = MOUSE_INVALID;
	rMouse = MOUSE_INVALID;
}


mvInput::~mvInput()
{
}

void mvInput::handleMouseFunc(int button, int state, int x, int y, mvMouseData mouseInput)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			lMouse = MOUSE_DOWN;
			init_x = x;
			init_y = y;
			init_theda = mouseInput.theda;
			init_phi = mouseInput.phi;
		}
		else if(state == GLUT_UP)
		{
			lMouse = MOUSE_UP;
		}
	}
}


bool mvInput::handleMouseMotionFunc(int x, int y, mvMouseData &mouseOutput)
{
	if(lMouse == MOUSE_DOWN)
	{
		mouseOutput.theda = init_theda + (init_y - y)/15.0;
		mouseOutput.phi = init_phi + (x - init_x)/15.0;
		return true;
	}
	return false;
}

void mvInput::handleKeyboardFunc(unsigned char key, mvKeyboardData keyboardInput)
{
	if(keyboardInput.keyState == KEY_DOWN)
	{
		if(key == 27)//ESC
		{
			//clean up
			exit(0);
		}
		else
		{
			keyStates[key].setPressed(true);
		}
	}
	else if(keyboardInput.keyState == KEY_UP)
	{
		keyStates[key].setPressed(false);
	}
}

void mvInput::handleSpecialFunc(int key, mvKeyboardData keyboardInput)
{
	if(keyboardInput.keyState == KEY_DOWN)
	{
		specialStates[key].setPressed(true);
	}
	else if(keyboardInput.keyState == KEY_UP)
	{
		specialStates[key].setPressed(false);
	}
}
	
double mvInput::timeKeyDown(unsigned char key)
{
	return keyStates[key].timeDown();
}

double mvInput::timeSpecialDown(int key)
{
	return specialStates[key].timeDown();
}