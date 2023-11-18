#include "../Headers/Model.h"   
#include<array> 
#include <vcruntime_string.h>
#include "glm/vec4.hpp"

Model::Model(const float points[], int pointsCount, bool texture, bool normal)
{
	if (texture && normal)
	{
		this->points = std::vector<float>();
		for (size_t i = 0; i < pointsCount; i++)
		{
			this->points.push_back(points[i]);
		}
		this->VBO = 0;
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), points, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		this->VAO = 0;
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));
		this->rowCount = pointsCount / 8;
	}
	else if(texture && !normal)
	{
		this->points = std::vector<float>();
		for (size_t i = 0; i < pointsCount; i++)
		{
			this->points.push_back(points[i]);
		}
		this->VBO = 0;
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), points, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		this->VAO = 0;
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(3 * sizeof(float)));
		this->rowCount = pointsCount / 8;

	}
	else if (normal)
	{
		this->points = std::vector<float>();
		for (size_t i = 0; i < pointsCount; i++)
		{
			this->points.push_back(points[i]);
		}
		this->VBO = 0;
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), points, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		this->VAO = 0;
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(3 * sizeof(float)));
		this->rowCount = pointsCount / 6;
	}
	else
	{
		this->points = std::vector<float>();
		for (size_t i = 0; i < pointsCount; i++)
		{
			this->points.push_back(points[i]);
		}
		this->VBO = 0;
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), points, GL_STATIC_DRAW);

		//Vertex Array Object (VAO)
		this->VAO = 0;
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glEnableVertexAttribArray(0); //enable vertex attributes
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (GLvoid*)0);
		this->rowCount = pointsCount / 3;
	}
}

Model::Model(std::vector<float> verticies, std::vector<GLuint> indicies)
{
	this->VAO = 0;
	this->VBO = 0;
	this->IBO = 0;
	

	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(6 * sizeof(float)));


	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

	this->rowCount = indicies.size();
}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	for(auto i : this->points)
		delete &i;
}

void Model::useModel()
{
	glBindVertexArray(VAO);
	if (this->IBO != 0)
	{
		glDrawElements(GL_TRIANGLES, this->rowCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, this->rowCount);
	}
	glBindVertexArray(0);
}

int Model::getVertexCount()
{
	return this->points.size();
}

int Model::getRowCount()
{
	return this->rowCount;
}
