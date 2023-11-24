#include "../Headers/Callback.h"
#include "../Headers/Camera.h"

bool Callback::isMouseButtonPressed = false;
bool Callback::removeOrAdd = false;

void Callback::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Callback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (app)
	{
		Camera* c = app->getScene()->getCamera();
		if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			a += c->getTarget() * c->getSpeed();
			c->setEye(a);
			app->getScene()->notifyLights();
		}
		if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			a -= c->getTarget() * c->getSpeed();
			c->setEye(a);
			app->getScene()->notifyLights();
		}
		if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			glm::vec3 b = glm::cross(c->getTarget(), c->getUp());
			a -= b * c->getSpeed();
			c->setEye(a);
			app->getScene()->notifyLights();
		}
		if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == 2))
		{
			glm::vec3 a = c->getEye();
			glm::vec3 b = glm::cross(c->getTarget(), c->getUp());
			a += b * c->getSpeed();
			c->setEye(a);
			app->getScene()->notifyLights();
		}
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			app->getScene()->getCamera()->setWindowSize(app->width, app->height);
			app->setScene(0);
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			app->getScene()->getCamera()->setWindowSize(app->width, app->height);
			app->setScene(1);
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		{
			app->getScene()->getCamera()->setWindowSize(app->width, app->height);
			app->setScene(2);
		}
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			removeOrAdd = !removeOrAdd;
		}
	}
	
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Callback::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Callback::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Callback::window_size_callback(GLFWwindow* window, int width, int height)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	printf("resize %d, %d \n", width, height);
	app->width = width;
	app->height = height;
	app->getScene()->getCamera()->setWindowSize(width, height);
	glViewport(0, 0, width, height);
}

void Callback::cursor_callback(GLFWwindow* window, double x, double y)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app && isMouseButtonPressed)
	{
		Camera* c = app->getScene()->getCamera();
		float xoffset = x - app->lastX;
		float yoffset = app->lastY - y;
		app->lastX = x;
		app->lastY = y;
		xoffset *= c->getSensitivity();
		yoffset *= c->getSensitivity();
		c->yaw += xoffset;
		c->pitch += yoffset;
		if (c->pitch > 89.0f)
			c->pitch = 89.0f;
		if (c->pitch < -89.0f)
			c->pitch = -89.0f;
		glm::vec3 front(
			cos(glm::radians(c->yaw)) * cos(glm::radians(c->pitch)),
			sin(glm::radians(c->pitch)),
			sin(glm::radians(c->yaw)) * cos(glm::radians(c->pitch)));
		c->setTarget(glm::normalize(front));
		
		//app->getScene()->notifyLights(); //why this lags the scene trees?
	}
	//printf("cursor_callback [%f,%f]\n",x,y);
}

void Callback::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) {
		//printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		isMouseButtonPressed = !isMouseButtonPressed;
		if (isMouseButtonPressed) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock and hide the cursor
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			// Center the cursor
			glfwSetCursorPos(window, width / 2, height / 2);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Release the cursor
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		GLbyte color[4];
		GLfloat depth;
		GLuint index;
		if (!isMouseButtonPressed)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			GLint x = (GLint)xpos;
			GLint y = (GLint)ypos;
			int newy = app->getScene()->getCamera()->getResolutionHeight() - y;
			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
			printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
			app->getScene()->getCamera()->getPosGlobal(glm::vec3(x, newy, depth));
		}
		else
		{
			int xpos, ypos;
			glfwGetWindowSize(window, &xpos, &ypos);
			GLint x = GLint(xpos/2);
			GLint y = GLint(ypos/2);
			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
			printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
			glm::vec3 pos = app->getScene()->getCamera()->getPosGlobal(glm::vec3(x, y, depth));
			if(removeOrAdd)
				app->getScene()->removeModel(index);
			else
			{
				VertexShader* vertexShader = new VertexShader("Shaders/vertexLightsTexture.vert");
				FragmentShader* fragmentShader = new FragmentShader("Shaders/fragmentPhongTexture.frag");
				ShaderProgram* shaderProgram = new ShaderProgram(app->getScene()->getCamera(),vertexShader, fragmentShader);
				app->getScene()->addModel(new RenderModel(app->getScene()->getPreloadModel(0), shaderProgram, new Material(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), glm::vec3(1.f), 32.0f, glm::vec4(0.0f, 0.5f, 1.f, 1.0f), new Texture("Textures/tree.png", 7)),true),pos);
			}
		}
	}
}
