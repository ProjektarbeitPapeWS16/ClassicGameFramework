#pragma once
#include "SpacePanicModel.h"
#include "WallEntity.h"

class MovableEntity : public Entity
{
protected:
	virtual SpacePanicModel* getModel() const = 0;
	virtual GameConfig* getConfig() const = 0;
	PhysicalObject* canMoveUp();
	PhysicalObject* canMoveDown();
	PhysicalObject* canMoveLeft();
	PhysicalObject* canMoveRight();
	HoleEntity::HoleState canFall(Position pos);
	HoleEntity::HoleState canFall();
	MovableEntity(Image** image, int movement_speed, bool solid, Boundaries* boundaries, bool movable, int animation_speed);


public:
	

};
