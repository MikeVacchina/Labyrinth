#ifndef MVMESH
#define MVMESH

#include <vector>

#include "mvSimpleStructs.h"

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
	
	void scale(double s);
	void scale(vec3 s);
	void translate(vec3 v);

	void clear();

private:
	std::vector<vec3> vertices;
	std::vector<vec3> faces;
	std::vector<vec3> colors;
};

#endif // MVMESH