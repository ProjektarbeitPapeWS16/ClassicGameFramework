#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Image.h"
#include "GameConfig.h"
#include "EngineModel.h"
#include "Session.h"
#include "Level.h"
#include "Stage.h"
#include "LadderEntity.h"
#include "WallEntity.h"
#include "HoleEntity.h"
#include "FloorEntity.h"


PlayerEntity::PlayerEntity(SpacePanicModel* model, Position* position):
	MovableEntity(
		new Image*[0],
		10,
		false,
		new Boundaries(
			position->x * model->getConfig()->getRasterWidth(),
			position->y * model->getConfig()->getRasterHeight(),
			model->getConfig()->getRasterWidth() * 2,
			model->getConfig()->getRasterHeight() * 2,
				model->getConfig()->applyFactor(4),
					0, model->getConfig()->applyFactor(4), 0
		),
		true,
		30
	),
	config(model->getConfig()),
	moveRight1(new Image("textures/player_run1_right.bmp", this, 200, 80, 0)),
	moveRight2(new Image("textures/player_run2_right.bmp", this, 200, 80, 0)),
	moveLeft1(new Image("textures/player_run1_left.bmp", this, 200, 80, 0)),
	moveLeft2(new Image("textures/player_run2_left.bmp", this, 200, 80, 0)),
	climb1(new Image("textures/player_climb1.bmp", this, 200, 80, 0)),
	climb2(new Image("textures/player_climb2.bmp", this, 200, 80, 0)),
	deadLeft(new Image("textures/player_dead_left.bmp", this, 200, 80, 0)),
	deadRight(new Image("textures/player_dead_right.bmp", this, 200, 80, 0)),
	deadLadder(new Image("textures/player_dead_ladder.bmp", this, 200, 80, 0)),
	digLeft1(new Image("textures/player_dig1_left.bmp", this, 200, 80, 0)),
	digLeft2(new Image("textures/player_dig2_left.bmp", this, 200, 80, 0)),
	digRight1(new Image("textures/player_dig1_right.bmp", this, 200, 80, 0)),
	digRight2(new Image("textures/player_dig2_right.bmp", this, 200, 80, 0)),
	model(model),
	original_boundaries(new Boundaries(boundaries->position.x, boundaries->position.y,
	                                   boundaries->width, boundaries->height,
	                                   boundaries->off_left, boundaries->off_bottom,
	                                   boundaries->off_right, boundaries->off_top))

{
}

void PlayerEntity::request(Request request)
{
	lastRequest = request;
}

int PlayerEntity::schrittweite() const
{
	return config->getRasterWidth() / 2;
}


bool PlayerEntity::canMove()
{


	PhysicalObject* physObj = nullptr;
	switch (lastRequest)
	{
	case DIG:
		return true;
	case UNDIG:
		return true;
	case MOVE_RIGHT:
		physObj = canMoveRight();
		if (physObj)
		{
			HoleEntity* hole = dynamic_cast<HoleEntity*>(physObj);
			if (hole && hole->getStage() != HoleEntity::STAGE3)
			{
				return false;
			}

			//y-axis correction
			setPosition(getPosX(), physObj->getBoundaries()->position.y + physObj->getBoundaries()->height);
		}
		return physObj;
	case MOVE_LEFT:
		physObj = canMoveLeft();
		if (physObj)
		{
			HoleEntity* hole = dynamic_cast<HoleEntity*>(physObj);
			if (hole && hole->getStage() != HoleEntity::STAGE3)
			{
				return false;
			}

			//y-axis correction
			setPosition(getPosX(), physObj->getBoundaries()->position.y + physObj->getBoundaries()->height);
		}
		return physObj;
	case MOVE_UP:
		physObj = canMoveUp();
		if (physObj)
		{
			//x-axis correction
			setPosition(physObj->getBoundaries()->position.x - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
		}
		return physObj;
	case MOVE_DOWN:
		physObj = canMoveDown();
		if (physObj)
		{
			//x-axis correction
			setPosition(physObj->getBoundaries()->position.x - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
		}
		return physObj;
	default: return false;
	}
}

bool PlayerEntity::dig() const
{
	auto ret = false;
	std::vector<PhysicalObject*>* entities;

	switch (state)
	{
	case MOVE_RIGHT_1:
	case MOVE_RIGHT_2:
	case DIG_RIGHT_1:
	case DIG_RIGHT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x + 2 * config->getRasterWidth(), boundaries->position.y - 1));
		break;

	case MOVE_LEFT_1:
	case MOVE_LEFT_2:
	case DIG_LEFT_1:
	case DIG_LEFT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x - config->getRasterWidth(), boundaries->position.y - 1));
		break;

	default:
		return false;
	}

	bool found_hole = false;
	for (auto i = 0; i < entities->size(); i++)
	{
		HoleEntity* hole = dynamic_cast<HoleEntity*>(entities->at(i));
		if (hole)
		{
			found_hole = true;
			ret = hole->grow();
			break;
		}
	}

	if (!found_hole)
	{
		for (auto i = 0; i < entities->size(); i++)
		{
			WallEntity* wall = dynamic_cast<WallEntity*>(entities->at(i));
			if (wall && wall->isMiddleWall())
			{
				ret = wall->makeHole();
				break;
			}
		}
	}


	delete entities;
	return ret;
}

