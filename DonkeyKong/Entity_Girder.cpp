#include "Image.h"
#include "Entity.h"

#include "GameConfig.h"
#include "Entity_Girder.h"


Entity_Girder::Entity_Girder(Position* position)
	: Entity(new Image*[0], 0, true, new Boundaries(
		position->x,
		position->y,
		8,8
	), true, 0) 
{
	image[0] = new Image("textures/DK_Girder.bmp", this, 0, 0, 0);	
}
