#pragma once

#include "PhysicalObject.h"
#include "Drawable.h"

class Entity : public Drawable, public PhysicalObject
{
	Texture* texture;
	int movementSpeed;
	bool solid;
	Boundaries* boundaries;
	bool movable;
	int animationSpeed;

public:
	Entity (Texture * texture, int movement_speed, bool solid, Boundaries * boundaries, bool movable, int animation_speed);

	bool isSolid() override;
	bool isMovable() override;

	unsigned getWidth() override;
	unsigned getHeight() override;
	unsigned getPosX() override;
	unsigned getPosY() override;
	int getMovementSpeed() override;

	Entity* getEntity() override;
	Texture* getTexture() override;
	Boundaries* getBoundaries() override;

	~Entity() override;

	void setPosition(int xPos, int yPos) override;
};
