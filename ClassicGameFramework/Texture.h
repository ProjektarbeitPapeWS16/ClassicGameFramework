#pragma once
#include "Config.h"

class Texture
{
	byte* bitmap;
public:
	//TODO
	byte* getPixelArray();
	void setPixelArray(byte* pixelArray);
};
