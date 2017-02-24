#pragma once
#include <vector>
#include "EngineModel.h"
#include "Position.h"
class PhysicalObject;
class Level;

/**
* Used by: checkAdjacency.
*/
typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Physics
{
	EngineModel* model;

	static std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool all, bool movable, bool solid);
protected:
	/**
	* For locating the direction towards an object B relative to object A.
	* Used by: checkAdjacency; Model (for enemy behavior)
	*/
	Direction* getRelativeDirection(PhysicalObject * fromA, PhysicalObject * toB, bool xAxis);

	/**
	*	For calculating distance from one object's boundaries to another.
	*	Uses: getRelativeDirection; getOverlapOnAxis
	*	@returns: distance towards the object in the desired direction (horzontal or vertical)
	*/
	int getRelativeDistance(PhysicalObject *fromA, PhysicalObject *toB, bool xAxis);

	/*
	Helper function for two given bounderies. Checks for a shared intersection interval on the x-Axis.
	*/
	int getOverlapOnAxis(PhysicalObject * objA, PhysicalObject * objB, bool xAxis);

	/*
	Helper function for two given bounderies. Checks for a shared intersection interval on the x-Axis or the y-Axis.
	Used by: checkCollisions, checkAdjacency (TODO)
	@return Amount of pixels, if at least one vertical line intersects with both boundaries.
	*/
	int getOverlapOnXAxis(PhysicalObject* objA, PhysicalObject *objB);

	/*
	Helper function for two given bounderies. Checks for a shared intersection interval on the x-Axis.
	Used by: checkCollisions, checkAdjacency (TODO)
	@return Amount of pixels, if at least one horizontal line intersects with both boundaries.
	*/
	int getOverlapOnYAxis(PhysicalObject* objA, PhysicalObject *objB);
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

	/**
	 * Gets all background objects on given position.
	 * @param pos The position.
	 * @returns Vector of Objects on the given position.
	 */
	std::vector<PhysicalObject*>* backgroundOnPosition(Position pos) const;


	/**
	* For locating the horizontal direction towards an object B relative to object A.
	* Used by: checkAdjacency; Model (for enemy behavior)
	* @result True, if first given object has higher x-Coordinate
	*/
	bool isRightFromOther(PhysicalObject * obj, PhysicalObject * objB);
	/**
	* For locating the vertical direction towards an object B relative to object A.
	* Used by: checkAdjacency; Model (for enemy behavior)
	* @result True, if first given object has higher y-Coordinate
	*/
	bool isAboveOther(PhysicalObject * obj, PhysicalObject * objB);

	/**
	*	For calculating width (in pixels) from one object's boundaries to another.
	*	Uses: getRelativeDirection; getOverlapOnAxis
	*	@returns: x-distance towards the object. (Negative means going left on the x-axis.)
	*/
	int getRelativeXDistance(PhysicalObject *fromA, PhysicalObject *toB);
	/**
	*	For calculating height (in pixels) from one object's boundaries to another.
	*	Uses: getRelativeDirection; getOverlapOnAxis
	*	@returns: y-distance towards the object. (Negative means going down on the y-axis.)
	*/
	int getRelativeYDistance(PhysicalObject *fromA, PhysicalObject *toB);

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
	/*
	 * Checks if a given object is adjacent to a solid object in the level.
	 *	Usage: Determining possible player movement (e.g. state for standing on ground; preventing movement into walls)
	 *	@param checkObject		The object to test
	 *	@param physicalObjects	The physicalObjects of the level to iterate through
	 *	@param boundaryEdge	Determines from which direction the adjacency should be tested. (E.g. objects to the right of the checkObject?)
	 *	@bool  strict			If true, adds a physical object to the result even if only one pixel of both boundaries are adjacent.
	 *							If false, only adds a physical object if its boundary has adjacent pixels at the center of the textObject's edge.
	 *	@returns	All physical objects that are considered adjacent to the requested direction of the object 
	*/
	std::vector<PhysicalObject*>* Physics::checkAdjacency(PhysicalObject* checkObject, std::vector<PhysicalObject*>* physicalObjects, Direction boundaryEdge, bool checkStrict);
};
