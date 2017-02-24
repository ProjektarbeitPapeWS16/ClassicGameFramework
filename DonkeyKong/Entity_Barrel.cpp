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
	img = new Image("stone1left.bmp", this, 0, 0, 0);
	//todo
}

void Entity_Barrel::execute()
{
}

Image * Entity_Barrel::getImage()
{
	return img;
}
