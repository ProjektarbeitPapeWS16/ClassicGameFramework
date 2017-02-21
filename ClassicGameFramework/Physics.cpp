#include "Physics.h"
#include <vector>
#include "PhysicalObject.h"
#include "Level.h"


Physics::Physics():
	collisionListeners(new std::vector<std::pair<PhysicalObject*, PhysicalObject*>>())
{
}

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::checkCollisions(std::vector<PhysicalObject*>* physicalObjects) const
{
	collisionListeners->clear();

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
					if (objA != objB)
					{
						if (objA->getBoundaries()->position.x + (0.5 * objA->getBoundaries()->width) >= objB->getBoundaries()->position.x - (0.5 * objB->getBoundaries()->width) && // aRight >= bLeft &&
							objB->getBoundaries()->position.x + (0.5 * objB->getBoundaries()->width) >= objA->getBoundaries()->position.x - (0.5 * objA->getBoundaries()->width) && // bRight >= aLeft &&
							objA->getBoundaries()->position.y + (0.5 * objA->getBoundaries()->height) >= objB->getBoundaries()->position.y - (0.5 * objB->getBoundaries()->height) && // aTop >= bBot &&
							objB->getBoundaries()->position.y + (0.5 * objB->getBoundaries()->height) >= objA->getBoundaries()->position.y - (0.5 * objA->getBoundaries()->height)) // aBot >= bTop
						{
							collisionListeners->push_back(std::make_pair(objA, objB));
						}
					}
				}
			}
		}
		return collisionListeners;
	} 
	else
	{
		return nullptr;
	}
}

/*
void Physics::addCollisionListener(PhysicalObject* phys1, PhysicalObject* phys2)
{
	collisionListeners->push_back(std::make_pair(phys1, phys2));
}

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Physics::getCollisionListeners()
{
}

void Physics::clearCollisionListeners()
{
}*/
