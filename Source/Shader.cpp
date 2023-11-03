#include "../Headers/Shader.h"
#include "../Headers/Camera.h"
#include <string>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "../Headers/FileLoader.h"

Shader::Shader(Camera* camera, const char* path_vertex_shader, const char* path_fragment_shader)
{
	std::string vertexShaderSource = FileLoader::loadShader(path_vertex_shader);
	std::string fragmentShaderSource = FileLoader::loadShader(path_fragment_shader);
	this->vertex_shader = vertexShaderSource.c_str();
	this->fragment_shader = fragmentShaderSource.c_str();
	this->camera = camera;
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

void Shader::update(Subject* s)
{
	if (Camera* c = dynamic_cast<Camera*>(s))
	{
		GLint idViewTransform = glGetUniformLocation(this->shader_Program, "viewMatrix");
		GLint idProjectionTransform = glGetUniformLocation(this->shader_Program, "projectionMatrix");
		GLint idCameraPosition = glGetUniformLocation(this->shader_Program, "cameraPosition");
		glUseProgram(this->shader_Program);
		glUniformMatrix4fv(idViewTransform, 1, GL_FALSE, &this->camera->getViewMatrix()[0][0]);
		glUniformMatrix4fv(idProjectionTransform, 1, GL_FALSE, &this->camera->getProjectionMatrix()[0][0]);
		glUniform3f(idCameraPosition, this->camera->getEye().x, this->camera->getEye().y, this->camera->getEye().z);
	}
	if (Light* l = dynamic_cast<Light*>(s))
	{
		GLint idLightPosition = glGetUniformLocation(this->shader_Program, "lightPosition");
		GLint idLightColor = glGetUniformLocation(this->shader_Program, "lightColor");
		GLint idLightAttenuation = glGetUniformLocation(this->shader_Program, "attenuation");
		glUseProgram(this->shader_Program);
		glUniform3f(idLightPosition, l->getPosition().x, l->getPosition().y, l->getPosition().z);
		glUniform3f(idLightColor, l->getColor().x, l->getColor().y, l->getColor().z);
		glUniform1f(idLightAttenuation, l->getAttenuation());
	}
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
	glDeleteShader(vertex_Shader);
	glDeleteShader(fragment_Shader);
	delete camera;
}
