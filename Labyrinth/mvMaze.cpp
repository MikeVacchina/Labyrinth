#include "mvMaze.h"

mvMaze::mvMaze()
{
	rect.loadMesh("cube.obj");
}

mvMaze::~mvMaze()
{
}

void mvMaze::setSize(double w, double d)
{
	mvRect tmp;
	tmp = rect;
	
	tmp.translate(0.0,-1.0,0.0);
	tmp.scale(w/2.0,0.25,d/2.0);
	tmp.setColor(0.0,1.0,0.0);

	mesh = tmp.getMesh();
}

void mvMaze::setWall(double x, double z, double w, double d)
{
	mvRect tmp;

	int wallCount = xWalls.size();

	tmp = rect;
	
	tmp.scale(w/2.0,0.5,d/2.0);
	tmp.translate(x,0.5,z);
	tmp.setColor(1.0,0.0,0.0);

	mesh.addMesh(tmp.getMesh());
	
	xWalls.push_back(mvWall(x-(w/2), x+(w/2.0), wallCount+1));
	zWalls.push_back(mvWall(z-(d/2), z+(d/2.0), wallCount+1));
}

void mvMaze::init()
{
	std::sort(xWalls.begin(), xWalls.end());
	std::sort(zWalls.begin(), zWalls.end());

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}