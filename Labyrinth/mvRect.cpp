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