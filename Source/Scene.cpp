#include "../Headers/Scene.h"
#include "../Headers/Camera.h"
#include "../Headers/FileLoader.h";
#include "../Headers/Transformation/Rotation.h"
#include "../Headers/Transformation/Translation.h"
#include "../Headers/Transformation/Scale.h"
#include "../Headers/Light/PointLight.h"
#include "../Headers/Light/DirectionLight.h"
#include "../Headers/Light/SpotLight.h"
#include "../Models/sphere.hpp";
#include "../Models/plain.hpp";
#include "../Models/suzi_smooth.hpp";
#include "../Models/suzi_flat.hpp";
#include "../Models/tree.hpp";
#include "../Models/gift.hpp";
#include "../Models/bushes.hpp"
#include "../Headers/Texture.h"

void Scene::attachObservers()
{
	for (auto light : this->lights)
		for (auto observer : this->shaders)
			light->addObserver(observer);
	this->camera->notify();
	this->notifyLights();
}

Scene::Scene()
{
	this->camera = new Camera();
	this->lights = std::vector<Light*>();
	this->models = std::vector<RenderModel*>();
	this->shaders = std::vector<Shader*>();
}

Scene::~Scene()
{
	delete this->camera;

	for (auto model : this->models)
		delete model;
	for(auto light : this->lights)
		delete light;
	for(auto shader : this->shaders)
		delete shader;
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::notifyLights()
{
	int i = 0;
	for (auto light : this->lights)
	{
		if (PointLight* l = dynamic_cast<PointLight*>(light))
		{
			light->notify(i);
			i++;
		}
		else
			light->notify();
		
	}		
}

void Scene::makeSceneTrees()
{
	this->animated = false;
	srand(time(NULL));
	VertexShader* vertexShader = new VertexShader("Shaders/vertexlights.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhong.frag");
	VertexShader* vertexShaderTexture = new VertexShader("Shaders/vertexLightsTexture.vert");
	FragmentShader* fragmentShaderTexture = new FragmentShader("Shaders/fragmentPhongTexture.frag");


	this->lights.push_back(new DirectionLight(glm::vec3(0.0, -1.0, 0.0), glm::vec3(1.0f)));
	/*this->lights.push_back(new PointLight(glm::vec3(5.0f, 2.f, 0.0f), glm::vec3(1.0f)));
	this->lights.push_back(new PointLight(glm::vec3(20.0f, 20.f, 0.0f), glm::vec3(1.0f)));
	this->lights.push_back(new PointLight(glm::vec3(-20.0f, 20.f, 0.0f), glm::vec3(1.0f)));*/
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 20.f, 20.0f), glm::vec3(1.0f)));
	this->lights.push_back(new SpotLight(this->camera->getEye(), glm::vec3(1.0f), this->camera->getTarget(), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	this->camera->setEye(glm::vec3(0.0f, 15.0f, -10.0f));
	this->camera->setTarget(glm::vec3(0.0f, 0.0f, -1.0f));
	Model* model_tree = new Model(tree, sizeof(tree) / sizeof(float));
	Model* model_bushes = new Model(bushes, sizeof(bushes) / sizeof(float));
	Material* m = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.09f, 0.77f, 0.09f, 1.0f));
	Texture* t = new Texture("Textures/grass.png", 2);
	Material* m_plain = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),t);
	for (size_t i = 0; i < 275; i++)
	{
		this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
		this->addModel(new RenderModel(model_tree, this->shaders[i],m), this->shaders[i]);
		this->models[i]->addTransformation(new Rotation(rand() % 360,glm::vec3(0.0f, 1.0f, 0.0f)));
		this->models[i]->addTransformation(new Scale(glm::vec3(rand() % 10 / 10.0f + 0.5f)));
		float x = rand() % 50;
		float z = rand() % 50 ;
		this->models[i]->addTransformation(new Translation(glm::vec3(x, 0.0f, z)));
		this->models[i]->applyTransformations();
	}
	for (size_t i = 275; i < 295; i++)
	{
		this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
		this->addModel(new RenderModel(model_bushes, this->shaders[i],m), this->shaders[i]);
		this->models[i]->addTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->models[i]->addTransformation(new Scale(glm::vec3(rand() % 10 / 10.0f + 1.5f)));
		float x = rand() % 50;
		float z = rand() % 50;
		this->models[i]->addTransformation(new Translation(glm::vec3(x, 0.0f, z)));
		this->models[i]->applyTransformations();
	}
	Material* m_ball = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Material* m_suzi = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f));

	this->shaders.push_back(new Shader(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->addModel(new RenderModel(plain, sizeof(plain) / sizeof(float), this->shaders[295],m_plain,true), this->shaders[295]);
	this->models[295]->addTransformation(new Scale(glm::vec3(100.0f)));
	this->models[295]->applyTransformations();
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));	
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[296],m_ball), this->shaders[296]);
	this->models[296]->addTransformation(new Scale(glm::vec3(0.5f)));
	this->models[296]->addTransformation(new Translation(glm::vec3(0.0f, 5.0f, 10.0f)));
	this->models[296]->applyTransformations();
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->addModel(new RenderModel(gift, sizeof(gift) / sizeof(float), this->shaders[297], m_ball), this->shaders[297]);
	this->models[297]->addTransformation(new Scale(glm::vec3(2.5f)));
	this->models[297]->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 8.0f)));
	this->models[297]->applyTransformations();
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->addModel(new RenderModel(suziSmooth, sizeof(suziSmooth) / sizeof(float), this->shaders[298], m_suzi), this->shaders[298]);
	this->models[298]->addTransformation(new Scale(glm::vec3(1.5f)));
	this->models[298]->addTransformation(new Translation(glm::vec3(0.0f, 2.5f, 0.0f)));
	this->models[298]->applyTransformations();
	this->attachObservers();
}

