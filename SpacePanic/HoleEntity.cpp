#include "HoleEntity.h"
#include "GameConfig.h"
#include "Image.h"

Image* HoleEntity::getImage()
{
	switch (state)
	{
	case STAGE3: return stage3;
	case STAGE2: return stage2;
	case STAGE1: case STAGE0: default: return stage1;
	}
}

HoleEntity::HoleEntity(
	SpacePanicModel* model,
	Position position
):
	Entity(
		new Image*[0],
		0,
		true,
		new Boundaries(
			(model->getConfig()->getRasterWidth()-1) * position.x,
			model->getConfig()->getRasterHeight() * position.y,
			model->getConfig()->getRasterWidth() * 3,
			model->getConfig()->getRasterHeight()),
		false,
		0
	), state(STAGE1),
	stage1(new Image("textures/hole1.bmp", this, 200, 80, 0)),
	stage2(new Image("textures/hole2.bmp", this, 200, 80, 0)),
	stage3(new Image("textures/hole3.bmp", this, 200, 80, 0))
{
}


bool HoleEntity::grow()
{
	switch (state)
	{
	case STAGE1:
		state = STAGE2;
		return true;
	case STAGE2:
		state = STAGE3;
		return true;
	default:
		return false;
	}
}

bool HoleEntity::shrink()
{
	switch (state)
	{
	case STAGE1:
		state = STAGE0;
		return true;
	case STAGE2:
		state = STAGE1;
		return true;
	case STAGE3:
		state = STAGE2;
	default:
		return false;
	}
}
