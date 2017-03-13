#pragma once
#include <string>
#include <map>

class Entity;
struct Boundaries;

class Image
{
	static std::map<std::string, unsigned char*> path_images;
	static std::map<std::string, long> path_refcount;
	static std::map<std::string, std::pair<int, int>> path_width_height;
	int imageWidth, imageHeight;
	const char* imageFile;

	unsigned char* imageBytes;
	unsigned short transR, transG, transB;
	unsigned char* readImage2ByteArray();
public:

	//double getScale() const;
	Image(const char* imageFile, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);

	/**
	 * For Compatibility only.
	 * @deprecated Use Image(imageFile, transR, transG, transB) instead. Entity is not necessary.
	 */
	Image(const char* imageFile, Entity* entity, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	Image(unsigned char* imageBytes, int width, int height, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256);
	~Image();

	const char* getImageFile() const;
	bool isLoaded() const;
	void loadImageBytes();
	int getWidth() const;
	int getHeight() const;
	unsigned char* getImageBytes();
};
