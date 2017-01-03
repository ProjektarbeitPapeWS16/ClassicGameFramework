#include "Renderer.h"
//#include <iostream>
#include "glfw3.h"

void Renderer::init()
{
	//std::cout << "Starting GLFW context, OpenGL " << GL_VERSION_MAJOR << "." << GL_VERSION_MINOR << std::endl;
	// Initializing GLFW (OpenGL interfaces)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, RESIZABLE_WINDOW);
}

int Renderer::initGLEW()
{
	glewExperimental = GL_TRUE;
	return glewInit();
}

GLFWwindow* Renderer::createWindow()
{
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	if (window != nullptr)
	{
		glfwMakeContextCurrent(window);
	}
	return window;
}

void Renderer::terminate()
{
	glfwTerminate();
}

void Renderer::log(const char* message)
{
	//std::cout << std::endl << message << std::endl;
}

GLfloat* Renderer::translateToWorldCoordinates(GLuint xPos, GLuint yPos)
{
	GLfloat halfWidth = WINDOW_WIDTH / 2.0f;
	GLfloat halfHeight = WINDOW_HEIGHT / 2.0f;

	return new GLfloat[2]{
		(xPos - halfWidth) / halfWidth,
		(yPos - halfHeight) / halfHeight
	};
}

Renderer::Renderer()
{
	// Initializing
	this->init();

	// Creating a window
	window = this->createWindow();

	// Initializing GLEW (OpenGL implementations)
	this->initGLEW();

	// Creating viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Turn on Vsync
	if (VSYNC == GL_TRUE)
	{
		glfwSwapInterval(1);
	}
}

Renderer::~Renderer()
{
	terminate();
}

void Renderer::render(Display& display)
{
	// Clear the color buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: render stuff with display here


	// Swap the buffers
	glfwSwapBuffers(window);
}