void Scene::makeScenePhong()
{
	this->animated = false;
	//Scene 4 spheres and light in the middle of them
	VertexShader* vertexShader = new VertexShader("Shaders/vertexlights.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhong.frag");

	Material* m = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.385, 0.647, 0.812, 1.0));
	Material* m2 = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.385, 0.647, 0.812, 1.0));
	
	this->lights.push_back(new DirectionLight(glm::vec3(3.0, 2.0, 0.0), glm::vec3(1.0f)));
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f)));
	this->lights.push_back(new SpotLight(this->camera->getEye(), glm::vec3(1.0f), this->camera->getTarget(), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[0],m2), this->shaders[0]);
	this->models[0]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(-2.0f, 0.0f, 0.0f)));
	this->models[0]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[1],m), this->shaders[1]);
	this->models[1]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	this->models[1]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[2],m), this->shaders[2]);
	this->models[2]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, 0.0f)));
	this->models[2]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[3],m), this->shaders[3]);
	this->models[3]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	this->models[3]->applyTransformations();
	this->attachObservers();
}


void Scene::makeSceneTest()
{
	VertexShader* vertexShader = new VertexShader("Shaders/vertex.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragment.frag");
	this->animated = false;
	this->lights.push_back(new DirectionLight(glm::vec3(3.0, 2.0, 0.0), glm::vec3(1.0f)));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	Model* plain_textured = new Model(plain, sizeof(plain) / sizeof(float), true);
	Texture* texture = new Texture("Textures/test.png", 0);
 	Material* m = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.09f, 0.73f, 0.09f, 1.0f),texture);
	this->addModel(new RenderModel(plain_textured, this->shaders[0], m), this->shaders[0]);
	this->attachObservers();
}