bool PlayerEntity::canDig() const
{
	auto ret = false;
	std::vector<PhysicalObject*>* entities;

	switch (state)
	{
	case MOVE_RIGHT_1:
	case MOVE_RIGHT_2:
	case DIG_RIGHT_1:
	case DIG_RIGHT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x + 2 * config->getRasterWidth(), boundaries->position.y - 1));
		break;

	case MOVE_LEFT_1:
	case MOVE_LEFT_2:
	case DIG_LEFT_1:
	case DIG_LEFT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x - config->getRasterWidth(), boundaries->position.y - 1));
		break;

	default:
		return false;
	}

	bool found_hole = false;
	for (auto i = 0; i < entities->size(); i++)
	{
		HoleEntity* hole = dynamic_cast<HoleEntity*>(entities->at(i));
		if (hole)
		{
			found_hole = true;
			ret = hole->canGrow();
			break;
		}
	}

	if (!found_hole)
	{
		for (auto i = 0; i < entities->size(); i++)
		{
			WallEntity* wall = dynamic_cast<WallEntity*>(entities->at(i));
			if (wall && wall->isMiddleWall())
			{
				ret = true;
				break;
			}
		}
	}


	delete entities;
	return ret;
}

bool PlayerEntity::canUnDig() const
{
	auto ret = false;
	std::vector<PhysicalObject*>* entities;

	switch (state)
	{
	case MOVE_RIGHT_1:
	case MOVE_RIGHT_2:
	case DIG_RIGHT_1:
	case DIG_RIGHT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x + 2 * config->getRasterWidth(), boundaries->position.y - 1));
		break;

	case MOVE_LEFT_1:
	case MOVE_LEFT_2:
	case DIG_LEFT_1:
	case DIG_LEFT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x - config->getRasterWidth(), boundaries->position.y - 1));
		break;

	default:
		return false;
	}

	bool found_hole = false;
	for (auto i = 0; i < entities->size(); i++)
	{
		HoleEntity* hole = dynamic_cast<HoleEntity*>(entities->at(i));
		if (hole)
		{
			found_hole = true;
			ret = hole->canShrink();
			break;
		}
	}

	delete entities;
	return ret;
}

bool PlayerEntity::unDig() const
{
	auto ret = false;
	std::vector<PhysicalObject*>* entities;

	switch (state)
	{
	case MOVE_RIGHT_1:
	case MOVE_RIGHT_2:
	case DIG_RIGHT_1:
	case DIG_RIGHT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x + 2 * config->getRasterWidth(), boundaries->position.y - 1));
		break;

	case MOVE_LEFT_1:
	case MOVE_LEFT_2:
	case DIG_LEFT_1:
	case DIG_LEFT_2:
		entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x - config->getRasterWidth(), boundaries->position.y - 1));
		break;

	default:
		return false;
	}

	bool found_hole = false;
	for (auto i = 0; i < entities->size(); i++)
	{
		HoleEntity* hole = dynamic_cast<HoleEntity*>(entities->at(i));
		if (hole)
		{
			found_hole = true;
			ret = hole->shrink();
			if (hole->getStage() == HoleEntity::HoleState::STAGE0)
			{
				static_cast<Stage*>(model->getLevel())->removeHole(hole);
			}
			break;
		}
	}

	delete entities;
	return ret;
}

