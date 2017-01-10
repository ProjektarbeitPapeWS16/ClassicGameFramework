#pragma once
#include "Config.h"

class Entity;

class PhysicalObject
{
public:
	virtual ~PhysicalObject()
	{
	}

	virtual int getMovementSpeed() { return 0; };
	virtual bool isSolid() { return false; };

	// TODO: Get boundaries from Entity
	virtual Boundaries* getBoundaries() { return new Boundaries(0, 0, 0, 0); };

	virtual void setPosition(int xPos, int yPos)
	{
	};
	virtual Entity* getEntity() { return nullptr; };
	virtual bool isMovable() { return false; };
};
