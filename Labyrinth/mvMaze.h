#ifndef MVMAZE
#define MVMAZE

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <fstream>

#include "mvObject.h"
#include "mvSimpleStructs.h"
#include "mvObjLoader.h"
#include "mvMesh.h"
#include "mvRect.h"
#include "mvCircle.h"

class mvMaze : public mvObject
{
public:
	mvMaze();
	~mvMaze();

	bool loadMaze(const char *filename);
	
	void setSize(double w, double d);
	void setWall(double x, double z, double w, double d);
	void setHole(double x, double z, double r);

	void init();

	std::vector<mvWall> getXWalls();
	std::vector<mvWall> getZWalls();
	std::vector<mvHole> getHoles();
	glm::vec3 getGoal();

	glm::vec3 getBegin();

private:
	mvRect rect;
	
	std::vector<mvWall> xWalls;
	std::vector<mvWall> zWalls;

	std::vector<mvHole> holes;

	glm::vec3 begin;
	mvCircle goal;

	bool skipCommentLine(std::istream& is);
	void skipLine(std::istream &is);
	bool processLine(std::istream &is);
};

#endif //MVMAZE