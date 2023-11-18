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
	VertexShader* vertexShader = new VertexShader("Shaders/vertexlights.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhong.frag");	
	//Lights
	this->lights.push_back(new SpotLight(this->camera->getEye(), glm::vec3(1.0f), this->camera->getTarget(), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.01f, 0.0032f));
	//Camera
	this->camera->setEye(glm::vec3(0.0f, 1.0f, -1.0f));
	//Models
	Model* model_tree = new Model(tree, sizeof(tree) / sizeof(float), false, true);
	Model* model_bushes = new Model(bushes, sizeof(bushes) / sizeof(float), false, true);
	Model* floor = FileLoader::loadModel("Models/plane.obj");
	Model* cat = FileLoader::loadModel("Models/cat.obj");
	Model* rat = FileLoader::loadModel("Models/rat.obj");
	Model* duck = FileLoader::loadModel("Models/Duck.obj");
	Model* house = FileLoader::loadModel("Models/model.obj");
	//Textures
	Texture* tFloor = new Texture("Textures/grass.png", 2);
	Texture* tCat = new Texture("Textures/Cat_diffuse.jpg", 3);
	Texture* tRat = new Texture("Textures/street_rat.jpg", 4);
	Texture* tDuck = new Texture("Textures/Duck.jpg", 5);
	Texture* tHouse = new Texture("Textures/barak.png", 6);
	//Materials
	Material* mTreeBush = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.09f, 0.77f, 0.09f, 1.0f));
	Material* mFloor = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), tFloor);
	Material* mCat = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tCat);
	Material* mRat = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tRat);
	Material* mDuck = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tDuck);
	Material* mHouse = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), tHouse);
	//ShaderPrograms
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	///
	this->addModel(new RenderModel(floor, this->shaderPrograms[0], mFloor));
	this->models[0]->addTransformation(new Scale(glm::vec3(100.0f)));
	this->models[0]->applyTransformations();
	///
	this->addModel(new RenderModel(cat, this->shaderPrograms[1], mCat));
	this->models[1]->addTransformation(new Translation(glm::vec3(-2.0f, 0.0f, 1.0f)));
	this->models[1]->addTransformation(new Rotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->models[1]->addTransformation(new Scale(glm::vec3(0.03f)));
	this->models[1]->applyTransformations();

	this->addModel(new RenderModel(rat, this->shaderPrograms[2], mRat));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, 1.0f)));
	this->models[2]->addTransformation(new Rotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

	this->models[2]->applyTransformations();

	this->addModel(new RenderModel(duck, this->shaderPrograms[3], mDuck));
	this->models[3]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, -1.0f)));
	this->models[3]->addTransformation(new Rotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->models[3]->addTransformation(new Scale(glm::vec3(0.02f)));
	this->models[3]->applyTransformations();

	this->addModel(new RenderModel(house, this->shaderPrograms[4], mHouse));
	this->models[4]->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 40.0f)));
	this->models[4]->applyTransformations();

	//treees
	for (size_t i = 5; i < 255; i++)
	{
		this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
		this->addModel(new RenderModel(model_tree, this->shaderPrograms[i], mTreeBush));
		this->models[i]->addTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->models[i]->addTransformation(new Scale(glm::vec3(rand() % 10 / 10.0f + 0.5f)));
		float x = float(rand() % 30);
		float z = float(rand() % 30);
		this->models[i]->addTransformation(new Translation(glm::vec3(x, 0.0f, z)));
		this->models[i]->applyTransformations();
	}

	this->attachObservers();
}

