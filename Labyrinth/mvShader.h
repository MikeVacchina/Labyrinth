#ifndef MVSHADER
#define MVSHADER

#include <string>
#include <fstream>

//shader loading class
class mvShader
{
public:
	mvShader(char *filename = NULL);
	~mvShader();

	void loadShader(char* filename);
	
	const char* getShaderString();

	bool isShaderRdy();
	std::string getError();

private:
	unsigned long mvShader::getFileLength(std::ifstream& file);

	std::string shader;
	bool shaderRdy;
	std::string error;
};

#endif //MVSHADER