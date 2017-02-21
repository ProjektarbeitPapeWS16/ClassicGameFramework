#include "Entity_Ladder.h"

Entity_Ladder::Entity_Ladder(GameConfig* config, Position* position) : Entity(
	new Image*[1]
	, 0, false, new Boundaries(
		position->x * config->getRasterWidth(),
		position->y * config->getRasterHeight(),
		config->getRasterWidth(),
		config->getRasterHeight()
	), false, 0)
{
	this->image[0] = new Image("textures/ladder.bmp", this, 200, 80, 0);
}
