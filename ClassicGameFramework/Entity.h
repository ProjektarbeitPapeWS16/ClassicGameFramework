#pragma once

#include "PhysicalObject.h"
#include "Drawable.h"

struct Boundaries;

class Entity : public Drawable, public PhysicalObject
{
	int internalCounter = 0;
protected:
	int imageCount = 0;
	Image** image;
	int movementSpeed;
	bool solid;
	Boundaries* boundaries;
	bool movable;

	// speed = anzahl frames, nach denen umgeschaltet werden soll
	int animationSpeed;

public:
	int getImageCount() const;
	Entity (Image ** image, int movement_speed, bool solid, Boundaries * boundaries, bool movable, int animation_speed);

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