void Scene::makeSceneTrees()
{
	this->animated = false;
	srand(time(NULL));
	VertexShader* vertexShader = new VertexShader("Shaders/vertexlights.vert");
	FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhong.frag");
	VertexShader* vertexShaderTexture = new VertexShader("Shaders/vertexLightsTexture.vert");
	FragmentShader* fragmentShaderTexture = new FragmentShader("Shaders/fragmentPhongTexture.frag");

	this->lights.push_back(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	//this->lights.push_back(new DirectionLight(glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0f)));
	this->lights.push_back(new SpotLight(this->camera->getEye(), glm::vec3(1.0f), this->camera->getTarget(), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	this->camera->setEye(glm::vec3(0.0f, 0.0f, -1.0f));
	Model* model_tree = new Model(tree, sizeof(tree) / sizeof(float),false,true);
	Model* model_bushes = new Model(bushes, sizeof(bushes) / sizeof(float),false,true);
	Material* m = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.09f, 0.77f, 0.09f, 1.0f));
	Texture* t = new Texture("Textures/grass.png", 2);
	Material* m_plain = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),t);
	for (size_t i = 0; i < 175; i++)
	{
		this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
		this->addModel(new RenderModel(model_tree, this->shaderPrograms[i],m));
		this->models[i]->addTransformation(new Rotation(rand() % 360,glm::vec3(0.0f, 1.0f, 0.0f)));
		this->models[i]->addTransformation(new Scale(glm::vec3(rand() % 10 / 10.0f + 0.5f)));
		float x = float(rand() % 50);
		float z = float(rand() % 50) ;
		this->models[i]->addTransformation(new Translation(glm::vec3(x, 0.0f, z)));
		this->models[i]->applyTransformations();
	}
	for (size_t i = 175; i < 195; i++)
	{
		this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
		this->addModel(new RenderModel(model_bushes, this->shaderPrograms[i],m));
		this->models[i]->addTransformation(new Rotation(rand() % 360, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->models[i]->addTransformation(new Scale(glm::vec3(rand() % 10 / 10.0f + 1.5f)));
		float x = float(rand() % 50);
		float z = float(rand() % 50);
		this->models[i]->addTransformation(new Translation(glm::vec3(x, 0.0f, z)));
		this->models[i]->applyTransformations();
	}
	Material* m_ball = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Material* m_suzi = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f));
	Material* m_plainTextureWood = new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f), 32.0f, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f),new Texture("Textures/test.png",3));

	
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->addModel(new RenderModel(plain, sizeof(plain) / sizeof(float), this->shaderPrograms[195],m_plain,true,true));
	this->models[195]->addTransformation(new Scale(glm::vec3(100.0f)));
	this->models[195]->applyTransformations();
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));	
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[196],m_ball, false, true));
	this->models[196]->addTransformation(new Scale(glm::vec3(0.5f)));
	this->models[196]->addTransformation(new Translation(glm::vec3(0.0f, 5.0f, 10.0f)));
	this->models[196]->applyTransformations();
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->addModel(new RenderModel(gift, sizeof(gift) / sizeof(float), this->shaderPrograms[197], m_ball, false, true));
	this->models[197]->addTransformation(new Scale(glm::vec3(2.5f)));
	this->models[197]->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 8.0f)));
	this->models[197]->applyTransformations();
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->addModel(new RenderModel(suziSmooth, sizeof(suziSmooth) / sizeof(float), this->shaderPrograms[198], m_suzi, false, true));
	this->models[198]->addTransformation(new Scale(glm::vec3(1.5f)));
	this->models[198]->addTransformation(new Translation(glm::vec3(0.0f, 2.5f, 0.0f)));
	this->models[198]->applyTransformations();
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderTexture, fragmentShaderTexture));
	this->addModel(new RenderModel(plain, sizeof(plain) / sizeof(float), this->shaderPrograms[199], m_plainTextureWood,true,true));
	this->models[199]->addTransformation(new Translation(glm::vec3(0.0f, 0.01f, 0.0f)));	
	this->models[199]->addTransformation(new Scale(glm::vec3(14.0f)));
	this->models[199]->applyTransformations();

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
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[0],m2, false, true));
	this->models[0]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[0]->addTransformation(new Translation(glm::vec3(-2.0f, 0.0f, 0.0f)));
	this->models[0]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[1],m, false, true));
	this->models[1]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[1]->addTransformation(new Translation(glm::vec3(0.0f, 2.0f, 0.0f)));
	this->models[1]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[2],m, false, true));
	this->models[2]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[2]->addTransformation(new Translation(glm::vec3(2.0f, 0.0f, 0.0f)));
	this->models[2]->applyTransformations();
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[3],m, false, true));
	this->models[3]->addTransformation(new Scale(glm::vec3(0.7f)));
	this->models[3]->addTransformation(new Translation(glm::vec3(0.0f, -2.0f, 0.0f)));
	this->models[3]->applyTransformations();
	this->attachObservers();
}


void Scene::makeSceneTest()
{
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
	//Scene objects with different shaderPrograms, constant, lambert and phong 
	this->lights.push_back(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	Material* m = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.f), glm::vec3(1.f), 32.0f, glm::vec4(0.09f, 0.73f, 0.09f, 1.0f));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderCons, fragmentShaderCons));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShaderLambert));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShaderBlinn));

	this->addModel(new RenderModel(tree, sizeof(tree) / sizeof(float), this->shaderPrograms[0],m,false,true));
	this->addModel(new RenderModel(suziFlat, sizeof(suziFlat) / sizeof(float), this->shaderPrograms[1],m, false, true));
	this->addModel(new RenderModel(suziSmooth, sizeof(suziSmooth) / sizeof(float), this->shaderPrograms[2],m, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[3],m, false, true));

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
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShaderCons, fragmentShaderCons));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));
	this->shaderPrograms.push_back(new ShaderProgram(this->camera, vertexShader, fragmentShader));

	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[0],m,false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[1],m2, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[2], m3, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[3], m4, false, true));
	this->addModel(new RenderModel(sphere, sizeof(sphere) / sizeof(float), this->shaderPrograms[4], m5, false, true));

	this->attachObservers();
}

void Scene::addModel(RenderModel* model)
{
	this->models.push_back(model);
	this->camera->addObserver(model->getShaderProgram());
}

void Scene::render()
{
	for (auto model : this->models)
		model->render();
}

void Scene::renderSkybox()
{
	if(this->skybox != nullptr)
		this->skybox->render();
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
