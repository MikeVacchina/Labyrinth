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

#include "mvSimpleStructs.h"

#include "mvShader.h"
#include "mvInput.h"
#include "mvTime.h"
#include "mvDisplay.h"
#include "mvPhysics.h"
#include "mvCollision.h"
#include "mvObject.h"
#include "mvSphere.h"
#include "mvMaze.h"

#define M_PI        3.14159265358979323846264338327950288   /* pi */

//Initialize/Start Glut Functions
extern void initializeGlut(int argc, char **argv);
extern void startGlut();

//framework class for labyrinth game
//singleton class
//accessed by framework_labyrith::instance()
class framework_labyrinth
{
public:
	//singleton instance
	static framework_labyrinth* instance();

	//initialize labyrinth with glew/glut
	bool initialize(std::string windowName, int windowWdith, int windowHeight);

private:
	//make constructor private for singleton class
	framework_labyrinth();

	void initializeCallbacks();

	//framework function callbacks
	void displayFunc();
	void reshapeFunc(int newWidth, int newHeight);
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void specialFunc(int key, int x, int y);
	void specialUpFunc(int key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);
	void motionFunc(int x, int y);
	void idleFunc();

	//variable setters to enforce constraints on variables
	void setTheda(double t);
	void setPhi(double p);

	//timer
	mvTime stopwatch;

	//display handler
	mvDisplay display;

	//input handler
	mvInput userInput;

	//physics handler
	mvPhysics physics;

	//collision handler
	mvCollision collision;

	//keep a reference to objects in framework
	std::vector<mvObject*> objs;
	
	//maze orientation variables
	double theda, phi;
	
	//singleton instance
	static framework_labyrinth *__framework_labyrinth__;

	//friend callbacks for glut
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

//callbacks for glut which call framework funcs
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