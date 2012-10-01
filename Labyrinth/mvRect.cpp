#include "mvRect.h"

mvRect::mvRect(const char *filename)
{
	if(filename)
	{
		loadMesh(filename);
	}
}


mvRect::~mvRect()
{
}

void mvRect::loadMesh(const char *filename)
{
	std::string error;
	mvObjLoader(filename, mesh, error);

	if(error != "")
	{
        std::cerr << "[ERROR] cube.obj FAILED TO LOAD: ";
		std::cerr << error;
		return;
	}

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

void mvRect::setColor(double r, double g, double b)
{
	mesh.setColor(r, g, b);
	geometry = mesh.getGeometry();
}

mvMesh mvRect::getMesh()
{
	return mesh;
}
	
void mvRect::scale(double x, double y, double z)
{
	mesh.scale(vec3(x,y,z));

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

void mvRect::translate(double x, double y, double z)
{
	mesh.translate(vec3(x,y,z));

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}