#pragma once

class Texture;

class Drawable
{
public:
	virtual ~Drawable()
	{
	}

	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;
	virtual unsigned int getPosX() = 0;
	virtual unsigned int getPosY() = 0;
	virtual Texture* getTexture() = 0;
};
