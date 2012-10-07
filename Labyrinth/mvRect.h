#ifndef MVCUBE
#define MVCUBE

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <iostream>
#include <string>

#include "mvObject.h"
#include "mvSimpleStructs.h"
#include "mvObjLoader.h"
#include "mvMesh.h"

class mvRect : public mvObject
{
public:
	mvRect(const char *filename = NULL);
	~mvRect();

	mvMesh getMesh();
	
	void scale(double x, double y, double z);
	void translate(double x, double y, double z);
};

#endif //MVCUBE