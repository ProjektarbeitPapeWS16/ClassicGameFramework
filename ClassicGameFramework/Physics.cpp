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

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects, bool movable, bool solid)
{
	return checkCollisions(physicalObjects, false, movable, solid);
}

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects)
{
	return checkCollisions(physicalObjects, true, false, false);
}

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions() const
{
	return model != nullptr ? checkCollisions(model->getSession()->getLevel()->getPhysicalObjects()) : nullptr;
}

std::vector<PhysicalObject*>* Physics::checkCollisions(PhysicalObject * objA, std::vector<PhysicalObject*>* physicalObjects)
{
	std::vector<PhysicalObject*>* collisions = new std::vector<PhysicalObject*>();
	for (unsigned int i = 0; physicalObjects->size(); i++)
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
