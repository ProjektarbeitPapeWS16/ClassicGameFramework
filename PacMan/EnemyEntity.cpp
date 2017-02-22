#include "EnemyEntity.h"
#include "Boundaries.h"
#include "Image.h"
#include "EngineView.h"
#include "PacManView.h"
#include "Config.h"
#include "PlayerEntity.h"
#include "Physics.h"
#include "Level.h"
#include "WallEntity.h"

#define AMP 3

EnemyEntity::EnemyEntity() 
	: Entity(nullptr, 3*3, false, new Boundaries(200, 200, 14*3, 14*3), true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	deadUp = new Image("textures/Ghosts/deadGhostUp.bmp", this, 0, 0, 0);
	deadDown = new Image("textures/Ghosts/deadGhostDown.bmp", this, 0, 0, 0);
	deadRight = new Image("textures/Ghosts/deadGhostRight.bmp", this, 0, 0, 0);
	deadLeft = new Image("textures/Ghosts/deadGhostLeft.bmp", this, 0, 0, 0);
}

EnemyEntity::EnemyEntity(Boundaries * boundaries) : Entity(nullptr, 5 * 3, false, boundaries, true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	deadUp = new Image("textures/Ghosts/deadGhostUp.bmp", this, 0, 0, 0);
	deadDown = new Image("textures/Ghosts/deadGhostDown.bmp", this, 0, 0, 0);
	deadRight = new Image("textures/Ghosts/deadGhostRight.bmp", this, 0, 0, 0);
	deadLeft = new Image("textures/Ghosts/deadGhostLeft.bmp", this, 0, 0, 0);
}

void EnemyEntity::setTextures(char* moveUp1, char* moveUp2, char* moveDown1, char* moveDown2,
	char* moveRight1, char* moveRight2, char* moveLeft1, char* moveLeft2,
	char* energized1, char* energized2)
{
	this->moveUp1 = new Image(moveUp1, this, 0, 0, 0);
	this->moveUp2 = new Image(moveUp2, this, 0, 0, 0);
	this->moveDown1 = new Image(moveDown1, this, 0, 0, 0);
	this->moveDown2 = new Image(moveDown2, this, 0, 0, 0);
	this->moveRight1 = new Image(moveRight1, this, 0, 0, 0);
	this->moveRight2 = new Image(moveRight2, this, 0, 0, 0);
	this->moveLeft1 = new Image(moveLeft1, this, 0, 0, 0);
	this->moveLeft2 = new Image(moveLeft2, this, 0, 0, 0);
	this->energized1 = new Image(energized1, this, 0, 0, 0);
	this->energized2 = new Image(energized2, this, 0, 0, 0);
}

void EnemyEntity::request(Request request)
{
	lastRequest = request;
}

void EnemyEntity::setState(GhostState state)
{
	this->state = state;
}

void EnemyEntity::specialRequest(SpecialState request)
{
	if (request == ENERGIZED1)
	{
		energizerTimer = 0;
		energizerTimer2 = 0;
	}
	specialState = request;
}

