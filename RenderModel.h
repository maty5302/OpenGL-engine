#pragma once
#include <string>
#include <iostream>
#include <glm/vec4.hpp>
#include "Model.h"
#include "Shader.h"
#include "Transformation.h"
#include "TransformationComposite.h"
class RenderModel
{
private: 
	Model* model;
	Shader* shader;
	TransformationComposite* transform;
public:
	RenderModel(const float points[], int pointsCount);
	void applyTransformations();
	void addTransformation(Transformation* transformation);
	void removeTransformation(Transformation* transformation);
	void render();
	~RenderModel();
};

