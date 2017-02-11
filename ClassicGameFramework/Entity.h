#pragma once

#include "PhysicalObject.h"
#include "Drawable.h"

struct Boundaries;

class Entity : public Drawable, public PhysicalObject
{
	int internalCounter = 0;
protected
	bool solid;		// True, if it is an obstacle (can't be passed). Used by Physics
	bool movable;	// True, if entity is moved via player inputs (not:position can change (through physics))
	int imageCount = 0;
	int movementSpeed;
	Boundaries* boundaries;
	int animationSpeed;
	Image** image; // File with sprites for texture (and animation)
	Boundaries* boundaries; // Size and position
	//TODO: Class for movement behavior?


public:
	int getImageCount() const;
	// Creates an entity with given texture, size, and position; as well as properties for interaction behavior.
	// TODO: since only one image is given, all sprites for the animation must be located in this image, and
	// the respective image area loaded as texture by the renderer.
	// --the bitmap must follow a particular pattern; e.g. have a size of (nx16) x 16px for n sprites,
	// so the class responsible for updating the animation knows which part of the image contains the n-th sprite
	Entity (Image * image, int movement_speed, bool solid, Boundaries * boundaries, bool movable, int animation_speed);
	
	bool isSolid() override;
	bool isMovable() override;

	int getWidth() override;
	int getHeight() override;
	int getPosX() override;
	int getPosY() override;
	int getMovementSpeed() override;

	Entity* getEntity() override;
	Image* getImage() override; // Needed for retrieving respective sprite for rendering.
	Boundaries* getBoundaries() override; // Needed by Physics for collision

	~Entity() override;

	void setPosition(int xPos, int yPos) override;

	// For setting via Position object (used by Grid)
	void setPosition(Position pos);

/*	done via SetPosition (size doesn't change after init)
 *	void setWidth(int width) override;
	void setHeight(int height) override;
	void setPosX(int posX) override;
	void setPosY(int posY) override;*/
};
