/**
* @file RenderModel.h
*
* @brief Used to render model with shader and transformations
*
* @author Prudil Matìj PRU0059
* */
#pragma once
#include <string>
#include <iostream>
#include <glm/vec4.hpp>
#include "../Include/Model.h"
#include "../Include/Shader.h"
#include "../Include/Transformation/Transformation.h"
#include "../Include/Transformation/TransformationComposite.h"
class RenderModel
{
private: 
	Model* model;
	Shader* shader;
	TransformationComposite* transform;
public:
	RenderModel(const float points[], int pointsCount,Shader* shader);
	void applyTransformations();
	void addTransformation(Transformation* transformation);
	void removeTransformation(Transformation* transformation);
	void render();
	~RenderModel();
};

