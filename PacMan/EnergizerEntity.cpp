#include "EnergizerEntity.h"
#include "Image.h"

EnergizerEntity::EnergizerEntity(int xPos, int yPos)
	: Entity(nullptr, 0, false, new Boundaries(xPos, yPos, 8*3, 8*3), false, 0)
{
	helper = new Image("textures/energizer.bmp", this, 0, 0, 0);
}

Image* EnergizerEntity::getImage()
{
	return helper;
}

EnergizerEntity::~EnergizerEntity()
{
	delete helper;
}
