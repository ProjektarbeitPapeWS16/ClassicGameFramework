#pragma once

#include <glew.h>
#include "Shader.h"

class Entity;
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

	Entity* entity;
	static unsigned char* readImage2ByteArray(const GLchar* filename, int& width, int& height, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
public:
	
	Image(Renderer* renderer, const GLchar* imageFile, Entity* entity, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	void render() const;
	~Image();
};
