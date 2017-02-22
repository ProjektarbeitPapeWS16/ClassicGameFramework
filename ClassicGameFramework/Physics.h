#pragma once
#include <vector>
#include "EngineModel.h"
class PhysicalObject;
class Level;

class Physics
{
	EngineModel* model;

	static std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool all, bool movable, bool solid);
public:
	/**
	 * @deprecated Please use Physics(EngineModel* model) instead.
	 */
	Physics();

	/**
	 * Creates the Physics-Engine for a game.
	 * @param model The game model.
	 */
	Physics(EngineModel* model);
	
	static std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool movable, bool solid);
	/**
	 * Checks the given Objects for collisions. If Collisions happened, 
	 * Objects will be notified by calling {@link PhysicalObject#collideWith(PhysicalObject* objB)}.
	 * Only movable Objects are checked for collisions.
	 * There will be the pairs (A, B) and (B, A) in the map.
	 * @param physicalObjects Vector of all Objects that need to be checked for collisions.
	 * @returns Vector of all pairs of given Objects that collided. 
	 */
	static std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* checkCollisions(std::vector<PhysicalObject*>* physicalObjects);

	/**
	 * Checks the current level for collisions by using {@link Physics.checkCollisions(std::vector<PhysicalObject*>* physicalObjects)}.
	 * @returns Vector of all pairs of movable Objects that collided. 
	 */
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* checkCollisions() const;

	/*
		Checks if the parameter collides with anything, 
		all physical objects that collided are returned as a std::vector.
	*/
	std::vector<PhysicalObject*>* checkCollisions(PhysicalObject*, std::vector<PhysicalObject*>*);
};
