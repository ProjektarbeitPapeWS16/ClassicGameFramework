#include "Image.h"
#include "Entity.h"

#include "GameConfig.h"
#include "Entity_Girder.h"


Entity_Girder::Entity_Girder(GameConfig* config, Position* position, int yOffset)
	: Entity(new Image*[0], 0, true, new Boundaries(
		position->x * config->getRasterWidth(),
		position->y * config->getRasterHeight() + yOffset,
		config->getRasterWidth(),
		config->getRasterHeight()
	), true, 0) {
	image[0] = new Image("textures/stone1left.bmp", this, 200, 80, 0);
	
}