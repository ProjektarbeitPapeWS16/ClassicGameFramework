#pragma once
#include "Drawable.h"
#include "PhysicalObject.h"

class Entity : public Drawable, public PhysicalObject
{
	Texture texture;
	int movementSpeed;
	bool solid;
	Boundaries* boundaries;
	bool movable;
	int animationSpeed;
public:
	
	Entity(const Texture & texture, int movement_speed, bool solid, Boundaries * boundaries, bool movable, int animation_speed);

	unsigned getWidth() override;
	unsigned getHeight() override;
	unsigned getPosX() override;
	unsigned getPosY() override;
	Texture getTexture() override;
	int getMovementSpeed() override;
	bool isSolid() override;
	Boundaries* getBoundaries() override;
	void setPosition(int xPos, int yPos) override;
	bool isMovable() override;
	Entity* getEntity() override;
	~Entity() override;
};
