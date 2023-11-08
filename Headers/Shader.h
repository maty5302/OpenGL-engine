/**
* @file Shader.h
*
* @brief Class used to create and use shaders
*
* @author Prudil Mat�j PRU0059
* */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "../Headers/Observer/Observer.h"
#include "Shader/FragmentShader.h"
#include "Shader/VertexShader.h"
class Camera;
class Shader : public Observer
{
private:
	Camera *camera;
	GLuint shader_Program;

public:
	Shader(Camera* camera, VertexShader* vertex, FragmentShader* fragment);
	~Shader();

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