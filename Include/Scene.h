#pragma once
#include <vector>
#include "Include/RenderModel.h"
#include "Include/Observer/Subject.h"
class Scene
{
private:
	std::vector<RenderModel*> models;
	Camera* camera;
	Subject* subject;
public:	
	Scene();
	~Scene();
	Camera* getCamera();
	Subject* getSubject();
	void makeScene();
	void addModel(RenderModel* model);
	void render();
};

