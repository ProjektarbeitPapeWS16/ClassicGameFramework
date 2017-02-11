#pragma once
#include "Entity.h"

class Renderer;

class EnemyEntity : public Entity
{
	Renderer* renderer;
public:
	EnemyEntity(Renderer* renderer);
};
