#include "Physics.h"

Physics::Physics()
{
}

void Physics::checkCollisions()
{// TODO: call registered listeners here

}

void Physics::addCollisionListener(PhysicalObject& object, std::function<void(PhysicalObject&)> listener)
{
	collisionListeners.insert_or_assign(object, listener);
}

void Physics::removeCollisionListener(PhysicalObject& object)
{
	collisionListeners.erase(object);
}
