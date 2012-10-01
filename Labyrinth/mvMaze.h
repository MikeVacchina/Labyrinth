#ifndef MVMAZE
#define MVMAZE

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "mvObject.h"
#include "mvSimpleStructs.h"
#include "mvObjLoader.h"
#include "mvMesh.h"
#include "mvRect.h"

class mvMaze : public mvObject
{
public:
	mvMaze();
	~mvMaze();
	
	void setSize(double w, double d);
	void setWall(double x, double z, double w, double d);

	void init();
	
	std::vector<mvWall> xWalls;
	std::vector<mvWall> zWalls;

private:
	mvMesh mesh;

	mvRect rect;
};

#endif //MVMAZE