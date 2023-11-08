#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class VertexShader
{
private:
	GLuint VertexShaderID = 0;
	const char* vertex_shader;
public:
	VertexShader(const char* path);
	~VertexShader();
	GLuint getVertexShaderID();
};

