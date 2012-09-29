#ifndef MVSIMPLESTRUCTS
#define MVSIMPLESTRUCTS

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include "defines.h"

struct mvVertex
{
    GLfloat position[3];
    GLfloat color[3];
};

class mvMouseData
{
public:
	mvMouseData(double _theda=0.0, double _phi=0.0)
	{
		theda = _theda;
		phi   = _phi;
	}

	double theda;
	double phi;
};

class mvKeyboardData
{
public:
	mvKeyboardData(enum _keyState ks = KEY_INVALID)
	{
		keyState = ks;
	}

	int keyState;
};


#endif //MVSIMPLESTRUCTS

