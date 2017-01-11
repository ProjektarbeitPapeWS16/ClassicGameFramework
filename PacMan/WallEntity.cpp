#include "WallEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "PacManView.h"

WallEntity::WallEntity(Renderer* renderer, Boundaries* boundaries) : Entity(nullptr, 10, false, boundaries, true, 3), renderer(renderer)
{
	this->image = new Image(PacManView::getInstance()->renderer, "mario.bmp", // need that file :o
		this->Entity::getBoundaries()
		);
}

WallEntity::WallEntity(Renderer* renderer) : Entity(nullptr, 10, false, new Boundaries(100, 100, 100, 100), true, 3), renderer(renderer)
{
	this->image = new Image(PacManView::getInstance()->renderer, "mario.bmp", // need that file :o
		this->Entity::getBoundaries()
		);
}

