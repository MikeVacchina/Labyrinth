#include "mvMaze.h"

mvMaze::mvMaze()
{
	theda = 0.0;
	phi = 0.0;
}

mvMaze::mvMaze(std::vector<mvRect> &walls, mvRect base)
{
	theda = 0.0;
	phi = 0.0;

	mesh = base.getMesh();
	for(int i=0,size=walls.size();i<size;++i)
		mesh.addMesh(walls[i].getMesh());

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

mvMaze::~mvMaze()
{
}

void mvMaze::setMaze(std::vector<mvRect> &walls, mvRect base)
{
	mesh = base.getMesh();
	for(int i=0,size=walls.size();i<size;++i)
		mesh.addMesh(walls[i].getMesh());

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}
