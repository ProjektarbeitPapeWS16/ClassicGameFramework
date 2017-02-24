#include "Physics.h"
#include <vector>
#include "PhysicalObject.h"
#include "Level.h"
#include "EngineModel.h"
#include "Session.h"


Physics::Physics() : Physics(nullptr)
{
}

Physics::Physics(EngineModel* model) : model(model)
{
}


std::vector<PhysicalObject*>* Physics::backgroundOnPosition(Position pos) const
{
	auto ret = new std::vector<PhysicalObject*>();
	auto physObj = model->getLevel()->getPhysicalObjects();
	for (auto i = 0; i < physObj->size(); i++)
	{
		auto x = physObj->at(i);
		if (x->isMovable()) // Nur Hintergründe, keine beweglichen Entities
		{
			continue;
		}

		auto y = x->getBoundaries();
		if (pos.x >= y->real_x()
			&& pos.x <= y->real_x() + y->real_width() - 1
			&& pos.y >= y->real_y()
			&& pos.y <= y->real_y() + y->real_height() - 1)
		{
			ret->push_back(x);
		}
	}
	delete physObj;
	return ret;
}

// Checks collisions for a given vector of physical objects; selection for check can be filtered.
// Checks, if any boundaries of movable POs intersect with other POs.
// @param all If true, checks collisions with all types of other objects. Set false if you want to check for certain attributes only.
// @param movable If true [&&all=false], checks only collisions with other movable objects
// @param solid If true [&&all=false], checks only collisions with solid objects
std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool all, bool movable, bool solid)
{
	auto collisions = new std::vector<std::pair<PhysicalObject*, PhysicalObject*>>();

	// bewegbare Objekte werden nach Kollision abgefragt
	if (physicalObjects)
	{
		for (unsigned int i = 0; i < physicalObjects->size(); i++)
		{
			auto objA = physicalObjects->at(i);
			if (objA->isMovable())
			{
				// Schleife über alle die in Frage kommen

				for (auto iteratorB = physicalObjects->begin(); iteratorB != physicalObjects->end(); ++iteratorB)
				{
					auto objB = *iteratorB;
					if (objA != objB && (all || (objB->isMovable() == movable && objB->isSolid() == solid)))
					{
						if ((objA->getBoundaries()->real_x() + objA->getBoundaries()->real_width() - 1) >= objB->getBoundaries()->real_x() && // aRight >= bLeft &&
							(objB->getBoundaries()->real_x() + objB->getBoundaries()->real_width() - 1) >= objA->getBoundaries()->real_x() && // bRight >= aLeft &&
							(objA->getBoundaries()->real_y() + objA->getBoundaries()->real_height() - 1) >= objB->getBoundaries()->real_y() && // aTop >= bBot &&
							(objB->getBoundaries()->real_y() + objB->getBoundaries()->real_height() - 1) >= objA->getBoundaries()->real_y()) // bTop >= aBot
						{
							collisions->push_back(std::make_pair(objA, objB));
							objA->collideWith(objB);
						}
					}
				}
			}
		}
	}

	return collisions;
}

int Physics::getOverlapOnAxis(PhysicalObject * objA, PhysicalObject * objB, bool xAxis)
{
	int sharedPixels;

	int xLeftA = objA->getBoundaries()->real_x();
	int xRightA = objA->getBoundaries()->real_x() + objA->getBoundaries()->real_width();
	int yBottomA = objA->getBoundaries()->real_y();
	int yTopA = objA->getBoundaries()->real_y() + objA->getBoundaries()->real_height();

	int xLeftB = objB->getBoundaries()->real_x();
	int xRightB = objB->getBoundaries()->real_x() + objB->getBoundaries()->real_width();
	int yBottomB = objB->getBoundaries()->real_y();
	int yTopB = objB->getBoundaries()->real_y() + objB->getBoundaries()->real_height();

	int overlapStart;
	int overlapEnd;
	
	if (xAxis) {
		(xLeftB >= xLeftA) ? overlapStart = xLeftB : overlapStart = xLeftA;
		(xRightB <= xRightA) ? overlapEnd = xRightB : overlapEnd = xRightA;
	} 	
	else {
		(yBottomB >= yBottomA) ? overlapStart = yBottomB : overlapStart = yBottomA;
		(yTopB <= yTopA) ? overlapEnd = yTopB : overlapEnd = yTopA;
	}

	sharedPixels = overlapEnd - overlapStart;	// If negative, describes distance.

	return sharedPixels;
}

