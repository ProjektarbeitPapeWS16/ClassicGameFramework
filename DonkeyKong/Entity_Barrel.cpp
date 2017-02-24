#include "Entity_Barrel.h"
#include "GameConfig.h"
#include "Image.h"

Entity_Barrel::Entity_Barrel(GameConfig* config, Position* position) :
	Entity(new Image*[0], 5, false, new Boundaries(
		position->x * config->getRasterWidth(),
		position->y * config->getRasterHeight(),
		config->getRasterWidth() * 2,
		config->getRasterHeight() * 2
	), true, 3)
{
	//todo
}