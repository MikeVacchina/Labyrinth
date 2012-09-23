#include "mvObjLoader.h"


mvObjLoader::mvObjLoader()
{
}


mvObjLoader::~mvObjLoader()
{
}

mvObjLoader::mvObjLoader(std::string filename, mvMesh &mesh, std::string &error)
{
	loadObj(filename, mesh, error);
}

mvObjLoader::mvObjLoader(char *filename, mvMesh &mesh, char *error)
{
	loadObj(filename, mesh, error);
}
	
void mvObjLoader::loadObj(std::string filename, mvMesh &mesh, std::string &error)
{
	char *e=NULL;
	char *fn=new char[filename.size()+1];
	fn[filename.size()+1] = NULL;

	std::strcpy(fn,filename.c_str());

	loadObj(fn, mesh, e);
	if(e)
		error = std::string(e);
}

void mvObjLoader::loadObj(char *filename, mvMesh &mesh, char *error)
{
	mesh.clear();

	std::ifstream ifs(filename, std::ios::in);
	if(!ifs)
	{
		error = "[ERROR] CANNOT OPEN FILE!";
		return;
	}

	while(skipCommentLine(ifs))
	{
		if(!processLine(mesh,ifs))
			break;
	}
}

bool mvObjLoader::skipCommentLine(std::istream& is)
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

void mvObjLoader::skipLine(std::istream &is)
{
	char next;
	is >> std::noskipws;
	while( (is>>next) && (next != '\n') );
}
	
bool mvObjLoader::processLine(mvMesh &mesh, std::istream &is)
{
	std::string ele;
	double x, y, z;

	if( !(is >> ele) )
		return false;

	if(ele == "mtllib")
	{
		//nothing to do here...
		skipLine(is);
	}
	else if(ele == "usemtl")
	{
		//nothing to do here...
		skipLine(is);
	}
	else if(ele == "v")
	{
		is >> x >> y >> z;
		mesh.addVertex( vec3(x, y, z) );
	}
	else if(ele == "vt")
	{
		//nothing to do here...
		skipLine(is);
	}
	else if(ele == "vn")
	{
		//nothing to do here...
		skipLine(is);
	}
	else if(ele == "f")
	{
		//assume for now only triangles with only vertices
		is >> x >> y >> z;
		mesh.addFace( vec3(x, y, z) );
	}
	else
	{
		skipLine(is);
	}
	return true;
}