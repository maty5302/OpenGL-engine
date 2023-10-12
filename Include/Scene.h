#pragma once
#include <vector>
#include "Include/RenderModel.h"
class Scene
{
private:
	std::vector<RenderModel*> models;
	Camera* camera;
public:
	Scene();
	~Scene();
	void makeScene();
	void addModel(RenderModel* model);
	void render();
};

