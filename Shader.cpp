#include "Shader.h"
#include <string>

Shader::Shader()
{
	vertex_Shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_Shader, 1, &vertex_shader, NULL);
	glCompileShader(vertex_Shader);
	fragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_Shader, 1, &fragment_shader, NULL);
	glCompileShader(fragment_Shader);
	shader_Program = glCreateProgram();
	glAttachShader(shader_Program, fragment_Shader);
	glAttachShader(shader_Program, vertex_Shader);
	glLinkProgram(shader_Program);

	GLint status;
	glGetProgramiv(shader_Program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shader_Program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shader_Program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}


void Shader::useShader()
{
	glUseProgram(this->shader_Program);
}

void Shader::setMatrixModel(glm::mat4 modelMatrix)
{
	GLint idModelTransform = glGetUniformLocation(this->shader_Program, "modelMatrix");
	glUseProgram(this->shader_Program);
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &modelMatrix[0][0]);
}

Shader::~Shader()
{
	glDeleteProgram(shader_Program);
	glDeleteShader(vertex_Shader);
	glDeleteShader(fragment_Shader);
	delete vertex_shader;
	delete fragment_shader;
}
