#pragma once

class Entity;
struct Boundaries;

class Image
{
	static unsigned long image_count;
	unsigned long id;

	int imageWidth, imageHeight;
	const char* imageFile;

	Entity* entity;
	unsigned char* imageBytes;
	unsigned short transR, transG, transB;
	unsigned char* readImage2ByteArray();
public:

	double getScale() const;
	Image(const char* imageFile, Entity* entity, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	Image(unsigned char* imageBytes, int width, int height, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	~Image();

	const char* getImageFile() const;
	Entity* getEntity() const;
	bool isLoaded() const;
	void loadImageBytes();
	int getWidth() const;
	int getHeight() const;
	unsigned char* getImageBytes() const;
	unsigned long getId() const;
};
