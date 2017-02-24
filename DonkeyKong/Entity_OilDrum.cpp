#include "Entity_OilDrum.h"
#include "Image.h"

Entity_OilDrum::Entity_OilDrum(Position * position)
	: Entity(new Image*[0], 0, true, new Boundaries(
		position->x,
		position->y,
		8, 8
	), true, 0) {
	image[0] = new Image("textures/DK_Oildrum.bmp", this, 0, 0, 0);

}