//int PlayerEntity::fallingUntil = 0;
void PlayerEntity::execute()
{
	if(state == FALLING_RIGHT || state == FALLING_LEFT || tryFall())
	{
		setPosY(getPosY() - schrittweite());
		if(getPosY() <= fallingUntil)
		{
			if(state == FALLING_LEFT)
			{
				
					state = MOVE_LEFT_1;
				
			} else
			{
				
					state = MOVE_RIGHT_1;
				
			}
			
		}
		return;
	} 

	if (!canMove())
	{
		lastRequest = NONE;
		return;
	}
	int row = this->getPosY() / config->getRasterHeight();
	int column = (static_cast<double>(this->getPosX()) + (0.5 * config->getRasterWidth())) / config->getRasterWidth();


	switch (lastRequest)
	{
	case MOVE_RIGHT:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case MOVE_RIGHT_1:
			this->setPosX(this->getPosX() + schrittweite());
			//this->setPosY(row * config->getRasterHeight());
			state = MOVE_RIGHT_2;
			break;
		case MOVE_RIGHT_2: default:
			this->setPosX(this->getPosX() + schrittweite());
			//this->setPosY(row * config->getRasterHeight());
			state = MOVE_RIGHT_1;
			break;
		}

		break;
	case MOVE_LEFT:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case MOVE_LEFT_1:
			this->setPosX(this->getPosX() - schrittweite());
			//this->setPosY(row * config->getRasterHeight());
			state = MOVE_LEFT_2;
			break;
		case MOVE_LEFT_2: default:
			this->setPosX(this->getPosX() - schrittweite());
			//this->setPosY(row * config->getRasterHeight());
			state = MOVE_LEFT_1;
			break;
		}
		break;
	case MOVE_UP:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case CLIMB_1:
			//this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_2;
			break;
		case CLIMB_2: default:
			//this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_1;
			break;
		}
		break;
	case MOVE_DOWN:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case CLIMB_1:
			//this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_2;
			break;
		case CLIMB_2: default:
			//this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_1;
			break;
		}
		break;
	case DIG:
		if (cycle_counter++ % 3 == 0)
		{
			switch (state)
			{
			case DEAD_LADDER:
			case DEAD_LEFT:
			case DEAD_RIGHT: break;

			case DIG_LEFT_1:
				if (dig())
				{
					state = DIG_LEFT_2;
				}
				break;


			case DIG_LEFT_2:
			case MOVE_LEFT_1:
			case MOVE_LEFT_2:
				if (canDig())
				{
					state = DIG_LEFT_1;
				}
				break;

			case DIG_RIGHT_1:
				if (dig())
				{
					state = DIG_RIGHT_2;
				}
				break;

			case DIG_RIGHT_2:
			case MOVE_RIGHT_1:
			case MOVE_RIGHT_2: default:
				if (canDig())
				{
					state = DIG_RIGHT_1;
				}
				break;
			}
		}
		break;
	case UNDIG:
		if (cycle_counter++ % 3 == 0)
		{
			switch (state)
			{
			case DEAD_LADDER:
			case DEAD_LEFT:
			case DEAD_RIGHT: break;

			case DIG_LEFT_1:
			case MOVE_LEFT_1:
			case MOVE_LEFT_2:
				if (canUnDig())
				{
					state = DIG_LEFT_2;
				}
				break;


			case DIG_LEFT_2:
				if (unDig())
				{
					state = DIG_LEFT_1;
				}
				break;

			case DIG_RIGHT_1:
			case MOVE_RIGHT_1:
			case MOVE_RIGHT_2:
				if (canUnDig())
				{
					state = DIG_RIGHT_2;
				}
				break;

			case DIG_RIGHT_2:
			default:
				if (unDig())
				{
					state = DIG_RIGHT_1;
				}
				break;
			}
		}
		break;
	default: break;
	}
	lastRequest = NONE;
}

