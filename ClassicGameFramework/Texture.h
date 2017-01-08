#pragma once

typedef char byte;

class Texture
{
	byte* bitmap;
public:
	//TODO
	byte* getPixelArray();
	void setPixelArray(byte* pixelArray);
};
