#ifndef MVOBJECT
#define MVOBJECT

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include <iostream>
#include <string>
#include <vector>

#include "mvSimpleStructs.h"
#include "mvObjLoader.h"

class mvObject
{
public:
	mvObject();
	~mvObject();
	
	GLuint vbo_geometry;// VBO handle for our geometry
	glm::mat4 model;//obj->world each object should have its own model matrix

	mvVertex *geometry;
	int vertexCount;

	virtual void loadMesh(const char *filename);

	virtual mvMesh getMesh();

	virtual void setColor(double r, double g, double b);

	virtual int sizeofgeometry();
	
	glm::vec3 acc;
	glm::vec3 vel;
	glm::vec3 pos;

	std::vector<glm::vec3> normalForces;

protected:
	mvMesh mesh;
};

#endif //MVOBJECT

