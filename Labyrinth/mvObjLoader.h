#ifndef MVOBJLOADER
#define MVOBJLOADER

#include <string>
#include <fstream>

#include "mvMesh.h"

//very simple obj loader
//currently does not handle textures
class mvObjLoader
{
public:
	mvObjLoader();
	mvObjLoader(std::string filename, mvMesh &mesh, std::string &error);
	mvObjLoader(char *filename, mvMesh &mesh, char *error);
	~mvObjLoader();
	
	void loadObj(std::string filename, mvMesh &mesh, std::string &error);
	void loadObj(char *filename, mvMesh &mesh, char *error);

private:
	bool skipCommentLine(std::istream& is);
	void skipLine(std::istream &is);
	bool processLine(mvMesh &mesh, std::istream &is);
};

#endif //MVOBJLOADER