#include "Entity_Pauline.h"
#include "Image.h"

Entity_Pauline::Entity_Pauline(Position * position) : Entity(
	new Image*[1]
	, 0, false, new Boundaries(
		position->x,
		position->y,
		16, 14 // 2x3 on grid
	), false, 0)
{
	this->image[0] = new Image("textures/DK_Pauline.bmp", this, 0, 0, 0);
}