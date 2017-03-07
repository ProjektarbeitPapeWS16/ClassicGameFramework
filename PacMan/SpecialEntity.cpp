#include "SpecialEntity.h"
#include "Image.h"


SpecialEntity::SpecialEntity(int life) 
	: Entity(nullptr, 0, false, new Boundaries((18 + life * 16) * 3, 3 * 3, 10 * 3, 10 * 3), true, 100)
{
	img = new Image("textures/PacMan/pacmanLeft.bmp", this, 0, 0, 0);
}


SpecialEntity::~SpecialEntity()
{
}


Image* SpecialEntity::getImage()
{
	return img;
}