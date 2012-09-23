#ifndef FRAMEWORK_LABYRINTH
#define FRAMEWORK_LABYRINTH

#include <Windows.h>
#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <iostream>
//#include <chrono>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include "mvShader.h"
#include "mvVertex.h"
#include "mvObject.h"
#include "mvRect.h"
#include "mvMaze.h"

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
	
	bool initializeResources();

	void glBufferInitialize(mvObject &object);

	void displayFunc();
	void reshapeFunc(int newWidth, int newHeight);
	void keyboardFunc(unsigned char key, int x, int y);
	void specialFunc(int key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);
	void motionFunc(int x, int y);
	void idleFunc();

	void displayObject(mvObject object);

	void updateDisplay();

	float getDT();

	int width, height;
	std::clock_t t1, t2;

	GLuint program;

	//uniform locations
	GLint loc_mvpmat;// Location of the modelviewprojection matrix in the shader

	//attribute locations
	GLint loc_position;
	GLint loc_color;

	glm::mat4 view;//world->eye
	glm::mat4 projection;//eye->clip

	mvMaze maze;

	double init_x, init_y, init_theda, init_phi;
	enum clickState {DOWN, UP, INVALID};
	clickState leftMouse;

	static framework_labyrinth *__framework_labyrinth__;

	friend extern void displayWrapperFunc();
	friend extern void reshapeWrapperFunc(int newWidth, int newHeight);
	friend extern void keyboardWrapperFunc(unsigned char key, int x, int y);
	friend extern void specialWrapperFunc(int key, int x, int y);
	friend extern void mouseWrapperFunc(int button, int state, int x, int y);
	friend extern void motionWrapperFunc(int x, int y);
	friend extern void idleWrapperFunc();
};

//static framework_labyrinth labyrinth;

extern void displayWrapperFunc();
extern void reshapeWrapperFunc(int newWidth, int newHeight);
extern void keyboardWrapperFunc(unsigned char key, int x, int y);
extern void specialWrapperFunc(int key, int x, int y);
extern void mouseWrapperFunc(int button, int state, int x, int y);
extern void motionWrapperFunc(int x, int y);
extern void idleWrapperFunc();

#endif //FRAMEWORK_LABYRINTH