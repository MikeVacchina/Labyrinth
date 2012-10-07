#ifndef MVSPHERE
#define MVSPHERE

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include <iostream>
#include <string>

#include "mvObject.h"
#include "mvSimpleStructs.h"
#include "mvObjLoader.h"
#include "mvMesh.h"

class mvSphere : public mvObject
{
public:
	mvSphere(const char *filename = NULL);
	~mvSphere();

	void loadMesh(const char *filename);

	mvMesh getMesh();
	
	void scale(double s);
	void translate(double x, double y, double z);

	double getMeshRadius();
	void getMeshCenter(double &x, double &y, double &z);

private:
	double radius;
	double centerX, centerY, centerZ;
};

#endif //MVSPHERE