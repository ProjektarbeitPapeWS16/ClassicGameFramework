#include "Renderer.h"
#include "Display.h"
#include "Drawable.h"
#include "Shader.h"
//#include <glfw3.h>

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


GLuint Renderer::LoadTexture(const char * filename)
{

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;
	fopen_s(&file, filename, "rb"); // assumes correct file type (bitmap?)

	if (file == NULL) return 0;
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}


void Renderer::loadTextures()
{
	// Build and compile our shader program
	Shader ourShader("textureShader.vert", "textureShader.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO


						  // Load and create a texture 
	GLuint texture1 = LoadTexture("textur.bmp");
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
}





void fillEntireScreenWithColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	// Clear the color buffer
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(Drawable* drawable)
{
	// TODO
	
}

void Renderer::render(Display* display)
{
	// Clear
	fillEntireScreenWithColor(0.0f, 0.0f, 0.0f, 1.0f);

	loadTextures();

	/*std::vector<Drawable*>* drawables = display->getDrawables();
	for(int i = 0; i < drawables->size(); i++)
	{
		render(drawables->at(i));
	}*/

	// Swap the buffers
	glfwSwapBuffers(window);
}
