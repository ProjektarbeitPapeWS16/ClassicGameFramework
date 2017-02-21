#include "DotEntity.h"
#include "Image.h"


DotEntity::DotEntity(int xPos, int yPos) 
	: Entity(nullptr, 0, false, new Boundaries(xPos, yPos, 2*3, 2*3), false, 0)
{
	helper = new Image("textures/dot.bmp", this, 0, 0, 0);
}

Image* DotEntity::getImage()
{
	return helper;
}

DotEntity::~DotEntity()
{
	delete helper;
}
