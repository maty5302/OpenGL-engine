#include "../Headers/Callback.h"
#include "../Headers/Camera.h"

bool Callback::isMouseButtonPressed = false;

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
			app->setScene(0);
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			app->setScene(1);
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		{
			app->setScene(2);
		}
		if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		{
			//app->setScene(3);
		}
		if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		{
			app->setScene(4);
		}
	}
	
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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
		glm::vec3 front;
		front.x = cos(glm::radians(c->yaw)) * cos(glm::radians(c->pitch));
		front.y = sin(glm::radians(c->pitch));
		front.z = sin(glm::radians(c->yaw)) * cos(glm::radians(c->pitch));
		c->setTarget(glm::normalize(front));
		app->getScene()->notifyLights();
	}
	printf("cursor_callback [%f,%f]\n",x,y);
}

void Callback::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) {
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		isMouseButtonPressed = !isMouseButtonPressed;
		if (isMouseButtonPressed) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock and hide the cursor
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Release the cursor
		}
	}
}
