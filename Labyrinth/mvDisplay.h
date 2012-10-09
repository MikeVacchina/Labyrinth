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

#include "mvText.h"

class mvDisplay
{
public:
	mvDisplay();
	~mvDisplay();
	
	void initializeDisplay(std::string windowName, int w, int h);
	bool initializeDisplayResources();

	//display objects
	void display();

	void reshape(int newWidth, int newHeight);

	void setMazeModelMat(glm::mat4 m);
	void setBallModelMat(glm::mat4 m);

	mvMaze* getMaze();
	mvSphere* getSphere();

private:
	void objectBufferInit(mvObject &object);
	
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

	//objects
	mvMaze maze;
	mvSphere sphere;
};

#endif //MVDISPLAY