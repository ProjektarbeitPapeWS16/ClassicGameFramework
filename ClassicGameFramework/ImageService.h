#pragma once
#include <set>
#include <map>
#include <vector>

class ImageService
{
	long imageCount = 0L;
	std::map<std::pair<std::pair<std::pair<const char*, unsigned short>, unsigned short>, unsigned short>, long> imageSignature_id;
	std::set<long> id;
	std::map<long, unsigned char*> id_imagedata;
	std::map<long, long> id_lastAccess;
	std::map<long, std::pair<int, int>> id_width_height;
	long timeUntilUnused;
	std::map<long, std::pair<std::pair<std::pair<const char*, unsigned short>, unsigned short>, unsigned short>> id_imageSignature;
	static unsigned char* readImage2ByteArray(char const* imageFile, int& imageWidth, int& imageHeight, int transR, int transG, int transB);
public:
	unsigned char* requestImagedata(const char* imageFile, int& imageWidth, int& imageHeight, unsigned short transR, unsigned short transG, unsigned short transB);
	ImageService();
	ImageService(long timeUntilUnusedMillis);
	void removeUnused();
	long getIdBySignature(const char* file, int trans_r, int trans_g, int trans_b);
};
