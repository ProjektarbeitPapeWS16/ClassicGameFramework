#include "PlayerEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "SpacePanicView.h"

PlayerEntity::PlayerEntity(Renderer* renderer): Entity(nullptr, 10, false, new Boundaries(100, 100, 100, 100), true, 30), renderer(renderer)
{
	this->imageCount = 2;
	this->image = new Image*[imageCount]{
		new Image(SpacePanicView::getInstance()->renderer, "mario.bmp", this),
		new Image(SpacePanicView::getInstance()->renderer, "textur.bmp", this)
	};
	
}

