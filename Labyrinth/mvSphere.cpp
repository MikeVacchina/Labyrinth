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

//reimplement loadMesh function to also determine center and radius based on mesh
void mvSphere::loadMesh(const char *filename)
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
	
	//reset radius and center
	radius = 0.0;
	centerX = centerY = centerZ = 0.0;
	
	//TODO: just noticed radius only works if center is 0,0,0 fix this some time
	for(int i=0;i<vertexCount;++i)
	{
		//add up distances for radius
		double tmp=0.0;
		for(int j=0;j<3;++j)
			tmp += geometry[i].position[j]*geometry[i].position[j];
		tmp = sqrt(tmp);
		radius += tmp;
		
		//add up vertices for center
		centerX += geometry[i].position[0];
		centerY += geometry[i].position[1];
		centerZ += geometry[i].position[2];
	}

	//average
	radius /= vertexCount;
	centerX /= vertexCount;
	centerY /= vertexCount;
	centerZ /= vertexCount;
}
	
void mvSphere::scale(double s)
{
	//scale mesh
	mesh.scale(s);

	//scale radius
	radius *= s;

	//scale center
	centerX *= s;
	centerY *= s;
	centerZ *= s;

	//reload geometry and vertex count
	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

void mvSphere::translate(double x, double y, double z)
{
	//translate mesh
	mesh.translate(vec3(x,y,z));

	//translate center
	centerX += x;
	centerY += y;
	centerZ += z;

	//reload geometry and vertex count
	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

double mvSphere::getMeshRadius()
{
	//return mesh radius
	return radius;
}

void mvSphere::getMeshCenter(double &x, double &y, double &z)
{
	//return mesh center
	x = centerX;
	y = centerY;
	z = centerZ;
}