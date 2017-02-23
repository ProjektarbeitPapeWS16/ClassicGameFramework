#include "WallEntity.h"
#include "GameConfig.h"
#include "Image.h"
#include "HoleEntity.h"
#include "SpacePanicModel.h"

WallEntity::WallEntity(SpacePanicModel* model, Position* position, WallState wallState) :
	Entity(
		new Image*[1],
		0,
		true,
		new Boundaries(
			position->x * model->getConfig()->getRasterWidth(),
			position->y * model->getConfig()->getRasterHeight(),
			model->getConfig()->getRasterWidth(),
			model->getConfig()->getRasterHeight()
		),
		false,
		0
	), wallState(wallState), model(model), config(model->getConfig())
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
	case MIDDLE_WALL_2: default:
		image[0] = new Image("textures/stone2middle.bmp", this, 200, 80, 0);
		break;
	}
}

bool WallEntity::isMiddleWall() const
{
	return wallState == MIDDLE_WALL_1 || wallState == MIDDLE_WALL_2;
}

bool WallEntity::makeHole() const
{
	if(isMiddleWall())
	{
		HoleEntity* hole = new HoleEntity(model, Position(boundaries->position.x - config->getRasterWidth(), boundaries->position.y));
		static_cast<Stage*>(model->getLevel())->addHole(hole);
		return true;
	} else
	{
		return false;
	}
}
