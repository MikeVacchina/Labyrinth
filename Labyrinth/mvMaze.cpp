#include "mvMaze.h"

mvMaze::mvMaze()
{
	rect.loadMesh("cube.obj");
}

mvMaze::~mvMaze()
{
}

bool mvMaze::loadMaze(const char *filename)
{
	std::ifstream ifs(filename, std::ios::in);

	while(skipCommentLine(ifs))
	{
		if(!processLine(ifs))
			break;
	}

	init();

	return true;
}

void mvMaze::setSize(double w, double d)
{
	mvRect tmp;
	tmp = rect;
	
	tmp.translate(0.0,-1.0,0.0);
	tmp.scale(w/2.0,0.25,d/2.0);
	tmp.setColor(0.0,1.0,0.0);

	mesh = tmp.getMesh();
}

void mvMaze::setWall(double x, double z, double w, double d)
{
	mvRect tmp;

	int wallCount = xWalls.size();

	tmp = rect;
	
	tmp.scale(w/2.0,0.5,d/2.0);
	tmp.translate(x,0.5,z);
	tmp.setColor(0.0,0.0,1.0);

	mesh.addMesh(tmp.getMesh());
	
	xWalls.push_back(mvWall(x-(w/2), x+(w/2.0), wallCount+1));
	zWalls.push_back(mvWall(z-(d/2), z+(d/2.0), wallCount+1));
}

void mvMaze::setHole(double x, double z, double r)
{
	holes.push_back(mvHole(x, z, r));
}

void mvMaze::init()
{
	std::sort(xWalls.begin(), xWalls.end());
	std::sort(zWalls.begin(), zWalls.end());

	geometry = mesh.getGeometry();
	vertexCount = mesh.countVertices();
}

std::vector<mvWall> mvMaze::getXWalls()
{
	return xWalls;
}

std::vector<mvWall> mvMaze::getZWalls()
{
	return zWalls;
}

std::vector<mvHole> mvMaze::getHoles()
{
	return holes;
}

glm::vec3 mvMaze::getGoal()
{
	return glm::vec3(goal.pos.x, goal.pos.z, goal.radius);
}

glm::vec3 mvMaze::getBegin()
{
	return begin;
}

bool mvMaze::skipCommentLine(std::istream& is)
{
	char next;
	while(is >> std::skipws >> next)
	{
		is.putback(next);
		if(next == '#')
			skipLine(is);
		else
			return true;
	}
	return false;
}

void mvMaze::skipLine(std::istream &is)
{
	char next;
	is >> std::noskipws;
	while( (is>>next) && (next != '\n') );
}
	
bool mvMaze::processLine(std::istream &is)
{
	std::string ele;

	if( !(is >> ele) )
		return false;

	if(ele == "f")
	{
		std::string tmp;
		is >> tmp;
		mvObject floor;
		floor.loadMesh(tmp.c_str());
		floor.setColor(0.0,1.0,0.0);
		mesh.addMesh(floor.getMesh());
	}
	else if(ele == "c")
	{
		std::string tmp;
		is >> tmp;
		//load basic cube
		rect.loadMesh(tmp.c_str());
	}
	else if(ele == "h")
	{
		double x, z, r;
		is >> x >> z >> r;
		setHole(x,z,r);
	}
	else if(ele == "w")
	{
		double x, z, sx, sz;
		is >> x >> z >> sx >> sz;
		setWall(x, z, sx, sz);
	}
	else if(ele == "b")
	{
		float x, z;
		is >> x >> z;
		begin.x = x;
		begin.y = 0;
		begin.z = z;
	}
	else if(ele == "g")
	{
		std::string tmp;
		is >> tmp;
		goal.loadMesh(tmp.c_str());
		goal.setColor(1.0,0.0,0.0);
		mesh.addMesh(goal.getMesh());
	}
	else
	{
		skipLine(is);
	}
	return true;
}