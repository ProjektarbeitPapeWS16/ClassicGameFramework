#pragma once
#include "Entity.h"

class Renderer;

class WallEntity : public Entity
{
	Image* helper;
public:
	WallEntity(char* imagePath, Boundaries* boundaries);
	Image* getImage() override;
	~WallEntity();
};
