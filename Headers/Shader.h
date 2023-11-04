/**
* @file Shader.h
*
* @brief Class used to create and use shaders
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "../Headers/Observer/Observer.h"
class Camera;
class Shader : public Observer
{
private:
	const char* vertex_shader;
	const char* fragment_shader;
	Camera *camera;
	GLuint vertex_Shader;
	GLuint fragment_Shader;
	GLuint shader_Program;

public:
	Shader(Camera* camera, const char* path_vertex_shader, const char* path_fragment_shader);
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