#include "WallEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "PacManView.h"

WallEntity::WallEntity(char* imagePath, Boundaries* boundaries) : Entity(nullptr, 0, true, boundaries, false, 3)
{
	image = new Image(imagePath, this, 0, 0, 0);
}

Image* WallEntity::getImage()
{
	return image;
}