#pragma once
#include "Entity.h"
class SpacePanicModel;
class GameConfig;

class WallEntity : public Entity
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
	SpacePanicModel* model;
	GameConfig* config;
public:
	WallEntity(SpacePanicModel* model, Position* position, WallState wallState);
	bool isMiddleWall() const;
	bool makeHole() const;
};