bool PlayerEntity::tryFall()
{
	auto entities = model->getPhysics()->backgroundOnPosition(Position(boundaries->position.x + boundaries->width / 2, boundaries->position.y - 1));
	HoleEntity* hole = nullptr;
	for(int i = 0; i < entities->size(); i++)
	{
		hole = dynamic_cast<HoleEntity*>(entities->at(i));
		if(hole)
		{
			setPosX(hole->getPosX() + config->getRasterWidth() / 2);
			break;
		}
	}

	if(hole && hole->getStage() == HoleEntity::STAGE3)
	{
		switch(state)
		{
		case MOVE_RIGHT_1: ;
		case MOVE_RIGHT_2: ;
		case FALLING_RIGHT: 
			state = PlayerState::FALLING_RIGHT;
			break;
		default: 
			state = PlayerState::FALLING_LEFT;
			break;
		}
		
		fallingUntil = hole->getPosY() - 3 * config->getRasterHeight();
	}

	return state == FALLING_RIGHT || state == FALLING_LEFT;
}

Image* PlayerEntity::getImage()
{
	switch (state)
	{
	case FALLING_RIGHT:
	case MOVE_RIGHT_1: return moveRight1;
	case MOVE_RIGHT_2: return moveRight2;
	case FALLING_LEFT:
	case MOVE_LEFT_1: return moveLeft1;
	case MOVE_LEFT_2: return moveLeft2;
	case CLIMB_1: return climb1;
	case CLIMB_2: return climb2;
	case DIG_LEFT_1: return digLeft1;
	case DIG_LEFT_2: return digLeft2;
	case DIG_RIGHT_1: return digRight1;
	case DIG_RIGHT_2: return digRight2;
	case DEAD_LEFT: return deadLeft;
	case DEAD_RIGHT: return deadRight;
	case DEAD_LADDER: default: return deadLadder;
	}
}

bool PlayerEntity::isDead() const
{
	return state == DEAD_LEFT || state == DEAD_RIGHT || state == DEAD_LADDER;
}

void PlayerEntity::reset()
{
	this->state = MOVE_RIGHT_1;
	this->lastRequest = NONE;

	this->boundaries->position.x = original_boundaries->position.x;
	this->boundaries->position.y = original_boundaries->position.y;
	this->boundaries->width = original_boundaries->width;
	this->boundaries->height = original_boundaries->height;
	this->boundaries->off_left = original_boundaries->off_left;
	this->boundaries->off_right = original_boundaries->off_right;
	this->boundaries->off_top = original_boundaries->off_top;
	this->boundaries->off_bottom = original_boundaries->off_bottom;
}

SpacePanicModel* PlayerEntity::getModel() const
{
	return model;
}

Boundaries* PlayerEntity::getBoundaries()
{
	return boundaries;
}

GameConfig* PlayerEntity::getConfig() const
{
	return config;
}

void PlayerEntity::setPosition(int xPos, int yPos)
{
	boundaries->position.x = xPos;
	boundaries->position.y = yPos;
}

PlayerEntity::~PlayerEntity()
{
	delete moveRight1;
	delete moveRight2;
	delete moveLeft1;
	delete moveLeft2;
	delete climb1;
	delete climb2;
	delete deadLeft;
	delete deadRight;
	delete deadLadder;
	delete digLeft1;
	delete digLeft2;
	delete digRight1;
	delete digRight2;
}

void PlayerEntity::collideWith(PhysicalObject* physicalObject)
{
	if (isDead())
	{
		return;
	}

	EnemyEntity* enemy;
	if (((enemy = dynamic_cast<EnemyEntity*>(physicalObject->getEntity()))) && enemy->getState() != EnemyEntity::DEAD)
	{
		if (enemy->getPosX() < getPosX())
		{
			state = DEAD_RIGHT;
		}
		else if (enemy->getPosX() > getPosX())
		{
			state = DEAD_LEFT;
		}
		else
		{
			state = DEAD_LADDER;
		}

		deadSince = model->getSession()->getPassedTime();
	}
}

unsigned long long PlayerEntity::getDeadSince() const
{
	return deadSince;
}
