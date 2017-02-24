#include "MovableEntity.h"
#include "Position.h"
#include "LadderEntity.h"
#include "WallEntity.h"
#include "HoleEntity.h"
#include "FloorEntity.h"


PhysicalObject* MovableEntity::canMoveUp()
{
	// TODO: optimize
	PhysicalObject* ret = nullptr;
	auto posRight = Position(getBoundaries()->real_x() + (getBoundaries()->real_width() / 2), getBoundaries()->real_y() + 2 * getConfig()->getRasterHeight());
	auto posLeft = Position(posRight);
	posRight.x -= 1;

	auto entitiesLeft = getModel()->getPhysics()->backgroundOnPosition(posLeft);
	auto entitiesRight = getModel()->getPhysics()->backgroundOnPosition(posRight);

	bool ladderFound = false;
	for (auto i = 0; i < entitiesLeft->size(); i++)
	{
		LadderEntity* ladder = dynamic_cast<LadderEntity*>(entitiesLeft->at(i));
		if (ladder)
		{
			ladderFound = true;

			if (ladder->getPosX() <= posRight.x || ladder->getPosX() + ladder->getBoundaries()->width - 1 >= posLeft.x)
			{
				//setPosition(ladder->getPosX() - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
				ret = ladder;
			}
			break;
		}
	}

	if (!ladderFound)
	{
		for (auto i = 0; i < entitiesRight->size(); i++)
		{
			LadderEntity* ladder = dynamic_cast<LadderEntity*>(entitiesRight->at(i));
			if (ladder)
			{
				if (ladder->getPosX() <= posRight.x || ladder->getPosX() + ladder->getBoundaries()->width - 1 >= posLeft.x)
				{
					//setPosition(ladder->getPosX() - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
					ret = ladder;
				}
				break;
			}
		}
	}

	delete entitiesLeft;
	delete entitiesRight;
	return ret;
}

PhysicalObject* MovableEntity::canMoveDown()
{
	// TODO: optimize
	PhysicalObject* ret = nullptr;
	auto posRight = Position(getBoundaries()->real_x() + (getBoundaries()->real_width() / 2), getBoundaries()->position.y - 1);
	auto posLeft = Position(posRight);
	posRight.x -= 1;

	auto entitiesLeft = getModel()->getPhysics()->backgroundOnPosition(posLeft);
	auto entitiesRight = getModel()->getPhysics()->backgroundOnPosition(posRight);

	bool ladderFound = false;
	for (auto i = 0; i < entitiesLeft->size(); i++)
	{
		LadderEntity* ladder = dynamic_cast<LadderEntity*>(entitiesLeft->at(i));
		if (ladder)
		{
			ladderFound = true;

			if (ladder->getPosX() <= posRight.x || ladder->getPosX() + ladder->getBoundaries()->width - 1 >= posLeft.x)
			{
				//setPosition(ladder->getPosX() - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
				ret = ladder;
			}
			break;
		}
	}

	if (!ladderFound)
	{
		for (auto i = 0; i < entitiesRight->size(); i++)
		{
			LadderEntity* ladder = dynamic_cast<LadderEntity*>(entitiesRight->at(i));
			if (ladder)
			{
				if (ladder->getPosX() <= posRight.x || ladder->getPosX() + ladder->getBoundaries()->width - 1 >= posLeft.x)
				{
					//setPosition(ladder->getPosX() - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
					ret = ladder;
				}
				break;
			}
		}
	}

	delete entitiesLeft;
	delete entitiesRight;
	return ret;
}

