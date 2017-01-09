#pragma once
#include "Entity.h"

class Renderer;

class PlayerEntity : public Entity
{
	Renderer* renderer;
public:
	PlayerEntity(Renderer* renderer);	
};
