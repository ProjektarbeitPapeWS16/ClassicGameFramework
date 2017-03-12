#include "Image.h"
#include "Entity.h"

#include "Entity_Girder.h"

// Basic obstacle that can be walked on.
Entity_Girder::Entity_Girder(Position position)
	: Entity(new Image*[0], 0, true, new Boundaries(
		position.x,
		position.y,
		8,8
	), true, 0) 
{
	this->image[0] = new Image("textures/DK_Girder.bmp", this, 1, 0, 0); //color for alpha channel: not	quite black
}
