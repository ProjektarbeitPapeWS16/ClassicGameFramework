#pragma once
#include <map>
#include <functional>
class PhysicalObject;
class Level;

class Physics
{
	Level* level;

	std::map<PhysicalObject*, std::function<void(PhysicalObject*)>*>* collisionListener;

public:
	explicit Physics();

	// Checks the set Level for collisions. Only Movable PhysicalObjects of the Level are being checked for collisions. 
	// If any collision with another PhysicalObject happens, the corresponding functions in the collisionListener is being called.
	// Note that if A collides with B, the functions A(B) and B(A) are being both called. (if A is setMovable, and B is not)
	// TODO as of now if both A and B are setMovable the functions are being called double. We don't want that.
	void checkCollisions();

	// Gets the collision listeners. If you want to notice if a PhysicalObject collides with another, add a functor into this map. 
	// If a collision happens in checkCollision() the functor will be called with the PhysicalObject it collided with.
	std::map<PhysicalObject*, std::function<void(PhysicalObject*)>*>* getCollisionListener();

	Level* getLevel();

	// Please set the Level before you check for collisions.
	void setLevel(Level* level);
};
