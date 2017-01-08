#include "Entity.h"

Entity::Entity( Texture* texture, int movement_speed, bool solid, Boundaries* boundaries, bool movable, int animation_speed): texture(texture),
                                                                                                                                         movementSpeed(movement_speed),
                                                                                                                                         solid(solid),
                                                                                                                                         boundaries(boundaries),
                                                                                                                                         movable(movable),
                                                                                                                                         animationSpeed(animation_speed)
{
}

unsigned Entity::getWidth()
{
	return this->boundaries->width;
}

unsigned Entity::getHeight()
{
	return this->boundaries->height;
}

unsigned Entity::getPosX()
{
	return this->boundaries->position.x;
}

unsigned Entity::getPosY()
{
	return this->boundaries->position.y;
}

Texture* Entity::getTexture()
{
	return this->texture;
}

int Entity::getMovementSpeed()
{
	return this->movementSpeed;
}

bool Entity::isSolid()
{
	return this->solid;
}

Boundaries* Entity::getBoundaries()
{
	return this->boundaries;
}

void Entity::setPosition(int xPos, int yPos)
{
	this->boundaries->position.x = xPos;
	this->boundaries->position.y = yPos;
}

bool Entity::isMovable()
{
	return this->movable;
}

Entity* Entity::getEntity()
{
	return this;
}

Entity::~Entity()
{
}
