#pragma once
#include <map>
#include "PhysicalObject.h"
#include <functional>
class Level;

class Physics
{
private:
	Level *level;
 
	std::map<PhysicalObject, std::function<void>(PhysicalObject)> *collisionListener;

public:
	explicit Physics(Level *level);

	void checkCollisions();

	std::map<PhysicalObject, std::function<void>(PhysicalObject)> *getCollisionListener();

	Level *getLevel();
	void setLevel(Level *lvl);
};
