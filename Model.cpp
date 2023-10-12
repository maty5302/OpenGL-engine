#include "Include/Model.h"   
#include<array> 
#include <vcruntime_string.h>

Model::Model(const float pointss[], int pointsCount)
{
	//ruzne modely tridy a vao
	this->points = std::vector<float>();
	for (size_t i = 0; i < pointsCount; i++)
	{
		this->points.push_back(pointss[i]);
	}
	this->VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), pointss, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (GLvoid*)(3*sizeof(float)));
}

void Model::useModel()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->getRowCount());
}

int Model::getVertexCount()
{
	return this->points.size();
}

int Model::getRowCount()
{
	return this->points.size()/6;
}