void EnemyEntity::execute()
{
	findDirection();
	move(direction);

	/*
	switch (lastRequest)
	{
	case MOVE_RIGHT:
		switch (state)
		{
		case MOVE_RIGHT_1:
			this->setPosX(this->getPosX() + movementSpeed);
			state = MOVE_RIGHT_2;
			break;
		case MOVE_RIGHT_2:
			this->setPosX(this->getPosX() + movementSpeed);
			state = MOVE_RIGHT_1;
			break;
		default:
			this->setPosX(this->getPosX() + movementSpeed);
			state = MOVE_RIGHT_1;
			break;
		}

		break;
	case MOVE_LEFT:
		switch (state)
		{
		case MOVE_LEFT_1:
			this->setPosX(this->getPosX() - movementSpeed);
			state = MOVE_LEFT_2;
			break;
		case MOVE_LEFT_2:
			this->setPosX(this->getPosX() - movementSpeed);
			state = MOVE_LEFT_1;
			break;
		default:
			this->setPosX(this->getPosX() - movementSpeed);
			state = MOVE_LEFT_1;
			break;
		}
		break;
	case MOVE_UP:
		switch (state)
		{
		case MOVE_UP_1:
			this->setPosY(this->getPosY() + movementSpeed);
			state = MOVE_UP_2;
			break;
		case MOVE_UP_2:
			this->setPosY(this->getPosY() + movementSpeed);
			state = MOVE_UP_1;
			break;
		default:
			this->setPosY(this->getPosY() + movementSpeed);
			state = MOVE_UP_1;
			break;
		}
		break;
	case MOVE_DOWN:
		switch (state)
		{
		case MOVE_DOWN_1:
			this->setPosY(this->getPosY() - movementSpeed);
			state = MOVE_DOWN_2;
			break;
		case MOVE_DOWN_2:
			this->setPosY(this->getPosY() - movementSpeed);
			state = MOVE_DOWN_1;
			break;
		default:
			this->setPosY(this->getPosY() - movementSpeed);
			state = MOVE_DOWN_1;
			break;
		}
		break;
		
	default: break;
	}
	lastRequest = NONE;
	*/
	if (specialState == ENERGIZED1 || specialState == ENERGIZED2)
	{
		if (energizerTimer == 0) 
		{
			energizerTimer = Config::currentTimeMillis();
		}
		if ((Config::currentTimeMillis() - energizerTimer) > 10000) // 10 Sekunden um
		{
			if (energizerTimer2 == 0)
			{
				specialState = ENERGIZED1;
				energizerTimer2 = Config::currentTimeMillis();
			}
			if ((Config::currentTimeMillis() - energizerTimer2) > 500)
			{
				if (specialState == ENERGIZED1)
				{
					specialState = ENERGIZED2;
				}
				else if (specialState == ENERGIZED2)
				{
					specialState = ENERGIZED1;
				}
			}
			if ((Config::currentTimeMillis() - energizerTimer) > 13000)
			{
				specialState = ALIVE;
			}
		}
	}
}

void EnemyEntity::stepBack()
{
	switch (state)
	{
	case MOVE_RIGHT_1:
	case MOVE_RIGHT_2: this->setPosX(this->getPosX() - movementSpeed); break;
	case MOVE_LEFT_1:
	case MOVE_LEFT_2: this->setPosX(this->getPosX() + movementSpeed); break;
	case MOVE_UP_1:
	case MOVE_UP_2: this->setPosY(this->getPosY() - movementSpeed); break;
	case MOVE_DOWN_1:
	case MOVE_DOWN_2: this->setPosY(this->getPosY() + movementSpeed); break;
	default: break;
	}
}

Image* EnemyEntity::getImage()
{
	switch (specialState)
	{
	case ALIVE: break;
	case DEAD: 
		switch (state)
		{
		case MOVE_NONE:
		case MOVE_RIGHT_1:
		case MOVE_RIGHT_2: return deadRight;
		case MOVE_LEFT_1:
		case MOVE_LEFT_2: return deadLeft;
		case MOVE_UP_1:
		case MOVE_UP_2: return deadUp;
		case MOVE_DOWN_1:
		case MOVE_DOWN_2: return deadDown;
		default: break;
		}
		break;
	case ENERGIZED1: return energized1;
	case ENERGIZED2: return energized2;
	}

	switch (state)
	{
	case MOVE_RIGHT_1: return moveRight1;
	case MOVE_RIGHT_2: return moveRight2;
	case MOVE_LEFT_1: return moveLeft1;
	case MOVE_LEFT_2: return moveLeft2;
	case MOVE_UP_1: return moveUp1;
	case MOVE_UP_2: return moveUp2;
	case MOVE_DOWN_1: return moveDown1;
	case MOVE_DOWN_2: return moveDown2;
	default: return moveRight1;
	}
}


EnemyEntity::SpecialState EnemyEntity::getSpecialState()
{
	return specialState;
}

void EnemyEntity::move(Direction direction)
{
	switch (direction)
	{
	case UP:
		setPosY(getPosY() + movementSpeed);
		break;
	case DOWN:
		setPosY(getPosY() - movementSpeed);
		break;
	case RIGHT:
		setPosX(getPosX() + movementSpeed);
		break;
	case LEFT:
		setPosX(getPosX() + movementSpeed);
	}
}

