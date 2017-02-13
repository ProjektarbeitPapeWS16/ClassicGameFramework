#pragma once

#include <glew.h>
#include "Shader.h"

class Entity;
struct Boundaries;

// Puprose:	Provides framework for displaying a given Entity in the window, including animation.
class Image
{
	GLuint VBO, VAO, EBO;
	GLuint texture;
	Shader* textureShader;
	unsigned char * image;			// Stores the bitmap file information as char array
	int imageWidth, imageHeight;	// Stores width and height of bitmap to properly read information from "image"
	
	Renderer* renderer;
	const GLchar* imageFile;		// Name of the bitmap file that contains the sprites for the entity

	Entity* entity;					// Determines physical properties and behavior

	// Returns converted image information from a given bitmap file, including alpha channel through R,G,B value.
	static unsigned char* readImage2ByteArray(const GLchar* filename, int& width, int& height, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
public:
	
	Image(Renderer* renderer, const GLchar* imageFile, Entity* entity, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	void render() const;
	~Image();
};
