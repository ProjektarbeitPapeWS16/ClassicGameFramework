#pragma once
#include "Entity.h"

class Renderer;

class WallEntity : public Entity
{
	Renderer* renderer;
public:
	WallEntity(Renderer* renderer);
	WallEntity(Renderer* renderer, Boundaries* boundaries);
};
