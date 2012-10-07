#ifndef MVPHYSICS
#define MVPHYSICS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "mvSimpleStructs.h"

#include <vector>

#include "mvMath.h"
#include "mvObject.h"

class mvPhysics
{
public:
	mvPhysics();

	~mvPhysics();

	void setGravity(glm::vec3 g);

	void setObjs(std::vector<mvObject*> o);

	void update(double deltaTime);
	
private:
	glm::vec3 gravity;

	std::vector<mvObject*> objs;
};

#endif //MVPHYSICS