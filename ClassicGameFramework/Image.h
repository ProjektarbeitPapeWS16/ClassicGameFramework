#pragma once
#include "ImageRenderer.h"
//#include "Drawable.h"
class Drawable;
//class Entity;
struct Boundaries;

class Image
{
	static unsigned long image_count;
	unsigned long id;

	int imageWidth, imageHeight;
	const char* imageFile;

	Drawable* entity;
	unsigned char* imageBytes;
	unsigned short transR, transG, transB;
public:

	//double getScale() const;
	Image(const char* imageFile, Drawable* entity, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	Image(unsigned char* imageBytes, int width, int height, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	~Image();

	const char* getImageFile() const;
	Drawable* getEntity() const;
	int getWidth() const;
	int getHeight() const;
	unsigned char* getImageBytes();
	unsigned long getId() const;
	int getTransR() const;
	int getTransG() const;
	int getTransB() const;
};
