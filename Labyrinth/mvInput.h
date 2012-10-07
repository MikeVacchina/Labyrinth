#ifndef MVINPUT
#define MVINPUT

#include <map>

#include <Windows.h>
#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include "mvKey.h"

#include "mvSimpleStructs.h"

//this class handles user input throught the mouse and keyboard
class mvInput
{
public:
	mvInput();
	~mvInput();

	void handleMouseFunc(int button, int state, int x, int y, mvMouseData mouseInput);
	bool handleMouseMotionFunc(int x, int y, mvMouseData &mouseOutput);
	
	void handleKeyboardFunc(unsigned char key, mvKeyboardData keyboardInput);
	void handleSpecialFunc(int key, mvKeyboardData keyboardInput);
	
	double timeKeyDown(unsigned char key);
	double timeSpecialDown(int key);

private:
	double init_x, init_y, init_theda, init_phi;
	_mouseState lMouse;
	_mouseState rMouse;
	
	std::map<unsigned char, mvKey> keyStates;
	std::map<int, mvKey> specialStates;
};

#endif //MVINPUT