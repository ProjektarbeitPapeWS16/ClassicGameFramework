#include "PlayerEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "SpacePanicView.h"

PlayerEntity::PlayerEntity(Renderer* renderer): Entity(nullptr, 10, false, new Boundaries(100, 100, 100, 100), true, 3), renderer(renderer)
{
	this->image = new Image(SpacePanicView::getInstance()->renderer, "mario.bmp", 
		this->Entity::getBoundaries()
	);
}

