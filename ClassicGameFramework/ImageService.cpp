#include "ImageService.h"
#include "Config.h"

unsigned char* ImageService::readImage2ByteArray(char const* imageFile, int& imageWidth, int& imageHeight, int transR, int transG, int transB)
{
	FILE* file;;
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

unsigned char* ImageService::requestImagedata(const char* imageFile, int& imageWidth, int& imageHeight, unsigned short transR, unsigned short transG, unsigned short transB)
{
	removeUnused();

	auto unique_image = std::make_pair(std::make_pair(std::make_pair(imageFile, transR), transG), transB);
	if (imageSignature_id.find(unique_image) != imageSignature_id.end())
	{
		auto unique_id = imageSignature_id.at(unique_image);
		id_lastAccess.insert_or_assign(unique_id, Config::currentTimeMillis());

		std::pair<int, int> width_height = id_width_height.at(unique_id);
		imageWidth = width_height.first;
		imageHeight = width_height.second;

		return id_imagedata.at(unique_id);
	}
	else
	{
		int width, height;
		auto imagedata = readImage2ByteArray(imageFile, width, height, transR, transG, transB);

		auto unique_id = imageCount++;
		id.insert(unique_id);
		id_imageSignature.insert(std::make_pair(unique_id, unique_image));
		imageSignature_id.insert(std::make_pair(unique_image, unique_id));
		id_imagedata.insert(std::make_pair(unique_id, imagedata));
		id_lastAccess.insert(std::make_pair(unique_id, Config::currentTimeMillis()));
		id_width_height.insert(std::make_pair(unique_id, std::make_pair(width, height)));
		return imagedata;
	}
}

ImageService::ImageService() : ImageService(15000)
{
}

ImageService::ImageService(long timeUntilUnusedMillis) : timeUntilUnused(timeUntilUnusedMillis)
{	
}

void ImageService::removeUnused()
{
	for(auto x : id_lastAccess)
	{
		if(x.second + timeUntilUnused < Config::currentTimeMillis())
		{
			id_width_height.erase(x.first);
			id_imagedata.erase(x.first);
			
			auto unique_image = id_imageSignature.at(x.first);
			id_imageSignature.erase(x.first);
			imageSignature_id.erase(unique_image);
			id.erase(x.first);
		}
	}
}

long ImageService::getIdBySignature(const char* file, int trans_r, int trans_g, int trans_b)
{
	auto x = std::make_pair(std::make_pair(std::make_pair(file, trans_r), trans_g), trans_b);
	if(imageSignature_id.find(x) != imageSignature_id.end())
	{
		return imageSignature_id.at(x);
	} else
	{
		return -1L;
	}
}
