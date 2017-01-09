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
	static unsigned char* readImage2ByteArray(const GLchar* filename, int& width, int& height, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	Image(Renderer* renderer, const GLchar* imageFile, Boundaries* boundaries, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	void render() const;
	~Image();
};
