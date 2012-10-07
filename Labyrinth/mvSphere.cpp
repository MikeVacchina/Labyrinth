#include "mvSphere.h"

mvSphere::mvSphere(const char *filename)
{
	radius = 0.0;
	centerX = centerY = centerZ = 0.0;

	if(filename)
	{
		loadMesh(filename);
	}
}


mvSphere::~mvSphere()
{
}

void mvSphere::loadMesh(const char *filename)
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
	centerX = centerY = centerZ = 0.0;

	for(int i=0;i<vertexCount;++i)
	{
		double tmp=0.0;
		for(int j=0;j<3;++j)
			tmp += geometry[i].position[j]*geometry[i].position[j];
		tmp = sqrt(tmp);
		radius += tmp;
		
		centerX += geometry[i].position[0];
		centerY += geometry[i].position[1];
		centerZ += geometry[i].position[2];
	}
	radius /= vertexCount;
	centerX /= vertexCount;
	centerY /= vertexCount;
	centerZ /= vertexCount;
}

mvMesh mvSphere::getMesh()
{
	return mesh;
}
	
void mvSphere::scale(double s)
{
	mesh.scale(s);

	radius *= s;
	centerX *= s;
	centerY *= s;
	centerZ *= s;

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

void mvSphere::translate(double x, double y, double z)
{
	mesh.translate(vec3(x,y,z));

	centerX += x;
	centerY += y;
	centerZ += z;

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

double mvSphere::getMeshRadius()
{
	return radius;
}

void mvSphere::getMeshCenter(double &x, double &y, double &z)
{
	x = centerX;
	y = centerY;
	z = centerZ;
}