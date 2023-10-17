#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "../Include/Observer/Observer.h"
class Camera;
class Shader : public Observer
{
private:
	Camera *camera;
	GLuint vertex_Shader;
	GLuint fragment_Shader;
	GLuint shader_Program;

public:
	Shader(Camera* camera, const char* vertex_shaderr, const char* fragment_shaderr);
	void update() override;
	void useShader();
	void setMatrixModel(glm::mat4 modelMatrix);
	~Shader();
};

