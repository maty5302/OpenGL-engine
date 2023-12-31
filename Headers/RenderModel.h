/**
* @file RenderModel.h
*
* @brief Used to render model with shader and transformations
*
* @author Prudil Mat�j PRU0059
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
	static int ID;
	int objID = -1;
	Model* model;
	ShaderProgram* shaderProgram;
	TransformationComposite* transform;
	Material* material;
public:
	RenderModel(Model* model, ShaderProgram* shader, Material* material, bool setID);
	RenderModel(const float points[], int pointsCount, ShaderProgram* shader, Material* material, bool texture, bool normal);
	void applyTransformations();
	void addTransformation(Transformation* transformation);
	void removeTransformation(Transformation* transformation);
	void render();

	int getID();
	ShaderProgram* getShaderProgram();
	~RenderModel();
};

