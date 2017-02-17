#include "Physics.h"
#include <vector>
#include "PhysicalObject.h"
#include "Level.h"


Physics::Physics()
{
	collisionListener = new std::vector<std::pair<PhysicalObject, PhysicalObject>>;
}

void Physics::setLevel(Level* level)
{
	this->level = level;
}

Level* Physics::getLevel()
{
	return level;
}

std::vector<std::pair<PhysicalObject, PhysicalObject>>* Physics::checkCollisions()
{
	collisionListener->clear();

	// bewegbare Objekte werden nach Kollision abgefragt
	if (level->getPhysicalObjects()) 
	{
		std::vector<PhysicalObject> physicalObjects = *level->getPhysicalObjects();

		for (unsigned int i = 0; i < physicalObjects.size(); i++)
		{
			PhysicalObject objA = physicalObjects.at(i);
			if (objA.isMovable())
			{
				// Schleife über alle die in Frage kommen

				for (std::vector<PhysicalObject>::iterator iteratorB = physicalObjects.begin(); iteratorB != physicalObjects.end(); ++iteratorB)
				{
					PhysicalObject objB = *iteratorB;
					if (objA.getBoundaries()->position.x + (0.5 * objA.getBoundaries()->width) >= objB.getBoundaries()->position.x - (0.5 * objB.getBoundaries()->width) && // aRight >= bLeft &&
						objB.getBoundaries()->position.x + (0.5 * objB.getBoundaries()->width) >= objA.getBoundaries()->position.x - (0.5 * objA.getBoundaries()->width) && // bRight >= aLeft &&
						objA.getBoundaries()->position.y + (0.5 * objA.getBoundaries()->height) >= objB.getBoundaries()->position.y - (0.5 * objB.getBoundaries()->height) && // aTop >= bBot &&
						objB.getBoundaries()->position.y + (0.5 * objB.getBoundaries()->height) >= objA.getBoundaries()->position.y - (0.5 * objA.getBoundaries()->height)) // aBot >= bTop
					{
						collisionListener->push_back(std::make_pair(objA, objB));
					}
				}
			}
		}
		return collisionListener;
	} 
	else
	{
		return nullptr;
	}
}



