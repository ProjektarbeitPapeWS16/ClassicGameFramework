#include "EnemyEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "PacManView.h"

EnemyEntity::EnemyEntity(Renderer* renderer) : Entity(nullptr, 10, false, new Boundaries(100, 100, 100, 100), true, 3), renderer(renderer)
{
	this->image = new Image(PacManView::getInstance()->renderer, "mario.bmp", // need that file :o
		this->Entity::getBoundaries()
		);
}
