#include "Image.h"
#include <cstdio>
#include "EngineModel.h"


std::map<std::string, unsigned char*> Image::path_images = std::map<std::string, unsigned char*>();
std::map<std::string, long> Image::path_refcount = std::map<std::string, long>();
std::map<std::string, std::pair<int, int>> Image::path_width_height = std::map<std::string, std::pair<int, int>>();


const char* Image::getImageFile() const
{
	return imageFile;
}

// Stores RGBA-pixeldata of a given bitmap-file in a char array
unsigned char* Image::readImage2ByteArray()
{
	FILE* file;
	fopen_s(&file, imageFile, "rb");

	if (file == nullptr)
	{
		return nullptr;
	}

	// obtain file size:
	fseek(file, 0, SEEK_END);
	auto lSize = ftell(file);
	rewind(file);

	auto data = new unsigned char[lSize];
	fread(data, lSize, 1, file);
	fclose(file);


	// extract image height and width from header 
	imageWidth = *reinterpret_cast<int*>(&data[18]);
	imageHeight = *reinterpret_cast<int*>(&data[22]);
	auto padding = 0;
	while ((imageWidth * 3 + padding) % 4 != 0)
	{
		padding++;
	}
	auto widthnew = imageWidth * 3 + padding;

	//auto endPos = 54 + (widthnew * height);


	auto ret = new unsigned char[imageWidth * 4 * imageHeight];

	for (auto line = 0; line < imageHeight; line++)
	{
		for (auto column = 0, retcolumn = 0; column < widthnew - padding; column += 3 , retcolumn += 4)
		{
			auto ri = line * (imageWidth * 4) + retcolumn;
			auto gi = ri + 1;
			auto bi = ri + 2;
			auto ai = ri + 3;

			ret[ri] = data[line * widthnew + column + 54 + 2];
			ret[gi] = data[line * widthnew + column + 54 + 1];
			ret[bi] = data[line * widthnew + column + 54 + 0];

			if (transR != 256 && transB != 256 && transG != 256 && ret[ri] == static_cast<unsigned char>(transR) && ret[gi] == static_cast<unsigned char>(transG) && ret[bi] == static_cast<unsigned char>(transB))
			{
				ret[ai] = 0;
			}
			else
			{
				ret[ai] = 255;
			}
		}
	}

	delete[] data;
	return ret;
}

Image::Image(const char* imageFile,
             unsigned short transR, unsigned short transG, unsigned short transB) : imageWidth(0), imageHeight(0), imageFile(imageFile),
                                                                                    imageBytes(nullptr), transR(transR), transG(transG), transB(transB)
{
	if (path_refcount.find(imageFile) == path_refcount.end())
	{
		path_refcount.insert_or_assign(imageFile, 1);
		loadImageBytes();

		auto x = path_width_height.at(imageFile);
		this->imageWidth = x.first;
		this->imageHeight = x.second;
	}
	else
	{
		auto cnt = path_refcount.at(imageFile) + 1;
		path_refcount.insert_or_assign(imageFile, cnt);

		auto x = path_width_height.at(imageFile);
		this->imageWidth = x.first;
		this->imageHeight = x.second;
	}
}

Image::Image(const char* imageFile, Entity* entity, unsigned short transR, unsigned short transG, unsigned short transB) :
	Image(imageFile, transR, transG, transB)
{
}

Image::Image(unsigned char* imageBytes, int width, int height, unsigned short transR, unsigned short transG, unsigned short transB):
	imageWidth(width), imageHeight(height), imageFile(nullptr), imageBytes(imageBytes), transR(transR), transG(transG), transB(transB)
{
}

Image::~Image()
{
	if(imageFile)
	{
		auto cnt = path_refcount.at(imageFile) - 1;
		if (cnt == 0)
		{
			delete path_images.at(imageFile);
			path_images.erase(imageFile);
			path_refcount.erase(imageFile);
		}
		else
		{
			path_refcount.insert_or_assign(imageFile, cnt);
		}
	} else
	{
		delete imageBytes;
	}
	
}

bool Image::isLoaded() const
{
	return imageBytes || imageFile && path_images.find(imageFile) != path_images.end();
}

void Image::loadImageBytes()
{
	if (!isLoaded() && imageFile)
	{
		path_images.insert_or_assign(imageFile, readImage2ByteArray());
		path_width_height.insert_or_assign(imageFile, std::make_pair(imageWidth, imageHeight));
	}
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
	if (!isLoaded())
	{
		loadImageBytes();
	}

	return imageBytes ? imageBytes : path_images.at(imageFile);
}
