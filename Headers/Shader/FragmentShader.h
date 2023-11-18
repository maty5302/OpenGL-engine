/**
* @file FragmentShader.h
*
* @brief Class used for creating fragment shader
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class FragmentShader
{
private:
	GLuint FragmentShaderID = 0;
	const char* fragment_shader;
public:
	FragmentShader(const char* path);
	~FragmentShader();
	GLuint getFragmentShaderID();
};

