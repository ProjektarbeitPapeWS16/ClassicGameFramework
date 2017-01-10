#pragma once
// GLEW
#define GLEW_STATIC
#include <glew.h>
// GLFW
#include <glfw3.h>
class Drawable;
#include <vector>
class Display;
class Image;


class Renderer
{
	// TODO add parameters to constructor

	/// <summary>
	/// Initializes GLFW
	/// </summary>
	void init();

	/// <summary>
	/// Initializes GLEW
	/// </summary>
	/// <returns></returns>
	int initGLEW();

	/// <summary>
	/// Creates a GLFW window
	/// </summary>
	/// <param name="width">the window width</param>
	/// <param name="height">the window height</param>
	/// <param name="title">the window title</param>
	/// <returns></returns>
	GLFWwindow* createWindow(int width, int height, const char* title);

	/// <summary>
	/// Clears all resources allocated by GLFW and GLEW
	/// </summary>
	void terminate();

	/// <summary>
	/// Prints a given log message on the console
	/// </summary>
	/// <param name="message">the message</param>
	void log(const char* message);

	std::vector<Image*> imageBuffer;
	
public:
	// OpenGL Version
	const GLuint GL_VERSION_MAJOR = 3;
	const GLuint GL_VERSION_MINOR = 3;

	// Window options
	const GLboolean RESIZABLE_WINDOW = GL_FALSE;
	const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600; // Window dimensions
	//const GLchar* WINDOW_TITLE = "Rechteck-Beispiel";

	// Rendering options
	const GLboolean VSYNC = GL_TRUE;
	const GLboolean JUST_WIREFRAMES = GL_FALSE;

	GLFWwindow* window;

	Renderer(int width, int height, const char* title);

	~Renderer();

	void render(Drawable* drawable);
	void render(Display* display);

	/// <summary>
	/// Returns OpenGL-Coordinates for given pixel coordinates
	/// </summary>
	/// <param name="xPos"></param>
	/// <param name="yPos"></param>
	/// <returns></returns>
	GLfloat* translateToWorldCoordinates(GLint xPos, GLint yPos);
};
