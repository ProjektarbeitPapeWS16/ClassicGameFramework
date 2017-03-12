#include "BonusEntity.h"


BonusEntity::BonusEntity() 
	: Entity(nullptr, 0, false, new Boundaries(106 * 3, (69 + 6*8) * 3, 12 * 3, 12 * 3), true, 100)
{
	img = new Image("textures/Cherry12x12.bmp", this, 0, 0, 0);
}

Image* BonusEntity::getImage()
{
	return img;
}

BonusEntity::~BonusEntity()
{
}
