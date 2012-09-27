#ifndef MVOBJECT
#define MVOBJECT

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include "mvSimpleStructs.h"

class mvObject
{
public:
	mvObject();
	~mvObject();
	
	GLuint vbo_geometry;// VBO handle for our geometry
	glm::mat4 model;//obj->world each object should have its own model matrix

	mvVertex *geometry;
	int vertexCount;

	virtual int sizeofgeometry();
};

#endif //MVOBJECT

