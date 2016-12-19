#pragma once
#include <map>
#include "PhysicalObject.h"
#include <functional>

class Physics
{
	std::map<PhysicalObject, std::function<void(PhysicalObject&)>> collisionListeners;
public:
	explicit Physics();

	void checkCollisions();
	void addCollisionListener(PhysicalObject & object, std::function<void(PhysicalObject&)> listener);
	void removeCollisionListener(PhysicalObject & object);
};
