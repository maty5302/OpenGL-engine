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
#include "../Models/skycube.h"
#include "../Models/building.h"
#include "../Headers/Texture.h"

void Scene::attachObservers()
{
	for (auto light : this->lights)
		for (auto observer : this->shaderPrograms)
			light->addObserver(observer);
	this->camera->notify();
	this->notifyLights();
}

Scene::Scene()
{
	this->camera = new Camera();
	this->lights = std::vector<Light*>();
	this->models = std::vector<RenderModel*>();
	this->shaderPrograms = std::vector<ShaderProgram*>();
	this->skybox = nullptr;
}

Scene::Scene(Model* skybox, Texture* texture)
{
	this->camera = new Camera();
	this->lights = std::vector<Light*>();
	this->models = std::vector<RenderModel*>();
	this->shaderPrograms = std::vector<ShaderProgram*>();
	this->skybox = new RenderModel(skybox, new ShaderProgram(this->camera,
		new VertexShader("Shaders/vertexCube.vert"),
		new FragmentShader("Shaders/fragmentCube.frag")), 
		new Material(texture));
	this->camera->addObserver(this->skybox->getShaderProgram());
}

Scene::~Scene()
{
	delete this->camera;
	delete this->skybox;

	for (auto model : this->models)
		delete model;
	for(auto light : this->lights)
		delete light;
	for(auto shader : this->shaderPrograms)
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

void Scene::makeScene()
{
	//Shaders
	VertexShader* vertexShaderTexture = new VertexShader("Shaders/vertexLightsTexture.vert");
	FragmentShader* fragmentShaderTexture = new FragmentShader("Shaders/fragmentPhongTexture.frag");
	//Lights
	this->lights.push_back(new SpotLight(this->camera->getEye(), glm::vec3(1.0f), this->camera->getTarget(), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.01f, 0.0032f));
	//Camera
	this->camera->setEye(glm::vec3(0.0f, 1.0f, -1.0f));
	//Models
	Model* floor = FileLoader::loadModel("Models/plane.obj");
	Model* cat = FileLoader::loadModel("Models/cat.obj");
	Model* rat = FileLoader::loadModel("Models/rat.obj");
	Model* duck = FileLoader::loadModel("Models/Duck.obj");
	Model* house = FileLoader::loadModel("Models/model.obj");
	Model* model_tree = FileLoader::loadModel("Models/tree.obj");
	//Textures
	Texture* tFloor = new Texture("Textures/grass.png", 2);
	Texture* tCat = new Texture("Textures/Cat_diffuse.jpg", 3);
	Texture* tRat = new Texture("Textures/street_rat.jpg", 4);
	Texture* tDuck = new Texture("Textures/Duck.jpg", 5);
	Texture* tHouse = new Texture("Textures/barak.png", 6);
	Texture* tTree = new Texture("Textures/tree.png", 7);
	//Materials
	Material* mFloor = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), tFloor);
	Material* mCat = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tCat);
	Material* mRat = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tRat);
	Material* mDuck = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tDuck);
	Material* mHouse = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tHouse);
	Material* mTree = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.f, 1.0f), tTree);
	//Models
	this->addModel(new RenderModel(floor, new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture), mFloor));
	this->models[0]->addTransformation(new Scale(glm::vec3(100.0f)));
	this->models[0]->applyTransformations();
	///
	this->addModel(new RenderModel(cat, new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture), mCat));
	this->models[1]->addTransformation(new Translation(glm::vec3(-2.0f, 0.0f, 1.0f)));
	this->models[1]->addTransformation(new Rotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->models[1]->addTransformation(new Scale(glm::vec3(0.03f)));
	this->models[1]->applyTransformations();

	this->addModel(new RenderModel(rat, new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture), mRat));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, 1.0f)));
	this->models[2]->addTransformation(new Rotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

	this->models[2]->applyTransformations();

	this->addModel(new RenderModel(duck, new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture), mDuck));
	this->models[3]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, -1.0f)));
	this->models[3]->addTransformation(new Rotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->models[3]->addTransformation(new Scale(glm::vec3(0.02f)));
	this->models[3]->applyTransformations();

	this->addModel(new RenderModel(house, new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture), mHouse));
	this->models[4]->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 40.0f)));
	this->models[4]->applyTransformations();

	//treees
	for (size_t i = 5; i < 200; i++)
	{
		this->addModel(new RenderModel(model_tree, new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture), mTree));
		this->models[i]->addTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->models[i]->addTransformation(new Scale(glm::vec3(rand() % 5 / 15.0f)));
		float x = float(rand() % 30);
		float z = float(rand() % 30);
		this->models[i]->addTransformation(new Translation(glm::vec3(x, 0.0f, z)));
		this->models[i]->applyTransformations();
	}

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

	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader),m2, false, true));
	this->models[0]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(-2.0f, 0.0f, 0.0f)));
	this->models[0]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader),m, false, true));
	this->models[1]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	this->models[1]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader),m, false, true));
	this->models[2]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, 0.0f)));
	this->models[2]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader),m, false, true));
	this->models[3]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	this->models[3]->applyTransformations();
	this->attachObservers();
}


void Scene::makeSceneTest()
{
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

	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShaderCons, fragmentShaderCons),m,false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader),m2, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader), m3, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader), m4, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), new ShaderProgram(this->camera, vertexShader, fragmentShader), m5, false, true));

	this->attachObservers();
}

void Scene::addModel(RenderModel* model)
{
	this->models.push_back(model);
	this->camera->addObserver(model->getShaderProgram());
	this->shaderPrograms.push_back(model->getShaderProgram());
}

void Scene::removeModel(int id)
{
	for (int i = 0; i < this->models.size(); i++)
	if (this->models[i]->getID() == id)
	{
		this->camera->removeObserver(this->models[i]->getShaderProgram());
		this->models.erase(this->models.begin() + i);
		this->shaderPrograms.erase(this->shaderPrograms.begin() + i);
		for(auto light : lights)
			light->removeObserver(this->models[i]->getShaderProgram());
		break;
	}
}

void Scene::render()
{
	for (auto model : this->models){
		glStencilFunc(GL_ALWAYS, model->getID(), 0xFF);
		model->render();
	}
		
}

void Scene::renderSkybox()
{
	if (this->skybox != nullptr) {
		glStencilFunc(GL_ALWAYS, this->skybox->getID(), 0xFF);
		this->skybox->render();
	}
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
	t_venus->addTransformation(new Rotation(delta*1.5f, glm::vec3(0.0f, 1.0f, 0.0f)));
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
