#ifndef MVDISPLAY
#define MVDISPLAY

#include <Windows.h>
#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting
#include <gl/GLU.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "defines.h"

#include "mvShader.h"
#include "mvSimpleStructs.h"
#include "mvObject.h"
#include "mvRect.h"
#include "mvMaze.h"
#include "mvSphere.h"

class mvDisplay
{
public:
	mvDisplay();
	~mvDisplay();
	
	//initialize size and name of window
	void initializeDisplay(std::string windowName, int w, int h);

	//initialize resources to be used for gl and glut
	bool initializeDisplayResources();

	//display objects
	void display();

	//reshape window
	void reshape(int newWidth, int newHeight);

	//set maze to be played
	void playMaze(int mazeID);

	//set maze model matrix
	void setMazeModelMat(glm::mat4 m);

	//set ball model matrix
	void setBallModelMat(glm::mat4 m);

	//return reference to maze
	mvMaze* getMaze();
	
	//return reference to ball
	mvSphere* getSphere();

private:
	//initialize the object for gl and glut
	void objectBufferInit(mvObject &object);
	
	//display the object
	void displayObject(mvObject &object);
	
	int width, height;

	GLuint program;

	//uniform locations
	GLint loc_mvpmat;// Location of the modelviewprojection matrix in the shader

	//attribute locations
	GLint loc_position;
	GLint loc_color;

	glm::mat4 view;//world->eye
	glm::mat4 projection;//eye->clip

	//flag to know when to display objects
	bool started;

	//maze id
	int maze;

	//objects
	mvMaze maze1;
	mvMaze maze2;
	mvSphere sphere;
};

#endif //MVDISPLAY