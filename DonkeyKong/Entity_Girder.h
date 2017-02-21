#pragma once
#include "Entity.h"

class GameConfig;

class Entity_Girder : public Entity
{
public:
	typedef enum
	{
		LEFT_WALL_1,
		LEFT_WALL_2,
		RIGHT_WALL_1,
		RIGHT_WALL_2,
		MIDDLE_WALL_1,
		MIDDLE_WALL_2
	} WallState;
private:
	WallState wallState;
public:
	Entity_Girder(GameConfig* config, Position* position, WallState wallState);
};
