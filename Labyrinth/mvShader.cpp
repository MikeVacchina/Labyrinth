#include "mvShader.h"


mvShader::mvShader(char *filename)
{
	shaderRdy = false;
	if(filename)
		loadShader(filename);
}

mvShader::~mvShader()
{
}

void mvShader::loadShader(char* filename)
{
	int len;

	std::ifstream file;
	file.open(filename, std::ios::in); // opens as ASCII
	if(!file)
	{
		shaderRdy = false;
		error = "[ERROR] FAILED TO OPEN FILE!";
		return;
	}

	char *ShaderSource=NULL;

	len = getFileLength(file);
    
	if (len==0) // Error: Empty File 
	{
		shaderRdy = false;
		error = "[ERROR] FILE IS EMPTY!";
		return;
	}
    
	ShaderSource = new char[len+1];
	if (ShaderSource == 0) // can't reserve memory
	{
		shaderRdy = false;
		error = "[ERROR] CANNOT RESERVE MEMORY!";
		return;
	}
   
	// len isn't always strlen cause some characters are stripped in ascii read...
	// it is important to 0-terminate the real length later, len is just max possible value... 
	ShaderSource[len] = 0; 

	unsigned int i=0;
	while (file.good())
	{
		ShaderSource[i] = file.get(); // get character from file.
		if (!file.eof())
		i++;
	}
    
	ShaderSource[i] = 0; // 0-terminate it at the correct position
    
	file.close();

	shader = std::string(ShaderSource);

	shaderRdy = true;
	error = "";
}
	
const char* mvShader::getShaderString()
{
	return shader.c_str();
}

bool mvShader::isShaderRdy()
{
	return shaderRdy;
}

std::string mvShader::getError()
{
	return error;
}

/// This function is courtesy of the interwebz at http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php
unsigned long mvShader::getFileLength(std::ifstream& file)
{
	if(!file.good()) return 0;
    
	unsigned long pos=file.tellg();
	file.seekg(0,std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);
    
	return len;
}