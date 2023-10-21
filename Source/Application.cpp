#include "../Headers/Application.h"
#include "../Headers/FileLoader.h"
#include "../Models/tree.hpp"

Scene* Application::getScene()
{
	return this->activeScene;
}

void Application::setScene(int sceneNumber)
{
	if(sceneNumber < 0 || sceneNumber >= this->scenes.size())
	{
		std::cout << "Scene doesn't exist" << std::endl;
		return;
	}
	this->activeScene = this->scenes[sceneNumber];
}

void Application::initialization()
{
	glfwSetErrorCallback(Callback::error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(800, 600, "ZPG - PRU0059", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); 
	glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glEnable(GL_DEPTH_TEST);

	this->scenes.push_back(new Scene());
	this->scenes[0]->makeScene();
	this->scenes.push_back(new Scene());
	this->scenes[1]->makeScene2();
	this->scenes.push_back(new Scene());
	this->scenes[2]->makeScene3();
}

void Application::run()
{
	this->activeScene = this->scenes[0];
	glfwSetKeyCallback(window, Callback::key_callback);
	glfwSetCursorPosCallback(window, Callback::cursor_callback);
	glfwSetMouseButtonCallback(window, Callback::button_callback);
	glfwSetWindowFocusCallback(window, Callback::window_focus_callback);
	glfwSetWindowIconifyCallback(window, Callback::window_iconify_callback);
	glfwSetWindowSizeCallback(window, Callback::window_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->activeScene->render();		
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}
}

Application::Application()
{
}

Application::~Application()
{
	glfwDestroyWindow(window);
	glfwTerminate();

	delete this->activeScene;
	for (auto scene : this->scenes)
		delete scene;

	exit(EXIT_SUCCESS);
}

