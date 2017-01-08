#include "Physics.h"
#include <vector>
#include "PhysicalObject.h"
#include "Level.h"


Physics::Physics()
{
}

void Physics::checkCollisions()
{
	// bewegbare Objekte werden nach Kollision abgefragt
	std::vector<PhysicalObject> * physicalObjects = level->getPhysicalObjects();
	
	// ginge wohl auch: for (auto i = std::begin(*physicalObjects); i != std::end(*physicalObjects); ++i)
	//for (auto iteratorA = std::begin(*physicalObjects); iteratorA != std::end(*physicalObjects); ++iteratorA)

	std::vector<PhysicalObject>::iterator v = physicalObjects->begin();
	while (v != physicalObjects->end())
	{
		PhysicalObject objA = *v;
		if (objA.isMovable()) 
		{
		// Schleife über alle die in Frage kommen

			for (std::vector<PhysicalObject>::iterator iteratorB = physicalObjects->begin(); iteratorB != physicalObjects->end(); ++iteratorB)
			{
				PhysicalObject objB = *iteratorB;
				if (objA.getBoundaries()->position.x + (0.5 * objA.getBoundaries()->width) >= objB.getBoundaries()->position.x - (0.5 * objB.getBoundaries()->width) &&		// aRight >= bLeft &&
					objB.getBoundaries()->position.x + (0.5 * objB.getBoundaries()->width) >= objA.getBoundaries()->position.x - (0.5 * objA.getBoundaries()->width) &&		// bRight >= aLeft &&
					objA.getBoundaries()->position.y + (0.5 * objA.getBoundaries()->height) >= objB.getBoundaries()->position.y - (0.5 * objB.getBoundaries()->height) &&	// aTop >= bBot &&
					objB.getBoundaries()->position.y + (0.5 * objB.getBoundaries()->height) >= objA.getBoundaries()->position.y - (0.5 * objA.getBoundaries()->height))		// aBot >= bTop
				{
					try
					{
						std::function<void(PhysicalObject*)> * foo = collisionListener->at(&objB);
						(*foo)(&objA);
					}
					catch (int e) 
					{

					}
					try
					{
						std::function<void(PhysicalObject*)> * foo = collisionListener->at(&objA);
						(*foo)(&objB);
					}
					catch (int e)
					{

}
				}
			}
		}
	}
}

std::map<PhysicalObject*, std::function<void(PhysicalObject*)>*> *Physics::getCollisionListener()
{
	return collisionListener;
}

Level * Physics::getLevel()
{
	return level;
}

void Physics::setLevel(Level * level)
{
	this->level = level;
}

