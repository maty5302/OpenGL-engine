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
	GLuint IBO = 0;
	std::vector<float> points;
	int rowCount = 0;
public:
	Model(const float points[], int pointsCount, bool texture, bool normal);
	Model(std::vector<float> verticies, std::vector<GLuint> indicies);
	~Model();
	void useModel();
	int getVertexCount();
	int getRowCount();
};

