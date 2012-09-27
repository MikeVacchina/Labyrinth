#ifndef MVMAZE
#define MVMAZE

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include <iostream>
#include <string>
#include <vector>

#include "mvObject.h"
#include "mvSimpleStructs.h"
#include "mvObjLoader.h"
#include "mvMesh.h"
#include "mvRect.h"

class mvMaze : public mvObject
{
public:
	mvMaze();
	mvMaze(std::vector<mvRect> &walls, mvRect base);
	~mvMaze();

	void setMaze(std::vector<mvRect> &walls, mvRect base);

	double theda;
	double phi;

private:
	mvMesh mesh;
};

#endif //MVMAZE