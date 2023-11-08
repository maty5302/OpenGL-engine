#include "../Headers/Shader.h"
#include "../Headers/Camera.h"
#include <string>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "../Headers/FileLoader.h"

Shader::Shader(Camera* camera, VertexShader* vertex, FragmentShader* fragment)
{
	this->camera = camera;
	shader_Program = glCreateProgram();
	glAttachShader(shader_Program, fragment->getFragmentShaderID());
	glAttachShader(shader_Program, vertex->getVertexShaderID());
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

void Shader::update(const char* name, glm::vec4 value)
{
	this->setUniform(name, value);
}

void Shader::update(const char* name, glm::vec3 value)
{
	this->setUniform(name, value);
}

void Shader::update(const char* name, float value)
{
	this->setUniform(name, value);
}

void Shader::update(const char* name, glm::mat4 value)
{
	this->setUniform(name, value);
}

void Shader::update(const char* name, int value)
{
	this->setUniform(name, value);
}

void Shader::setUniform(const char* name, glm::vec4 value)
{
	GLint id = glGetUniformLocation(this->shader_Program, name);
	glUseProgram(this->shader_Program);
	glUniform4f(id, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const char* name, glm::vec3 value)
{
	GLint id = glGetUniformLocation(this->shader_Program, name);
	glUseProgram(this->shader_Program);
	glUniform3f(id, value.x, value.y, value.z);
}


void Shader::setUniform(const char* name, glm::mat4 value)
{
	GLint id = glGetUniformLocation(this->shader_Program, name);
	glUseProgram(this->shader_Program);
	glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}

void Shader::setUniform(const char* name, float value)
{
	GLint id = glGetUniformLocation(this->shader_Program, name);
	glUseProgram(this->shader_Program);
	glUniform1f(id, value);
}

void Shader::setUniform(const char* name, int value)
{
	GLint id = glGetUniformLocation(this->shader_Program, name);
	glUseProgram(this->shader_Program);
	glUniform1i(id, value);
}

void Shader::useShader()
{
	glUseProgram(this->shader_Program);
}

void Shader::cancelShader()
{
	glUseProgram(0);
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
	delete camera;
}
