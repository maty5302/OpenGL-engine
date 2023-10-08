#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
class Shader
{
private:
	const char* vertex_shader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 vertex_Color;"
		"out vec3 colorInput;"
		"uniform mat4 modelMatrix;"
		"void main() {"
		"		gl_Position = modelMatrix * vec4 (position, 1.0);" //gl_Position = vec4(position, 1.0f);
		"		colorInput = vertex_Color;"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"in vec3 colorInput;"
		"out vec4 color;"
		"void main () {"
		"     color = vec4(colorInput, 1.0f);"
		"}";

	GLuint vertex_Shader;
	GLuint fragment_Shader;
	GLuint shader_Program;
public:
	Shader();
	void useShader();
	void setMatrixModel(glm::mat4 modelMatrix);
	~Shader();
};

