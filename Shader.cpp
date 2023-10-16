#include "Include/Shader.h"
#include "Include/Camera.h"
#include <string>
#include <glm/ext/matrix_transform.hpp>

Shader::Shader(Camera* camera, const char* vertex_shaderr, const char* fragment_shaderr)
{
	this->camera = camera;
	vertex_Shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_Shader, 1, &vertex_shaderr, NULL);
	glCompileShader(vertex_Shader);
	fragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_Shader, 1, &fragment_shaderr, NULL);
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

void Shader::update()
{
	glUseProgram(this->shader_Program);
	GLint idViewTransform = glGetUniformLocation(this->shader_Program, "viewMatrix");
	GLint idProjectionTransform = glGetUniformLocation(this->shader_Program, "projectionMatrix");
	glUniformMatrix4fv(idViewTransform, 1, GL_FALSE, &this->camera->getViewMatrix()[0][0]);
	glUniformMatrix4fv(idProjectionTransform, 1, GL_FALSE, &this->camera->getProjectionMatrix()[0][0]);
}


void Shader::useShader()
{
	glUseProgram(this->shader_Program);
}

void Shader::setMatrixModel(glm::mat4 modelMatrix)
{
	GLint idProjectionTransform = glGetUniformLocation(this->shader_Program, "projectionMatrix");
	GLint idViewTransform = glGetUniformLocation(this->shader_Program, "viewMatrix");
	GLint idModelTransform = glGetUniformLocation(this->shader_Program, "modelMatrix");
	glUseProgram(this->shader_Program);
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(idViewTransform, 1, GL_FALSE, &this->camera->getViewMatrix()[0][0]);
	glUniformMatrix4fv(idProjectionTransform, 1, GL_FALSE, &this->camera->getProjectionMatrix()[0][0]);
}


Shader::~Shader()
{
	glDeleteProgram(shader_Program);
	glDeleteShader(vertex_Shader);
	glDeleteShader(fragment_Shader);
	delete camera;
}
