#include "Physics.h"
#include "Level.h"
#include <functional>

Physics::Physics()
{
}

void Physics::checkCollisions()
{// TODO: call registered listeners here

}

std::map<PhysicalObject*, std::function<void>(PhysicalObject*)> *Physics::getCollisionListener()
{
	return collisionListener;
}

Level * Physics::getLevel()
{
	return nullptr;
}

void Physics::setLevel(Level * lvl)
{
}

