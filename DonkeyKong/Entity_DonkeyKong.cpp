#include "Image.h"
#include "Entity.h"

#include "Entity_DonkeyKong.h"

// TODO
Entity_DonkeyKong::Entity_DonkeyKong(Position * position)
	: Entity(new Image*[1], 0, false, 
		new Boundaries(
			position->x, position->y,
			32, 32
		), false, 0
	)
{
this->image[0] = new Image("textures/DK_Ladder.bmp", this, 91, 127, 255);
}
