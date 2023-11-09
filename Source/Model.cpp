#include "../Headers/Model.h"   
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
	this->rowCount = pointsCount / 6;
}

Model::Model(const float points[], int pointsCount, bool texture, bool normal)
{
	if (texture)
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
	else
	{
		if (normal)
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
	glDrawArrays(GL_TRIANGLES, 0, this->getRowCount());
}

int Model::getVertexCount()
{
	return this->points.size();
}

int Model::getRowCount()
{
	return this->rowCount;
}
