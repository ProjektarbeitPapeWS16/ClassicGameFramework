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

// Checks collisions for a given vector of physical objects; selection for check can be filtered.
// Details: Checks, if any boundaries of movable POs intersect with other POs.
// @all: If true, checks collisions with all types of other objects. Set false if you want to check for certain attributes only.
// @moveable: If true [&&all=false], checks only collisions with other movable objects
// @solid: If true [&&all=false], checks only collisions with solid objects
std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool all, bool movable, bool solid)
{
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* collisions = new std::vector<std::pair<PhysicalObject*, PhysicalObject*>>();

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
	return model != nullptr ? checkCollisions(model->getSession()->getLevel()->getPhysicalObjects()) : nullptr;
}
