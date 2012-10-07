#include "mvCircle.h"


mvCircle::mvCircle()
{
	center = glm::vec3(0.0);
	radius = 0.0;
}


mvCircle::~mvCircle()
{
}

void mvCircle::loadMesh(const char *filename)
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

	radius = 0.0;
	center = glm::vec3(0.0);

	for(int i=0;i<vertexCount;++i)
	{
		double tmp=0.0;
		for(int j=0;j<3;++j)
			tmp += geometry[i].position[j]*geometry[i].position[j];
		tmp = sqrt(tmp);
		radius += tmp;
		
		center.x += geometry[i].position[0];
		center.y += geometry[i].position[1];
		center.z += geometry[i].position[2];
	}
	radius /= vertexCount;
	center.x /= vertexCount;
	center.y /= vertexCount;
	center.z /= vertexCount;
}
