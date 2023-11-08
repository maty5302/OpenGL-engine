#include "../../Headers/Shader/FragmentShader.h"
#include "../../Headers/FileLoader.h"

FragmentShader::FragmentShader(const char* path)
{
	std::string fs = FileLoader::loadShader(path);
	this->fragment_shader = fs.c_str();
	this->FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderID, 1, &fragment_shader, NULL);
	glCompileShader(FragmentShaderID);
}

FragmentShader::~FragmentShader()
{
	delete &FragmentShaderID;
	delete fragment_shader;
}

GLuint FragmentShader::getFragmentShaderID()
{
	return this->FragmentShaderID;
}
