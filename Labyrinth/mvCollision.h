#ifndef MVCOLLISION
#define MVCOLLISION

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include <iostream>

#include "mvObject.h"
#include "mvMaze.h"
#include "mvSphere.h"

#include "mvMath.h"

class mvCollision
{
public:
	mvCollision();
	~mvCollision();
	
	void setMaze(mvMaze *m);
	void setBall(mvSphere *b);

	void resolveCollisions();

private:
	mvMaze *maze;
	mvSphere *ball;

	std::vector<mvWall> xWalls;
	std::vector<mvWall> zWalls;
	std::vector<mvHole> holes;
	glm::vec3 goal;
	double radius;
};

#endif //MVCOLLISION