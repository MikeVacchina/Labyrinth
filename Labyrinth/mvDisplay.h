#ifndef MVDISPLAY
#define MVDISPLAY

#include <Windows.h>
#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "defines.h"

#include "mvInput.h"
#include "mvShader.h"
#include "mvSimpleStructs.h"
#include "mvObject.h"
#include "mvRect.h"
#include "mvMaze.h"
#include "mvTime.h"

class mvDisplay
{
public:
	mvDisplay();
	~mvDisplay();
	
	void initializeDisplay(std::string windowName, int w, int h);
	bool initializeDisplayResources();
	void display();
	void updateDisplay();
	void reshape(int newWidth, int newHeight);

	void setTheda(double t);
	void setPhi(double p);
	double getTheda();
	double getPhi();

	void setUserInput(mvInput *input);

private:
	void objectBufferInit(mvObject &object);
	
	void displayObject(mvObject &object);

	mvInput *userInput;
	
	int width, height;

	GLuint program;

	//uniform locations
	GLint loc_mvpmat;// Location of the modelviewprojection matrix in the shader

	//attribute locations
	GLint loc_position;
	GLint loc_color;

	glm::mat4 view;//world->eye
	glm::mat4 projection;//eye->clip

	mvMaze maze;

	double phi, theda;
};

#endif //MVDISPLAY