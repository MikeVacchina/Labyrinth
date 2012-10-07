#ifndef MVCIRCLE
#define MVCIRCLE

#include "mvObject.h"

class mvCircle : public mvObject
{
public:
	mvCircle();
	~mvCircle();

	void loadMesh(const char *filename);

	glm::vec3 center;
	double radius;
};

#endif //MVCIRCLE