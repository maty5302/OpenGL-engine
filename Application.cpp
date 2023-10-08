#include "Application.h"
//#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"
#include "Models/plain.h"
#include "TransformationComposite.h"
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"



void Application::initialization()
{
	glfwSetErrorCallback(Callback::error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(640, 480, "ZPG - PRU0059", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

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
}

void Application::createShaderAndModels()
{
	this->renderModels.push_back(new RenderModel(sphere, 17280));
	this->renderModels[0]->addTransformation(new Scale(glm::vec3(0.3f)));
	this->renderModels[0]->addTransformation(new Translation(glm::vec3(-1.5f, -0.7f, 0.0f)));
	this->renderModels[0]->addTransformation(new Rotation(2.f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->renderModels[0]->applyTransformations();
	
	this->renderModels.push_back(new RenderModel(suziSmooth, 17424));
	this->renderModels[1]->addTransformation(new Scale(glm::vec3(0.4f)));
	this->renderModels[1]->addTransformation(new Translation(glm::vec3(1.0f, 1.4f, 1.0f)));
	this->renderModels[1]->addTransformation(new Rotation(2.f, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->renderModels[1]->applyTransformations();

	this->renderModels.push_back(new RenderModel(sphere, 17280));
	this->renderModels[2]->addTransformation(new Scale(glm::vec3(0.2f)));
	this->renderModels[2]->addTransformation(new Translation(glm::vec3(2.f, 2.5f, 0.0f)));
	this->renderModels[2]->applyTransformations();
}

void Application::run()
{
	glfwSetKeyCallback(window, Callback::key_callback);
	glfwSetCursorPosCallback(window, Callback::cursor_callback);
	glfwSetMouseButtonCallback(window, Callback::button_callback);
	glfwSetWindowFocusCallback(window, Callback::window_focus_callback);
	glfwSetWindowIconifyCallback(window, Callback::window_iconify_callback);
	glfwSetWindowSizeCallback(window, Callback::window_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (size_t i = 0; i < renderModels.size(); i++)
		{		
			this->renderModels[i]->addTransformation(new Rotation(0.01f, glm::vec3(0.0f, 1.0f, 0.0f)));
			this->renderModels[i]->applyTransformations();
			this->renderModels[i]->render();
		}
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
	exit(EXIT_SUCCESS);
}

