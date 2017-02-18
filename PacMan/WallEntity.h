#pragma once
#include "Entity.h"

class Renderer;

class WallEntity : public Entity
{
	Renderer* renderer;
	Image* image;
public:
	WallEntity(Renderer* renderer);
	WallEntity(Renderer* renderer, Boundaries* boundaries);
};
