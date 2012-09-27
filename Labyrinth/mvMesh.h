#ifndef MVMESH
#define MVMESH

#include <vector>

#include "mvSimpleStructs.h"

class vec3
{
public:
	vec3(double _x=0, double _y=0, double _z=0)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	vec3 plus(int val)
	{
		return vec3(x+val, y+val, z+val);
	}

	double x, y, z;
};

class mvMesh
{
public:
	mvMesh();
	~mvMesh();
	
	void addVertex(vec3 v);
	void addFace(vec3 f);
	
	void setColor(vec3 c);
	void setColor(double r, double g, double b);

	mvVertex* getGeometry();
	int countVertices();

	void addMesh(mvMesh &mesh);

	void clear();

private:
	std::vector<vec3> vertices;
	std::vector<vec3> faces;
	std::vector<vec3> colors;
};

#endif // MVMESH