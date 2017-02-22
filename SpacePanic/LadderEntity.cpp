#include "LadderEntity.h"

LadderEntity::LadderEntity(GameConfig* config, Position* position): Entity(
	new Image*[1] {
		new Image("textures/ladder.bmp", this, 200, 80, 0)
	}
	, 0, false, new Boundaries(
		position->x * config->getRasterWidth(),
		position->y * config->getRasterHeight(),
		config->getRasterWidth(),
		config->getRasterHeight()
	), false, 0)
{
}
