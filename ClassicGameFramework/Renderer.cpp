#include "Renderer.h"
#include "Display.h"
#include "Drawable.h"
#include "Image.h"
#include "Config.h"

//#include <glfw3.h>

void Renderer::init() const
{
	//std::cout << "Starting GLFW context, OpenGL " << GL_VERSION_MAJOR << "." << GL_VERSION_MINOR << std::endl;
	// Initializing GLFW (OpenGL interfaces)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, RESIZABLE_WINDOW);

	// Build and compile our shader program
	//Renderer::shader = new Shader("textureShader.vert", "textureShader.frag");

	
	//Image image1 = Image(this, "textur.bmp", 200, 200, 70, 70);
}

int Renderer::initGLEW()
{
	glewExperimental = GL_TRUE;
	int ret = glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lade alle Texturen
	//loadTextures();

	return ret;
}

GLFWwindow* Renderer::createWindow(int width ,int height, const char* title)
{
	

	auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
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

GLfloat* Renderer::translateToWorldCoordinates(GLint xPos, GLint yPos) const
{
	auto halfWidth = WINDOW_WIDTH / 2.0f;
	auto halfHeight = WINDOW_HEIGHT / 2.0f;

	return new GLfloat[2]{
		(xPos - halfWidth) / halfWidth,
		(yPos - halfHeight) / halfHeight
	};
}

Renderer::Renderer(int width, int height, const char* title) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height)
{
	
	// Initializing
	this->init();

	// Creating a window
	window = this->createWindow(width, height, title);

	// Initializing GLEW (OpenGL implementations)
	this->initGLEW();

	// Creating viewport
	glViewport(0, 0, width, height);

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


void fillEntireScreenWithColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	// Clear the color buffer
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(Display* display)
{
	std::vector<long> deadpool;
	for(auto x : imageRenderers)
	{
		if (x.second->getLastUse() + 15000 < Config::currentTimeMillis())
		{
			deadpool.push_back(x.first);
		}
	}
	for(auto x : deadpool)
	{
		imageRenderers.erase(x);
	}


	// Clear screen
	fillEntireScreenWithColor(0.0f, 0.0f, 0.0f, 1.0f);

	auto drawables = display->getDrawables();
	
	for(size_t i = 0; i < drawables->size(); i++)
	{
		auto image = drawables->at(i)->getImage();

		if(imageRenderers.find(image->getId()) == imageRenderers.end())
		{
			imageRenderers.insert(std::make_pair(image->getId(), new ImageRenderer(this, drawables->at(i))));
		}

		imageRenderers.at(image->getId())->render();
	}

	// Swap the buffers
	glfwSwapBuffers(window);
}