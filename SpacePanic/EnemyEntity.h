#pragma once
#include "Entity.h"

class GameConfig;

class EnemyEntity : public Entity
{
public:
	EnemyEntity(GameConfig* config, Position* position);
	void execute();
};
