#include "../../Headers/Shader/VertexShader.h"
#include "../../Headers/FileLoader.h"

VertexShader::VertexShader(const char* path)
{
	std::string vs = FileLoader::loadShader(path);
	this->vertex_shader = vs.c_str();
	this->VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderID, 1, &vertex_shader, NULL);
	glCompileShader(VertexShaderID);
}

VertexShader::~VertexShader()
{
	delete &vertex_shader;
}

GLuint VertexShader::getVertexShaderID()
{
	return this->VertexShaderID;
}
