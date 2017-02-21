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
						if ( (objA->getBoundaries()->position.x + objA->getBoundaries()->width-1) >= objB->getBoundaries()->position.x && // aRight >= bLeft &&
							 (objB->getBoundaries()->position.x + objB->getBoundaries()->width-1) >= objA->getBoundaries()->position.x && // bRight >= aLeft &&
							 (objA->getBoundaries()->position.y + objA->getBoundaries()->height-1) >= objB->getBoundaries()->position.y && // aTop >= bBot &&
							 (objB->getBoundaries()->position.y + objB->getBoundaries()->height-1) >= objA->getBoundaries()->position.y ) // bTop >= aBot
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
