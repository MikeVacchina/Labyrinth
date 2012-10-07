#ifndef MVSIMPLESTRUCTS
#define MVSIMPLESTRUCTS

#include <gl/glew.h> // glew must be included before the main gl libs
#include <gl/glut.h> // doing otherwise causes compiler shouting

#include "defines.h"

struct mvVertex
{
    GLfloat position[3];
    GLfloat color[3];
};

class mvMouseData
{
public:
	mvMouseData(double _theda=0.0, double _phi=0.0)
	{
		theda = _theda;
		phi   = _phi;
	}

	double theda;
	double phi;
};

class mvKeyboardData
{
public:
	mvKeyboardData(enum _keyState ks = KEY_INVALID)
	{
		keyState = ks;
	}

	int keyState;
};

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

	vec3 plus(vec3 val)
	{
		return vec3(x+val.x, y+val.y, z+val.z);
	}

	vec3 mulScalar(double val)
	{
		return vec3(x*val, y*val, z*val);
	}

	vec3 mul(vec3 val)
	{
		return vec3(x*val.x, y*val.y, z*val.z);
	}

	double x, y, z;
};

class mvWall
{
public:
	mvWall(double s=0, double e=0, int i=-1)
	{
		start = s;
		end = e;
		id = i;
	}

	bool operator<(mvWall &other)
	{
		return start < other.start;
	}

	double start, end;
	int id;
};

class mvHole
{
public:
	mvHole(double _x=0.0, double _z=0.0, double _r=0.0)
	{
		x = _x;
		z = _z;
		r = _r;
	}

	double x, z, r;
};

class mvGoal
{
public:
	mvGoal(double _x=0.0, double _z=0.0, double _r=0.0)
	{
		x = _x;
		z = _z;
		r = _r;
	}

	double x, z, r;
};

#endif //MVSIMPLESTRUCTS

