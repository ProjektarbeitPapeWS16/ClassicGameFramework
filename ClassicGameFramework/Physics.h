#pragma once
#include <map>
#include <functional>
class PhysicalObject;
class Level;

class Physics
{
	Level *level;
	std::map<PhysicalObject*, std::function<void>(PhysicalObject*)> *collisionListener;

public:

	explicit Physics();

	void checkCollisions();
	std::map<PhysicalObject*, std::function<void>(PhysicalObject*)> *getCollisionListener();

	static Level *getLevel();
	void setLevel(Level *lvl);
};
