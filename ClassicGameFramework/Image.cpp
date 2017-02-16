#include "Image.h"
#include "Entity.h"
#include <cstdio>

const char* Image::getImageFile() const
{
	return imageFile;
}

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

			if (transR != 256 && transB != 265 && transG != 265 && ret[ri] == static_cast<unsigned char>(transR) && ret[gi] == static_cast<unsigned char>(transG) && ret[bi] == static_cast<unsigned char>(transB))
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

Image::Image(const char* imageFile, Entity* entity, unsigned short transR, unsigned short transG, unsigned short transB) : imageFile(imageFile), entity(entity), transR(transR), transG(transG), transB(transB)
{	
}


Image::~Image()
{
	delete imageBytes;
}

Entity* Image::getEntity() const
{
	return entity;
}

bool Image::isLoaded() const
{
	return imageBytes != nullptr;
}

void Image::loadImageBytes()
{
	if(!isLoaded())
	{
		imageBytes = readImage2ByteArray();
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

unsigned char* Image::getImageBytes() const
{
	return imageBytes;
}