PhysicalObject* MovableEntity::canMoveLeft()
{
	PhysicalObject* ret = nullptr;
	Position upperPos = Position(getBoundaries()->position.x - 1, getBoundaries()->position.y - 1);
	Position lowerPos = Position(upperPos);
	lowerPos.y -= getConfig()->getRasterHeight() / 2;

	auto upperEntities = getModel()->getPhysics()->backgroundOnPosition(upperPos);

	LadderEntity* ladder = nullptr;
	WallEntity* upperWall = nullptr;
	HoleEntity* hole = nullptr;
	FloorEntity* upperFloor = nullptr;
	for (auto i = 0; i < upperEntities->size(); i++)
	{
		if (!ladder) ladder = dynamic_cast<LadderEntity*>(upperEntities->at(i));
		if (!upperWall) upperWall = dynamic_cast<WallEntity*>(upperEntities->at(i));
		if (!hole) hole = dynamic_cast<HoleEntity*>(upperEntities->at(i));
		if (!upperFloor) upperFloor = dynamic_cast<FloorEntity*>(upperEntities->at(i));

		if (ladder || upperFloor || hole) break;
	}
	delete upperEntities;

	WallEntity* lowerWall = nullptr;
	FloorEntity* lowerFloor = nullptr;
	if (!ladder && !upperFloor)
	{
		auto lowerEntities = getModel()->getPhysics()->backgroundOnPosition(lowerPos);

		for (auto i = 0; i < lowerEntities->size(); i++)
		{
			if (!lowerWall) lowerWall = dynamic_cast<WallEntity*>(lowerEntities->at(i));
			if (!lowerFloor) lowerFloor = dynamic_cast<FloorEntity*>(lowerEntities->at(i));

			if (lowerFloor || lowerWall) break;
		}
		delete lowerEntities;
	}

	if (hole) return hole;
	else if (upperWall) return upperWall;

	if (lowerWall) return lowerWall;
	if (ladder) return ladder;
	if (upperFloor) return upperFloor;
	if (lowerFloor) return lowerFloor;

	return nullptr;
}

PhysicalObject* MovableEntity::canMoveRight()
{
	PhysicalObject* ret = nullptr;
	Position upperPos = Position(getBoundaries()->position.x + getBoundaries()->width, getBoundaries()->position.y - 1);
	Position lowerPos = Position(upperPos);
	lowerPos.y -= getConfig()->getRasterHeight() / 2;

	auto upperEntities = getModel()->getPhysics()->backgroundOnPosition(upperPos);

	LadderEntity* ladder = nullptr;
	WallEntity* upperWall = nullptr;
	HoleEntity* hole = nullptr;
	FloorEntity* upperFloor = nullptr;
	for (auto i = 0; i < upperEntities->size(); i++)
	{
		if (!ladder) ladder = dynamic_cast<LadderEntity*>(upperEntities->at(i));
		if (!upperWall) upperWall = dynamic_cast<WallEntity*>(upperEntities->at(i));
		if (!hole) hole = dynamic_cast<HoleEntity*>(upperEntities->at(i));
		if (!upperFloor) upperFloor = dynamic_cast<FloorEntity*>(upperEntities->at(i));

		if (ladder || upperFloor || hole) break;
	}
	delete upperEntities;

	WallEntity* lowerWall = nullptr;
	FloorEntity* lowerFloor = nullptr;
	if (!ladder && !upperFloor)
	{
		auto lowerEntities = getModel()->getPhysics()->backgroundOnPosition(lowerPos);

		for (auto i = 0; i < lowerEntities->size(); i++)
		{
			if (!lowerWall) lowerWall = dynamic_cast<WallEntity*>(lowerEntities->at(i));
			if (!lowerFloor) lowerFloor = dynamic_cast<FloorEntity*>(lowerEntities->at(i));

			if (lowerFloor || lowerWall) break;
		}
		delete lowerEntities;
	}

	if (hole) return hole;
	else if (upperWall) return upperWall;

	if (lowerWall) return lowerWall;
	if (ladder) return ladder;
	if (upperFloor) return upperFloor;
	if (lowerFloor) return lowerFloor;

	return nullptr;
}

HoleEntity::HoleState MovableEntity::canFall(Position pos)
{
	auto entities = getModel()->getPhysics()->backgroundOnPosition(pos);

	HoleEntity* hole = nullptr;
	for (int i = 0; i < entities->size(); i++)
	{
		hole = dynamic_cast<HoleEntity*>(entities->at(i));
		break;
	}

	delete entities;

	if (hole)
	{
		return hole->getStage();
	}

	return HoleEntity::STAGE0;
}

HoleEntity::HoleState MovableEntity::canFall()
{
	return canFall(Position(getBoundaries()->position.x + getBoundaries()->width / 2, getBoundaries()->position.y - 1));
}

MovableEntity::MovableEntity(Image** image, int movement_speed, bool solid, Boundaries* boundaries, bool movable, int animation_speed): Entity(image, movement_speed, solid, boundaries, movable, animation_speed)
{
}
