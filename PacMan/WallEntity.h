#pragma once
#include "Entity.h"

class Renderer;

class WallEntity : public Entity
{
	Image* image;
public:
	WallEntity(char* imagePath, Boundaries* boundaries);
	Image* getImage() override;
	~WallEntity();
};