int Physics::getOverlapOnXAxis(PhysicalObject * objA, PhysicalObject * objB)
{
	return getOverlapOnAxis(objA, objB, true);
}

int Physics::getOverlapOnYAxis(PhysicalObject * objA, PhysicalObject * objB)
{
	return getOverlapOnAxis(objA, objB, false);
}


Direction * Physics::getRelativeDirection(PhysicalObject * fromA, PhysicalObject * toB, bool xAxis)
{
	Direction* result = nullptr;
	if (xAxis) {
		(fromA->getBoundaries()->real_x() <= toB->getBoundaries()->real_x()) ?
			result = new Direction(RIGHT) : result = new Direction(LEFT);
	}
		else {
		(fromA->getBoundaries()->real_y() < toB->getBoundaries()->real_y()) ?
			result = new Direction(UP) : result = new Direction(DOWN);
	}
	return result;
}

bool Physics::isRightFromOther(PhysicalObject * obj, PhysicalObject * objB)
{
	return (obj->getBoundaries()->real_x() > objB->getBoundaries()->real_x()) ?
			true : false;
}

bool Physics::isAboveOther(PhysicalObject * obj, PhysicalObject * objB)
{
	return (obj->getBoundaries()->real_y() > objB->getBoundaries()->real_y()) ?
		true : false;
}

int Physics::getRelativeDistance(PhysicalObject * fromA, PhysicalObject * toB, bool xAxis)
{
	// Determine overlap. Positive value describes an interval size along the axis.
	//					  Negative value describes a distance along the axis.
	int distance;
	int overlap = Physics::getOverlapOnAxis(fromA, toB, xAxis);
	if (overlap < 0) {
		// Determine direction of distance: is B left or right from A?
		Direction* direction = Physics::getRelativeDirection(fromA, toB, xAxis);
		switch (*direction) {
		case Direction::LEFT:
		case Direction::DOWN:
			// B is further from axis origin than A. Return positive distance.
			distance = overlap * -1;
			break;
		case Direction::RIGHT:
		case Direction::UP:
			// B is closer to axis origin than A. Return negative distance.
			distance = overlap;
			break;
		default:
			break;
		}
	}
	return 0;
}

int Physics::getRelativeXDistance(PhysicalObject * fromA, PhysicalObject * toB)
{
	return getRelativeDistance(fromA, toB, true);
}

int Physics::getRelativeYDistance(PhysicalObject * fromA, PhysicalObject * toB)
{
	return getRelativeDistance(fromA, toB, false);
}

// Checks for only movable and/or solid objects.
std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool movable, bool solid)
{
	return checkCollisions(physicalObjects, false, movable, solid);
}

// Checks for all objects.
std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects)
{
	return checkCollisions(physicalObjects, true, false, false);
}

// Checks for all collisions of current level.
// Asserts: this.model has a session with a level that are both initialized.
std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions() const
{
	if(model != nullptr)
	{
		auto physObj = model->getSession()->getLevel()->getPhysicalObjects();
		auto collisions = checkCollisions(physObj);
		delete physObj;
		return collisions;
	} else
	{
		return nullptr;
	}
}

