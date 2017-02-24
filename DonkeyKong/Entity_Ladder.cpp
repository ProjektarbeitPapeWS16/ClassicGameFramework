#include "Entity_Ladder.h"
#include "Image.h"

Entity_Ladder::Entity_Ladder(Position* position) : Entity(
	new Image*[1]
	, 0, false, new Boundaries(
		position->x,
		position->y,
		8,8
	), false, 0)
{
	this->image[0] = new Image("textures/DK_Ladder.bmp", this, 0, 0, 0);
}