void EnemyEntity::findDirection()
{
	if (isCrossing())
	{
		// TODO is specialcrossing?


		findTargetTile();
		// Pfad finden
		int z1 = std::numeric_limits<int>::max();
		int z2 = std::numeric_limits<int>::max();
		int z3 = std::numeric_limits<int>::max();
		int z4 = std::numeric_limits<int>::max();
		if (direction != DOWN)
		{
			if (canMove(UP))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z1 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(RIGHT))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z3 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(LEFT))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z4 = sqrt(pow(x, 2) + pow(y, 2));
			}
		}
		if (direction != UP)
		{
			if (canMove(DOWN))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z2 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(RIGHT))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z3 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(LEFT))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z4 = sqrt(pow(x, 2) + pow(y, 2));
			}
		}
		if (direction != LEFT)
		{
			if (canMove(UP))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z1 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(RIGHT))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z3 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(DOWN))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z2 = sqrt(pow(x, 2) + pow(y, 2));
			}
		}
		if (direction != RIGHT)
		{
			if (canMove(UP))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z1 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(DOWN))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z2 = sqrt(pow(x, 2) + pow(y, 2));
			}
			if (canMove(LEFT))
			{
				int x = abs(getPosX() + 3 * AMP - targetTile.real_x);
				int y = abs(getPosY() + 3 * AMP - targetTile.real_y);
				z4 = sqrt(pow(x, 2) + pow(y, 2));
			}
		}

		if (z1 < z2 && z1 < z3 && z1 < z4)
		{
			direction = UP;
		}
		else if (z2 < z1 && z2 < z3 && z2 < z4)
		{
			direction = DOWN;
		}
		else if (z3 < z2 && z3 < z1 && z3 < z4)
		{
			direction = RIGHT;
		}
		else if (z4 < z2 && z4 < z3 && z4 < z1)
		{
			direction = LEFT;
		}
	}
	else
	{
		// Pfad folgen
		if (direction != DOWN) 
		{
			if (canMove(UP)) { direction = UP; }
		}
		if (direction != UP)
		{
			if (canMove(DOWN)) { direction = DOWN; }
		}
		if (direction != LEFT)
		{
			if (canMove(RIGHT)) { direction = RIGHT; }
		}
		if (direction != RIGHT)
		{
			if (canMove(LEFT)) { direction = LEFT; }
		}
	}
}

