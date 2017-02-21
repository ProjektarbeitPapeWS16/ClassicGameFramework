#pragma once
#include "Boundaries.h"

class Entity;

class PhysicalObject
{
public:
	virtual ~PhysicalObject()
	{
	}

	virtual int getMovementSpeed() { return 0; };
	virtual bool isSolid() { return false; };

	virtual Boundaries* getBoundaries() { return new Boundaries(0, 0, 0, 0); };

	virtual void setPosition(int xPos, int yPos)
	{
	};
	virtual Entity* getEntity() { return nullptr; };
	virtual bool isMovable() { return false; };

	virtual void collideWith(PhysicalObject* physicalObject)
	{
	};
};
