#include "Entity.h"

Entity::Entity(Texture* texture, int movement_speed, bool solid, Boundaries* boundaries, bool movable, int animation_speed): texture(texture),
                                                                                                                             movementSpeed(movement_speed),
                                                                                                                             solid(solid),
                                                                                                                             boundaries(boundaries),
                                                                                                                             movable(movable),
                                                                                                                             animationSpeed(animation_speed)
{
}

int Entity::getWidth()
{
	return this->boundaries->width;
}

int Entity::getHeight()
{
	return this->boundaries->height;
}

int Entity::getPosX()
{
	return this->boundaries->position.x;
}

int Entity::getPosY()
{
	return this->boundaries->position.y;
}

int Entity::getMovementSpeed()
{
	return this->movementSpeed;
}

bool Entity::isSolid()
{
	return this->solid;
}

Texture* Entity::getTexture()
{
	return this->texture;
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
