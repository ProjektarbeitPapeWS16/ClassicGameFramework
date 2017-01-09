#pragma once

#include <glew.h>
#include "Shader.h"

struct Boundaries;

class Image
{
	GLuint VBO, VAO, EBO;
	GLuint texture;
	Shader* textureShader;
	unsigned char * image;
	int imageWidth, imageHeight;
	
	Renderer* renderer;
	const GLchar* imageFile;

	Boundaries* boundaries;
public:
	Image(Renderer* renderer, const GLchar* imageFile, Boundaries* boundaries);
	void render();
	~Image();
};
