/**
* @file Model.h
*
* @brief Used for creating models from points
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Model
{
private:
	GLuint VBO = 0;
	GLuint VAO = 0;
	std::vector<float> points;
public:
	Model(const float points[], int pointsCount);
	Model(const float points[], int pointsCount, bool texture);
	~Model();
	void useModel();
	int getVertexCount();
	int getRowCount();
};

