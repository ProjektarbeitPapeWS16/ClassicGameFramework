#include "Image.h"
#include "Entity.h"
#include <cstdio>
#include "EngineModel.h"

unsigned long Image::image_count = 0L;

const char* Image::getImageFile() const
{
	return imageFile;
}


Image::Image(const char* imageFile, Drawable* entity,
             unsigned short transR, unsigned short transG, unsigned short transB) : id(image_count++), imageWidth(0), imageHeight(0), imageFile(imageFile), entity(entity), imageBytes(nullptr),
                                                                                    transR(transR), transG(transG), transB(transB)
{
}

Image::Image(unsigned char* imageBytes, int width, int height, unsigned short transR, unsigned short transG, unsigned short transB) : id(image_count++), imageWidth(width), imageHeight(height), imageFile(nullptr), entity(nullptr), imageBytes(imageBytes),
                                                                                                                                      transR(transR), transG(transG), transB(transB)
{
}


Image::~Image()
{
	if (imageBytes != nullptr)
	{
		delete imageBytes;
	}
}

Drawable* Image::getEntity() const
{
	return entity;
}

int Image::getWidth() const
{
	return imageWidth;
}

int Image::getHeight() const
{
	return imageHeight;
}

unsigned char* Image::getImageBytes()
{
	return imageBytes != nullptr
		       ? imageBytes
		       : EngineModel::getInstance()
		       ->getImageService()
		       ->requestImagedata(imageFile, imageWidth, imageHeight, transR, transG, transB);
}

unsigned long Image::getId() const
{
	return id;
}

int Image::getTransR() const
{
	return transR;
}

int Image::getTransG() const
{
	return transG;
}

int Image::getTransB() const
{
	return transB;
}