void Scene::makeSceneResizeTest()
{
	VertexShader* vertexShaderCons = new VertexShader("Shaders/vertexConstant.vert");
	VertexShader* vertexShader = new VertexShader("Shaders/vertexlights.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhong.frag");
	FragmentShader* fragmentShaderCons = new FragmentShader("Shaders/fragmentConstant.frag");
	FragmentShader* fragmentShaderBlinn = new FragmentShader("Shaders/fragmentBlinn.frag");
	FragmentShader* fragmentShaderLambert = new FragmentShader("Shaders/fragmentLambert.frag");

	this->animated = false;
	//Scene objects with different shaders, constant, lambert and phong //todo add light and blinn-phong shader
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	Material* m = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.09f, 0.73f, 0.09f, 1.0f));
	this->shaders.push_back(new Shader(this->camera, vertexShaderCons, fragmentShaderCons));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShaderLambert));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShaderBlinn));

	this->addModel(new RenderModel(tree, sizeof(tree) / sizeof(float), this->shaders[0],m), this->shaders[0]);
	this->addModel(new RenderModel(suziFlat, sizeof(suziFlat) / sizeof(float), this->shaders[1],m), this->shaders[1]);
	this->addModel(new RenderModel(suziSmooth, sizeof(suziSmooth) / sizeof(float), this->shaders[2],m), this->shaders[2]);
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[3],m), this->shaders[3]);

	for(RenderModel* model : this->models)
		model->addTransformation(new Scale(glm::vec3(0.7f)));

	this->models[0]->addTransformation(new Translation(glm::vec3(-2.5f, 2.5f, 0.0f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(2.5f, 2.5f, 0.0f)));
	this->models[2]->addTransformation(new Translation(glm::vec3( - 2.5f, -2.5f, 0.0f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(2.5f, -2.5f, 0.0f)));

	this->models[0]->addTransformation(new Scale(glm::vec3(0.3f)));
	
	for(RenderModel* model : this->models)
		model->applyTransformations();

	this->attachObservers();
}

void Scene::makeScenePlanets()
{
	this->animated = true;
	VertexShader* vertexShaderCons = new VertexShader("Shaders/vertexConstant.vert");
	VertexShader* vertexShader = new VertexShader("Shaders/vertexlights.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhong.frag");
	FragmentShader* fragmentShaderCons = new FragmentShader("Shaders/fragmentConstant.frag");

	this->camera->setEye(glm::vec3(0.0f, 20.0f, 0.0f));
	Material* m = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(1.0f,1.0f,0.0f,1.0f));
	Material* m2 = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.09f, 0.73f, 0.09f, 1.0f));
	Material* m3 = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	Material* m4 = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.83f, 0.29f, 0.15f, 1.0f));
	Material* m5 = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.89f, 0.67f, 0.58f, 1.0f));

	this->lights.push_back(new DirectionLight(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f)));
	this->shaders.push_back(new Shader(this->camera, vertexShaderCons, fragmentShaderCons));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));
	this->shaders.push_back(new Shader(this->camera, vertexShader, fragmentShader));

	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[0],m), this->shaders[0]);
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[1],m2), this->shaders[1]);
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[2], m3), this->shaders[2]);
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[3], m4), this->shaders[3]);
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaders[4], m5), this->shaders[4]);

	this->attachObservers();
}

void Scene::addModel(RenderModel* model, Shader* shader)
{
	this->models.push_back(model);
	this->camera->addObserver(shader);
}

void Scene::render()
{
	for (auto model : this->models)
		model->render();
}

void Scene::animate()
{	
	delta += 0.01f;
	//animation of scene planets
	TransformationComposite*c_sun = new TransformationComposite();

	TransformationComposite* t_sun = new TransformationComposite();
	t_sun->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	c_sun->addTransformation(t_sun);
	c_sun->addTransformation(new Scale(glm::vec3(2.0f)));
	this->models[0]->addTransformation(c_sun);

	TransformationComposite* t_earth = new TransformationComposite();
	t_earth->addTransformation(t_sun);
	t_earth->addTransformation(new Rotation(-delta, glm::vec3(0.0f, 1.0f, 0.0f)));
	t_earth->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 20.0f)));
	this->models[1]->addTransformation(t_earth);

	TransformationComposite* t_moon = new TransformationComposite();
	t_moon->addTransformation(t_earth);
	t_moon->addTransformation(new Rotation(delta*2, glm::vec3(0.0f, 1.0f, 0.0f)));
	t_moon->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 2.0f)));
	t_moon->addTransformation(new Scale(glm::vec3(0.5f)));
	this->models[2]->addTransformation(t_moon);

	TransformationComposite* t_merkur = new TransformationComposite();
	t_merkur->addTransformation(t_sun);
	t_merkur->addTransformation(new Rotation(delta*2, glm::vec3(0.0f, 1.0f, 0.0f)));
	t_merkur->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 5.0f)));
	t_merkur->addTransformation(new Scale(glm::vec3(0.5f)));
	this->models[3]->addTransformation(t_merkur);

	TransformationComposite* t_venus = new TransformationComposite();
	t_venus->addTransformation(t_sun);
	t_venus->addTransformation(new Rotation(delta*1.5, glm::vec3(0.0f, 1.0f, 0.0f)));
	t_venus->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 10.0f)));
	t_venus->addTransformation(new Scale(glm::vec3(0.8f)));	
	this->models[4]->addTransformation(t_venus);

	this->models[0]->applyTransformations();
	this->models[1]->applyTransformations();
	this->models[2]->applyTransformations();
	this->models[3]->applyTransformations();
	this->models[4]->applyTransformations();

	this->models[0]->removeTransformation(t_sun);
	this->models[1]->removeTransformation(t_earth);
	this->models[2]->removeTransformation(t_moon);
	this->models[3]->removeTransformation(t_merkur);
	this->models[4]->removeTransformation(t_venus);
	this->models[0]->removeTransformation(c_sun);

}

bool Scene::isAnimated()
{
	return this->animated;
}