// TODO Testmode for Targettiles?
void EnemyEntity::findTargetTile()
{
	if (movementMode == FRIGHTENED)
	{
		// random movement
		switch (rand() % 4) 
		{
		case 0:
			targetTile = Boundaries(getPosX() + 16 * AMP + 3 * AMP, getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		case 1:
			targetTile = Boundaries(getPosX() + 3 * AMP, getPosY() + 16 * AMP + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		case 2:
			targetTile = Boundaries(getPosX() - 16 * AMP + 3 * AMP, getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		case 3:
			targetTile = Boundaries(getPosX() + 3 * AMP, getPosY() - 16 * AMP + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		}
	}
	switch (name)
	{
	case Blinky:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = Boundaries(264 * AMP, 200 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			// PacmanPosition
			targetTile = Boundaries(pacman->getPosX + 2 * AMP, pacman->getPosY + 3 * AMP, 8 * AMP, 8 * AMP);
		}
	case Pinky:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = Boundaries(16 * AMP, 200 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			// PacmanPosition + 4 Tiles
			switch (pacman->getState())
			{
			case PlayerEntity::MOVE_UP_1:
			case PlayerEntity::MOVE_UP_2:
				targetTile = Boundaries(pacman->getPosX + 2 * AMP, pacman->getPosY + (3 + 32) * AMP, 8 * AMP, 8 * AMP);
				break;
			case PlayerEntity::MOVE_DOWN_1:
			case PlayerEntity::MOVE_DOWN_2:
				targetTile = Boundaries(pacman->getPosX + 2 * AMP, pacman->getPosY + (3 - 32) * AMP, 8 * AMP, 8 * AMP);
				break;
			case PlayerEntity::MOVE_RIGHT_1:
			case PlayerEntity::MOVE_RIGHT_2:
				targetTile = Boundaries(pacman->getPosX + (2 + 32) * AMP, pacman->getPosY + 3 * AMP, 8 * AMP, 8 * AMP);
				break;
			case PlayerEntity::MOVE_LEFT_1:
			case PlayerEntity::MOVE_LEFT_2:
				targetTile = Boundaries(pacman->getPosX + (2 - 32) * AMP, pacman->getPosY + 3 * AMP, 8 * AMP, 8 * AMP);
				break;
			}
		}
	case Inky:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = Boundaries(280 * AMP, 0 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			int x = 0;
			int y = 0;
			// PacmanPosition + 2 Tiles + vektor from Blinky to Pacman
			switch (pacman->getState())
			{
			case PlayerEntity::MOVE_UP_1:
			case PlayerEntity::MOVE_UP_2:
				x = pacman->getPosX + 2 * AMP;
				y = pacman->getPosY + (3 + 16) * AMP;
				break;
			case PlayerEntity::MOVE_DOWN_1:
			case PlayerEntity::MOVE_DOWN_2:
				x = pacman->getPosX + 2 * AMP;
				y = pacman->getPosY + (3 - 16) * AMP;
				break;
			case PlayerEntity::MOVE_RIGHT_1:
			case PlayerEntity::MOVE_RIGHT_2:
				x = pacman->getPosX + (2 + 16) * AMP;
				y = pacman->getPosY + 3 * AMP;
				break;
			case PlayerEntity::MOVE_LEFT_1:
			case PlayerEntity::MOVE_LEFT_2:
				x = pacman->getPosX + (2 - 16) * AMP;
				y = pacman->getPosY + 3 * AMP;
				break;
			}
			int vektorX = pacman->getPosX() + 2 * AMP - blinky->getPosX() + 3 * AMP;
			int vektorY = pacman->getPosY() + 3 * AMP - blinky->getPosY() + 3 * AMP;
			targetTile = Boundaries(x + vektorX, y + vektorY, 8 * AMP, 8 * AMP);

		}
	case Clyde:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = Boundaries(0 * AMP, 0 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			// if(pacman away more than 8 tiles) set targettile to pacman
			// if(pacman is closer than 8 tiles) set targettile to scattertile
			int x = abs(pacman->getPosX() + 2 * AMP - x + 3 * AMP);
			int y = abs(pacman->getPosY() + 3 * AMP - y + 3 * AMP);

			int distance = sqrt(pow(x, 2) + pow(y, 2));
			if (distance > 8 * 8 * AMP)
			{
				targetTile = Boundaries(pacman->getPosX() - 2 * AMP, pacman->getPosY() - 3 * AMP, 8 * AMP, 8 * AMP);
			}
			else
			{
				targetTile = targetTile = Boundaries(0 * AMP, 0 * AMP, 8 * AMP, 8 * AMP);
			}
		}

	}
}

bool EnemyEntity::isCrossing()
{
	int c = 0;
	if (canMove(UP)) { c++; }
	if (canMove(DOWN)) { c++; }
	if (canMove(RIGHT)) { c++; }
	if (canMove(LEFT)) { c++; }
	if (c > 2)
	{
		return true;
	}
	return false;
}

bool EnemyEntity::canMove(Direction direct)
{
	switch (direct)
	{
	case UP:
		move(UP);
		auto collisions = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions->at(i)))
			{
				move(DOWN);
				return false;
			}
		}
		return true;
		break;
	case DOWN:
		move(DOWN);
		auto collisions = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions->at(i)))
			{
				move(UP);
				return false;
			}
		}
		return true;
		break;
	case RIGHT:
		move(RIGHT);
		auto collisions = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions->at(i)))
			{
				move(LEFT);
				return false;
			}
		}
		return true;
		break;
	case LEFT:
		move(LEFT);
		auto collisions = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions->at(i)))
			{
				move(RIGHT);
				return false;
			}
		}
		return true;
		break;
	}
}

EnemyEntity::Ghost EnemyEntity::getName()
{
	return name;
}

void EnemyEntity::setName(EnemyEntity::Ghost name)
{
	this->name = name;
}

void EnemyEntity::setPacman(PlayerEntity* pacman)
{
	this->pacman = pacman;
}

void EnemyEntity::setBlinky(EnemyEntity* blinky)
{
	this->blinky = blinky;
}

void EnemyEntity::setPhysics(Physics * physics)
{
	this->physics = physics;
}

void EnemyEntity::setLevel(Level * level)
{
	this->level = level;
}

EnemyEntity::MovementMode EnemyEntity::getMovementMode()
{
	return movementMode;
}

void EnemyEntity::setMovementMode(EnemyEntity::MovementMode mode)
{
	movementMode = mode;
}

bool EnemyEntity::moveOutOfCage()
{
	switch (name)
	{
	case Blinky: direction = LEFT; break; // once
	case Pinky:
		if (getPosY() >= 165) {
			direction = LEFT; 
			return true;
		}
		else
		{
			move(UP);
		}
		return false;
	case Inky:
		if (getPosY() >= 165) {
			direction = LEFT;
			return true;
		}
		else if (getPosX() >= 105) {
			move(UP);
		}
		else
		{
			move(RIGHT);
		}
		return false;
	case Clyde:
		if (getPosY() >= 165) {
			direction = LEFT;
			return true;
		}
		else if (getPosX() <= 105) {
			move(UP);
		}
		else
		{
			move(LEFT);
		}
		return false;
	}
}