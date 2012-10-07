#ifndef MVCIRCLE
#define MVCIRCLE

#include <iostream>

#include "mvObject.h"
#include "mvObjLoader.h"
#include "mvMesh.h"

//simple circle object with center and radius
//inherits object class
class mvCircle : public mvObject
{
public:
	mvCircle();
	~mvCircle();

	//reimplement loadMesh
	void loadMesh(const char *filename);

	glm::vec3 center;
	double radius;
};

#endif //MVCIRCLE