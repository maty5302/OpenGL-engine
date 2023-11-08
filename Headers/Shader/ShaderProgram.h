/**
* @file ShaderProgram.h
*
* @brief Class used to create and use shaderPrograms
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "../Observer/Observer.h"
#include "FragmentShader.h"
#include "VertexShader.h"
class Camera;
class ShaderProgram : public Observer
{
private:
	Camera *camera;
	GLuint shader_Program;

public:
	ShaderProgram(Camera* camera, VertexShader* vertex, FragmentShader* fragment);
	~ShaderProgram();

	void update (const char* name, glm::vec4 value) override;
	void update(const char* name, glm::vec3 value) override;
	void update(const char* name, float value) override;
	void update(const char* name, glm::mat4 value) override;
	void update(const char* name, int value) override;
	
	void setUniform(const char* name, glm::vec4 value);
	void setUniform(const char* name, glm::vec3 value);
	void setUniform(const char* name, glm::mat4 value);
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	
	void useShader();
	void cancelShader();
	void setMatrixModel(glm::mat4 modelMatrix);	
};