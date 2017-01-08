#pragma once
#include "Texture.h"

class Drawable
{
public:
	virtual ~Drawable()
	{
	}

	virtual unsigned int getWidth() { return 0; };
	virtual unsigned int getHeight() { return 0; };
	virtual unsigned int getPosX() { return 0; };
	virtual unsigned int getPosY() { return 0; };
	virtual Texture * getTexture() { return {}; };
};
