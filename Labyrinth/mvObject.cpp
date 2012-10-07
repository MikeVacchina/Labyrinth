#include "mvObject.h"


mvObject::mvObject()
{
	geometry = NULL;
	vertexCount = 0;
	
	acc = glm::vec3(0.0);
	vel = glm::vec3(0.0);
	pos = glm::vec3(0.0);
}

mvObject::~mvObject()
{
	//TODO: fix: seems to be a bug with this
	//if(geometry && vertexCount > 1)
	//	delete [] geometry;
	//else if(geometry && vertexCount > 0)
	//	delete geometry;
}

void mvObject::loadMesh(const char *filename)
{
	std::string error;
	mvObjLoader(filename, mesh, error);

	if(error != "")
	{
        std::cerr << "[ERROR] " << filename << " FAILED TO LOAD: ";
		std::cerr << error;
		return;
	}

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

mvMesh mvObject::getMesh()
{
	return mesh;
}

void mvObject::setColor(double r, double g, double b)
{
	mesh.setColor(r, g, b);
	geometry = mesh.getGeometry();
}

int mvObject::sizeofgeometry()
{
	return vertexCount*sizeof(mvVertex);
}