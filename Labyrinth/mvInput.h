#ifndef MVINPUT
#define MVINPUT

#include <Windows.h>
#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include "mvMouse.h"
#include "mvKeyboard.h"
#include "mvKey.h"

#include "mvSimpleStructs.h"

class mvInput
{
public:
	mvInput();
	~mvInput();

	void handleMouseFunc(int button, int state, int x, int y, mvMouseInput mouseInput);
	bool handleMouseMotionFunc(int x, int y, mvMouseOutput &mouseOutput);

	double init_x, init_y, init_theda, init_phi;
	enum mouseState {DOWN, UP, INVALID};
	mouseState lMouse;
	mouseState rMouse;
};

#endif //MVINPUT