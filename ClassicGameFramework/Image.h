#pragma once

class Entity;
struct Boundaries;

// Puprose:	Provides framework for displaying a given Entity in the window, including animation.
class Image
{
	int imageWidth, imageHeight;
	const char* imageFile;

	Entity* entity;
	unsigned char* imageBytes;
	unsigned short transR, transG, transB;
	unsigned char* readImage2ByteArray();
public:

	Image(const char* imageFile, Entity* entity, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	~Image();

	const char* getImageFile() const;
	Entity* getEntity() const;
	bool isLoaded() const;
	void loadImageBytes();
	int getWidth() const;
	int getHeight() const;
	unsigned char* getImageBytes() const;
};
