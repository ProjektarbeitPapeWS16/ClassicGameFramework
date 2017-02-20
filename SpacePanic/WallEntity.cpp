#include "WallEntity.h"
#include "GameConfig.h"
#include "Image.h"

WallEntity::WallEntity(GameConfig* config, Position* position, WallState wallState) :
	Entity(
		new Image*[1],
		0,
		true,
		new Boundaries(
			position->x * config->getRasterWidth(),
			position->y * config->getRasterHeight(),
			config->getRasterWidth(),
			config->getRasterHeight()
		),
		false,
		0
	), wallState(wallState)
{
	switch (wallState)
	{
	case LEFT_WALL_1: 
		image[0] = new Image("textures/stone1left.bmp", this, 200, 80, 0);
		break;
	case LEFT_WALL_2: 
		image[0] = new Image("textures/stone2left.bmp", this, 200, 80, 0);
		break;
	case RIGHT_WALL_1:
		image[0] = new Image("textures/stone1right.bmp", this, 200, 80, 0);
		break;
	case RIGHT_WALL_2:
		image[0] = new Image("textures/stone2right.bmp", this, 200, 80, 0);
		break;
	case MIDDLE_WALL_1:
		image[0] = new Image("textures/stone1middle.bmp", this, 200, 80, 0);
		break;
	case MIDDLE_WALL_2:
	default:
		image[0] = new Image("textures/stone2middle.bmp", this, 200, 80, 0);
		break;
	}
}
