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
#include "../Headers/Model.h"
#include "../Headers/Shader/ShaderProgram.h"
#include "../Headers/Transformation/Transformation.h"
#include "../Headers/Transformation/TransformationComposite.h"
#include "../Headers/Material.h"
class RenderModel
{
private: 
	Model* model;
	ShaderProgram* shaderProgram;
	TransformationComposite* transform;
	Material* material;
public:
	RenderModel(Model* model, ShaderProgram* shader, Material* material);
	RenderModel(const float points[], int pointsCount, ShaderProgram* shader, Material* material); 
	RenderModel(const float points[], int pointsCount, ShaderProgram* shader, Material* material, bool texture);
	void applyTransformations();
	void addTransformation(Transformation* transformation);
	void removeTransformation(Transformation* transformation);
	void render();
	ShaderProgram* getShaderProgram();
	~RenderModel();
};

