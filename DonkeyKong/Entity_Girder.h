#pragma once
#include "Entity.h"

class GameConfig;

class Entity_Girder : public Entity
{
public:
	//Entity_Girder(GameConfig* config, Position* position, int offset);
	Entity_Girder(Position* position); // immediately give offset via grid
};
