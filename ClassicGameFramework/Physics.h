#pragma once
#include <functional>
#include <vector>
class PhysicalObject;
class Level;

class Physics
{
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* collisionListener;

public:
	explicit Physics();

	// Checks the set Level for collisions. If Collisions happened, they will be given back in the map. 
	// Only movable Objects are checked for collissions. If two movable Ojects (A and B) collid, 
	// there will be the pairs (A, B) and (B, A) in the map.
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* checkCollisions(std::vector<PhysicalObject*>* physicalObjects) const;
};
