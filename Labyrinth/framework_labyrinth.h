#ifndef FRAMEWORK_LABYRINTH
#define FRAMEWORK_LABYRINTH

#include <Windows.h>
#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include "defines.h"

#include "mvInput.h"
#include "mvShader.h"
#include "mvSimpleStructs.h"
#include "mvObject.h"
#include "mvRect.h"
#include "mvMaze.h"
#include "mvTime.h"
#include "mvDisplay.h"

#define M_PI        3.14159265358979323846264338327950288   /* pi */

extern void initalizeGlut(int argc, char **argv);

extern void startGlut();

class framework_labyrinth
{
public:
	static framework_labyrinth* instance();

	bool initialize(std::string windowName, int windowWdith, int windowHeight);

private:
	framework_labyrinth();

	void initializeCallbacks();

	void displayFunc();
	void reshapeFunc(int newWidth, int newHeight);
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void specialFunc(int key, int x, int y);
	void specialUpFunc(int key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);
	void motionFunc(int x, int y);
	void idleFunc();

	mvTime stopwatch;
	mvDisplay display;

	mvInput userInput;
	
	static framework_labyrinth *__framework_labyrinth__;

	friend extern void displayWrapperFunc();
	friend extern void reshapeWrapperFunc(int newWidth, int newHeight);
	friend extern void keyboardWrapperFunc(unsigned char key, int x, int y);
	friend extern void keyboardUpWrapperFunc(unsigned char key, int x, int y);
	friend extern void specialWrapperFunc(int key, int x, int y);
	friend extern void specialUpWrapperFunc(int key, int x, int y);
	friend extern void mouseWrapperFunc(int button, int state, int x, int y);
	friend extern void motionWrapperFunc(int x, int y);
	friend extern void idleWrapperFunc();
};

//static framework_labyrinth labyrinth;

extern void displayWrapperFunc();
extern void reshapeWrapperFunc(int newWidth, int newHeight);
extern void keyboardWrapperFunc(unsigned char key, int x, int y);
extern void keyboardUpWrapperFunc(unsigned char key, int x, int y);
extern void specialWrapperFunc(int key, int x, int y);
extern void specialUpWrapperFunc(int key, int x, int y);
extern void mouseWrapperFunc(int button, int state, int x, int y);
extern void motionWrapperFunc(int x, int y);
extern void idleWrapperFunc();

#endif //FRAMEWORK_LABYRINTH