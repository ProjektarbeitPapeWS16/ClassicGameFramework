#pragma once

class Texture;

class Drawable
{
public:
	virtual ~Drawable()
	{
	}

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	virtual Texture* getTexture() = 0;
};
