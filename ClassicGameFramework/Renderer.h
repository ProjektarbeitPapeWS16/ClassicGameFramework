#pragma once
// GLEW
#define GLEW_STATIC
#include <glew.h>
// GLFW
#include <glfw3.h>
#include <map>
#include "ImageRenderer.h"
class Text;
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
	void init() const;

	/// <summary>
	/// Initializes GLEW
	/// </summary>
	/// <returns></returns>
	static int initGLEW();

	/// <summary>
	/// Creates a GLFW window
	/// </summary>
	/// <param name="width">the window width</param>
	/// <param name="height">the window height</param>
	/// <param name="title">the window title</param>
	/// <returns></returns>
	static GLFWwindow* createWindow(int width, int height, const char* title);

	/// <summary>
	/// Clears all resources allocated by GLFW and GLEW
	/// </summary>
	static void terminate();

	/// <summary>
	/// Prints a given log message on the console
	/// </summary>
	/// <param name="message">the message</param>
	static void log(const char* message);

	std::map<unsigned long, ImageRenderer*> imageRenderers;
	const GLuint WINDOW_WIDTH;
	const GLuint WINDOW_HEIGHT;

	//std::map<Image>

public:
	// OpenGL Version
	const GLuint GL_VERSION_MAJOR = 3;
	const GLuint GL_VERSION_MINOR = 3;

	// Window options
	const GLboolean RESIZABLE_WINDOW = GL_FALSE;
	
	// Rendering options
	const GLboolean VSYNC = GL_TRUE;
	const GLboolean JUST_WIREFRAMES = GL_FALSE;

	GLFWwindow* window;

	Renderer(int width, int height, const char* title);

	~Renderer();

	void render(Display* display);
	void clearBuffer();
	/// <summary>
	/// Returns OpenGL-Coordinates for given pixel coordinates
	/// </summary>
	/// <param name="xPos"></param>
	/// <param name="yPos"></param>
	/// <returns></returns>
	GLfloat* translateToWorldCoordinates(GLint xPos, GLint yPos) const;
};