// Checks by comparing the amount of pixels adjacent to the given edge.
std::vector<PhysicalObject*>* Physics::checkAdjacency(PhysicalObject * checkObject, std::vector<PhysicalObject*>* physicalObjects, Direction boundaryEdge, bool checkStrict)
{
	std::vector<PhysicalObject*>* adjacentObjects = new std::vector<PhysicalObject*>();

	// Initialize boundary points for edge comparison. Starting point at bottom right corner)
	//int xLeft = checkObject->getBoundaries()->real_x;
	//int xRight = checkObject->getBoundaries()->real_x + checkObject->getBoundaries()->real_width;
	//int yBottom = checkObject->getBoundaries()->real_y;
	//int yTop = checkObject->getBoundaries()->real_y+ checkObject->getBoundaries()->real_height;

	bool isAdjacent = false;
	static int STRICT_OVERLAP = 3;
	static int ADJACENCY_DIST = 1;
	//int pixelOverlap;	// Pixel overlap of boundaries [x or y direction only]; perpendicular to adjacency-test
	int requiredOverlap = checkStrict ? STRICT_OVERLAP : 1;

	if (physicalObjects)
	{
		for (auto iteratorB = physicalObjects->begin(); iteratorB != physicalObjects->end(); ++iteratorB)
		{
			auto obj = *iteratorB;
			if (!obj->isMovable())	// Only check walls/floors
			{
				isAdjacent = false;
				// Check if any pixels are adjacent
				switch (boundaryEdge) {
					// Boundary corner reference:
					// topleft	(x     | y + height)		upper edge	y + height
					// topright (x + w | y + height)		lower edge	y
					// btmleft  (x     | y)					left  edge	x
					// btmright (x + w | y)					right edge	x + width
				case Direction::DOWN:
					// y-Coordinate of lower edge (from checkObj) 'touches' y-Coordinate of upper edge (from obj)?
					isAdjacent = Physics::getOverlapOnXAxis(checkObject, obj) >= requiredOverlap 
							&& getRelativeYDistance(checkObject, obj) <= ADJACENCY_DIST
							&& isAboveOther(checkObject, obj);
					isAdjacent &= checkStrict ? getOverlapOnXAxis(checkObject, obj) : isAdjacent;
					break;
				case Direction::UP:
					isAdjacent = Physics::getOverlapOnXAxis(checkObject, obj) >= requiredOverlap 
							&& getRelativeYDistance(checkObject, obj) <= ADJACENCY_DIST
							&& !isAboveOther(checkObject, obj);
					break;
				case Direction::LEFT:
					isAdjacent = Physics::getOverlapOnYAxis(checkObject, obj) >= requiredOverlap 
							&& getRelativeXDistance(checkObject, obj) <= ADJACENCY_DIST
							&& isRightFromOther(checkObject, obj);
					break;
				case Direction::RIGHT:
					isAdjacent = Physics::getOverlapOnYAxis(checkObject, obj) >= requiredOverlap 
							&& getRelativeXDistance(checkObject, obj) <= ADJACENCY_DIST
							&& !isRightFromOther(checkObject, obj);
					break;
				default:
					isAdjacent = false;
					break;
				}
				// Store obj in result list, if deemed adjacent.
				if (isAdjacent) adjacentObjects->push_back(obj);
			}
		}
		return nullptr;
	}
}


std::vector<PhysicalObject*>* Physics::checkCollisions(PhysicalObject * objA, std::vector<PhysicalObject*>* physicalObjects)
{
	std::vector<PhysicalObject*>* collisions = new std::vector<PhysicalObject*>();
	for (unsigned int i = 0; i < physicalObjects->size(); i++)
	{
		auto objB = physicalObjects->at(i);
		if ((objA->getBoundaries()->real_x() + objA->getBoundaries()->real_width() - 1) >= objB->getBoundaries()->real_x() && // aRight >= bLeft &&
			(objB->getBoundaries()->real_x() + objB->getBoundaries()->real_width() - 1) >= objA->getBoundaries()->real_x() && // bRight >= aLeft &&
			(objA->getBoundaries()->real_y() + objA->getBoundaries()->real_height() - 1) >= objB->getBoundaries()->real_y() && // aTop >= bBot &&
			(objB->getBoundaries()->real_y() + objB->getBoundaries()->real_height() - 1) >= objA->getBoundaries()->real_y()) // bTop >= aBot
		{
			collisions->push_back(objB);
		}
	}
	return collisions;
}
