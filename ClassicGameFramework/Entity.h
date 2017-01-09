#pragma once

#include "PhysicalObject.h"
#include "Drawable.h"

class Entity : public Drawable, public PhysicalObject
{
protected:
	Image* image;
	int movementSpeed;
	bool solid;
	Boundaries* boundaries;
	bool movable;
	int animationSpeed;

public:
	Entity (Image * image, int movement_speed, bool solid, Boundaries * boundaries, bool movable, int animation_speed);

	bool isSolid() override;
	bool isMovable() override;

	int getWidth() override;
	int getHeight() override;
	int getPosX() override;
	int getPosY() override;
	int getMovementSpeed() override;

	Entity* getEntity() override;
	Image* getImage() override;
	Boundaries* getBoundaries() override;

	~Entity() override;

	void setPosition(int xPos, int yPos) override;

	void setWidth(int width) override;
	void setHeight(int height) override;
	void setPosX(int posX) override;
	void setPosY(int posY) override;
};
