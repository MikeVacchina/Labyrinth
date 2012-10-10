#include "mvObject.h"


mvObject::mvObject()
{
	//set default values
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
	
	//load mesh
	mvObjLoader(filename, mesh, error);

	//check for error
	if(error != "")
	{
        std::cerr << "[ERROR] " << filename << " FAILED TO LOAD";
		std::cerr << error;
		return;
	}
	
	//set geometry and vertex count based on mesh
	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

mvMesh mvObject::getMesh()
{
	//return copy of mesh
	return mesh;
}

void mvObject::setColor(double r, double g, double b)
{
	//set color for entire mesh
	mesh.setColor(r, g, b);
	//reload geometry
	geometry = mesh.getGeometry();
}

int mvObject::sizeofgeometry()
{
	//return size of geometry
	return vertexCount*sizeof(mvVertex);
}