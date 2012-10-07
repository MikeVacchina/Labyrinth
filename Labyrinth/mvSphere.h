#ifndef MVSPHERE
#define MVSPHERE

#include <iostream>

#include "mvObject.h"
#include "mvObjLoader.h"
#include "mvMesh.h"
#include "mvSimpleStructs.h"

//simple sphere object with center and radius
//and allows scaling and translation of mesh
//inherits object class
class mvSphere : public mvObject
{
public:
	mvSphere(const char *filename = NULL);
	~mvSphere();
	
	//reimplement loadMesh
	void loadMesh(const char *filename);
	
	//allow scaling and translation of mesh
	void scale(double s);
	void translate(double x, double y, double z);

	//return mesh radius
	double getMeshRadius();

	//return mesh center
	void getMeshCenter(double &x, double &y, double &z);

private:
	double radius;
	double centerX, centerY, centerZ;
};

#endif //MVSPHERE