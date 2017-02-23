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
#include <vector>

#define AMP 3

EnemyEntity::EnemyEntity() 
	: Entity(nullptr, 3 * AMP, false, new Boundaries(200, 200, 14 * AMP, 14 * AMP), true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	deadUp = new Image("textures/Ghosts/deadGhostUp.bmp", this, 0, 0, 0);
	deadDown = new Image("textures/Ghosts/deadGhostDown.bmp", this, 0, 0, 0);
	deadRight = new Image("textures/Ghosts/deadGhostRight.bmp", this, 0, 0, 0);
	deadLeft = new Image("textures/Ghosts/deadGhostLeft.bmp", this, 0, 0, 0);
}

EnemyEntity::EnemyEntity(Boundaries * boundaries) : Entity(nullptr, 3 * AMP, false, boundaries, true, 100)
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
	if (specialState == DEAD)
	{
		if (getPosX() == 105 * AMP)
		{
			if (getPosY() == 165 * AMP)
			{
				specialState = ALIVE;
			}
		}
	}

	findDirection();
	move(direction);

	if (specialState == ENERGIZED1 || specialState == ENERGIZED2)
	{
		if (energizerTimer == 0) 
		{
			energizerTimer = Config::currentTimeMillis();
		}
		if ((Config::currentTimeMillis() - energizerTimer) > 4500) // 4,5 sekunden
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
			if ((Config::currentTimeMillis() - energizerTimer) > 6000)
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
		switch (direction)
		{
		case RIGHT: return deadRight;
		case LEFT: return deadLeft;
		case UP: return deadUp;
		case DOWN: return deadDown;
		default: break;
		}
		break;
	case ENERGIZED1: return energized1;
	case ENERGIZED2: return energized2;
	}

	switch (direction)
	{
	case UP:
		if (imageDifferUp)
		{
			imageDifferUp = false;
			return moveUp1;
		}
		else
		{
			imageDifferUp = true;
			return moveUp2;
		}
	case DOWN:
		if (imageDifferDown)
		{
			imageDifferDown = false;
			return moveDown1;
		}
		else
		{
			imageDifferDown = true;
			return moveDown2;
		}
	case RIGHT:
		if (imageDifferRight)
		{
			imageDifferRight = false;
			return moveRight1;
		}
		else
		{
			imageDifferRight = true;
			return moveRight2;
		}
	case LEFT:
		if (imageDifferLeft)
		{
			imageDifferLeft = false;
			return moveLeft1;
		}
		else
		{
			imageDifferLeft = true;
			return moveLeft2;
		}
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
		setPosX(getPosX() - movementSpeed);
	}
}

void EnemyEntity::findDirection()
{
	if (isCrossing())
	{
		// TODO is specialcrossing?


		findTargetTile();
		// Pfad finden
		double zDown = std::numeric_limits<int>::max();
		double zUp = std::numeric_limits<int>::max();
		double zRight = std::numeric_limits<int>::max();
		double zLeft = std::numeric_limits<int>::max();
		if (canMove(UP))
		{
			//move(UP);
			int x = abs(getPosX() + 3 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP + 8 * AMP - targetTile->real_y());
			zUp = sqrt(pow(x, 2) + pow(y, 2));
			//move(DOWN);
		}
		if (canMove(DOWN))
		{
			//move(DOWN);
			int x = abs(getPosX() + 3 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP - 8 * AMP - targetTile->real_y());
			zDown = sqrt(pow(x, 2) + pow(y, 2));
			//move(UP);
		}
		if (canMove(RIGHT))
		{
			//move(RIGHT);
			int x = abs(getPosX() + 3 * AMP + 8 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP - targetTile->real_y());
			zRight = sqrt(pow(x, 2) + pow(y, 2));
			//move(LEFT);
		}
		if (canMove(LEFT))
		{
			//move(LEFT);
			int x = abs(getPosX() + 3 * AMP - 8 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP - targetTile->real_y());
			zLeft = sqrt(pow(x, 2) + pow(y, 2));
			//move(RIGHT);
		}
		
		// can't turn back
		switch (direction)
		{
		case UP:
			zDown = std::numeric_limits<int>::max();
			break;
		case DOWN:
			zUp = std::numeric_limits<int>::max();
			break;
		case RIGHT:
			zLeft = std::numeric_limits<int>::max();
			break;
		case LEFT:
			zRight = std::numeric_limits<int>::max();
			break;
		}

		if (zDown < zUp && zDown < zRight && zDown < zLeft)
		{
			direction = DOWN;
		}
		else if (zUp < zDown && zUp < zRight && zUp < zLeft)
		{
			direction = UP;
		}
		else if (zRight < zUp && zRight < zDown && zRight < zLeft)
		{
			direction = RIGHT;
		}
		else if (zLeft < zUp && zLeft < zRight && zLeft < zDown)
		{
			direction = LEFT;
		}
	}
	else
	{
		// Pfad folgen
		if (direction == DOWN) 
		{
			if (canMove(DOWN)) { direction = DOWN; }
			if (canMove(RIGHT)) { direction = RIGHT; }
			if (canMove(LEFT)) { direction = LEFT; }
			return;
		}
		if (direction == UP)
		{
			if (canMove(UP)) { direction = UP; }
			if (canMove(RIGHT)) { direction = RIGHT; }
			if (canMove(LEFT)) { direction = LEFT; }
			return;
		}
		if (direction == LEFT)
		{
			if (canMove(LEFT)) { direction = LEFT; }
			if (canMove(UP)) { direction = UP; }
			if (canMove(DOWN)) { direction = DOWN; }
			return;
		}
		if (direction == RIGHT)
		{
			if (canMove(RIGHT)) { direction = RIGHT; }
			if (canMove(UP)) { direction = UP; }
			if (canMove(DOWN)) { direction = DOWN; }
			return;
		}
	}
}

// TODO Testmode for Targettiles?
// TODO targetTile speicherlecks
void EnemyEntity::findTargetTile()
{
	if (specialState == DEAD)
	{
		targetTile = new Boundaries((105 + 3) * AMP, (165 + 3) * AMP, 8 * AMP, 8 * AMP);
		return;
	}

	if (movementMode == FRIGHTENED)
	{
		// random movement
		switch (rand() % 4) 
		{
		case 0:
			targetTile = new Boundaries(getPosX() + 16 * AMP + 3 * AMP, getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		case 1:
			targetTile = new Boundaries(getPosX() + 3 * AMP, getPosY() + 16 * AMP + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		case 2:
			targetTile = new Boundaries(getPosX() - 16 * AMP + 3 * AMP, getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		case 3:
			targetTile = new Boundaries(getPosX() + 3 * AMP, getPosY() - 16 * AMP + 3 * AMP, 8 * AMP, 8 * AMP);
			break;
		}
	}
	switch (name)
	{
	case Blinky:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = new Boundaries(200 * AMP, 264 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			// PacmanPosition
			targetTile = new Boundaries(pacman->getPosX() + 2 * AMP, pacman->getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
		}
		break;
	case Pinky:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = new Boundaries(16 * AMP, 264 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			// PacmanPosition + 4 Tiles
			switch (pacman->getState())
			{
			case PlayerEntity::MOVE_UP_1:
			case PlayerEntity::MOVE_UP_2:
				targetTile = new Boundaries(pacman->getPosX() + 2 * AMP, pacman->getPosY() + (3 + 32) * AMP, 8 * AMP, 8 * AMP);
				break;
			case PlayerEntity::MOVE_DOWN_1:
			case PlayerEntity::MOVE_DOWN_2:
				targetTile = new Boundaries(pacman->getPosX() + 2 * AMP, pacman->getPosY() + (3 - 32) * AMP, 8 * AMP, 8 * AMP);
				break;
			case PlayerEntity::MOVE_RIGHT_1:
			case PlayerEntity::MOVE_RIGHT_2:
				targetTile = new Boundaries(pacman->getPosX() + (2 + 32) * AMP, pacman->getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
				break;
			case PlayerEntity::MOVE_LEFT_1:
			case PlayerEntity::MOVE_LEFT_2:
				targetTile = new Boundaries(pacman->getPosX() + (2 - 32) * AMP, pacman->getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
				break;
			}
		}
		break;
	case Inky:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = new Boundaries(216 * AMP, 0 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			int x = 0;
			int y = 0;
			// PacmanPosition + 2 Tiles + vektor from Blinky to Pacman
			switch (pacman->getState())
			{
			case PlayerEntity::MOVE_UP_1:
			case PlayerEntity::MOVE_UP_2:
				x = pacman->getPosX() + 2 * AMP;
				y = pacman->getPosY() + (3 + 16) * AMP;
				break;
			case PlayerEntity::MOVE_DOWN_1:
			case PlayerEntity::MOVE_DOWN_2:
				x = pacman->getPosX() + 2 * AMP;
				y = pacman->getPosY() + (3 - 16) * AMP;
				break;
			case PlayerEntity::MOVE_RIGHT_1:
			case PlayerEntity::MOVE_RIGHT_2:
				x = pacman->getPosX() + (2 + 16) * AMP;
				y = pacman->getPosY() + 3 * AMP;
				break;
			case PlayerEntity::MOVE_LEFT_1:
			case PlayerEntity::MOVE_LEFT_2:
				x = pacman->getPosX() + (2 - 16) * AMP;
				y = pacman->getPosY() + 3 * AMP;
				break;
			}
			int vektorX = pacman->getPosX() + 2 * AMP - blinky->getPosX() + 3 * AMP;
			int vektorY = pacman->getPosY() + 3 * AMP - blinky->getPosY() + 3 * AMP;
			targetTile = new Boundaries(x + vektorX, y + vektorY, 8 * AMP, 8 * AMP);

		}
		break;
	case Clyde:
		switch (movementMode)
		{
		case SCATTER:
			targetTile = new Boundaries(0 * AMP, 0 * AMP, 8 * AMP, 8 * AMP);
			break;
		case CHASE:
			// if(pacman away more than 8 tiles) set targettile to pacman
			// if(pacman is closer than 8 tiles) set targettile to scattertile

			int a = abs(pacman->getPosX() + 2 * AMP - getPosX() + 3 * AMP);
			int b = abs(pacman->getPosY() + 3 * AMP - getPosY() + 3 * AMP);

			double distance = sqrt(pow(a, 2) + pow(b, 2));
			if (distance > 8 * 8 * AMP)
			{
				targetTile = new Boundaries(pacman->getPosX() - 2 * AMP, pacman->getPosY() - 3 * AMP, 8 * AMP, 8 * AMP);
			}
			else
			{
				targetTile = targetTile = new Boundaries(0 * AMP, 0 * AMP, 8 * AMP, 8 * AMP);
			}
			break;
		}
		break;
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
	std::vector<PhysicalObject*>* collisions1;
	std::vector<PhysicalObject*>* collisions2;
	std::vector<PhysicalObject*>* collisions3;
	std::vector<PhysicalObject*>* collisions4;
	switch (direct)
	{
	case UP:
		move(UP);
		collisions1 = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions1->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions1->at(i)))
			{
				move(DOWN);
				return false;
			}
		}
		move(DOWN);
		return true;
		break;
	case DOWN:
		move(DOWN);
		collisions2 = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions2->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions2->at(i)))
			{
				move(UP);
				return false;
			}
		}
		move(UP);
		return true;
		break;
	case RIGHT:
		move(RIGHT);
		collisions3 = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions3->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions3->at(i)))
			{
				move(LEFT);
				return false;
			}
		}
		move(LEFT);
		return true;
		break;
	case LEFT:
		move(LEFT);
		collisions4 = physics->checkCollisions(static_cast<PhysicalObject*>(this), level->getPhysicalObjects());
		for (unsigned int i = 0; i < collisions4->size(); i++)
		{
			if (dynamic_cast<WallEntity*>(collisions4->at(i)))
			{
				move(RIGHT);
				return false;
			}
		}
		move(RIGHT);
		return true;
		break;
	default:
		return false;
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
	case Blinky: direction = LEFT; return true; // once
	case Pinky:
		if (getPosY() >= 165 * AMP) {
			direction = LEFT; 
			return true;
		}
		else
		{
			move(UP);
		}
		return false;
	case Inky:
		if (getPosY() >= 165 * AMP) {
			direction = LEFT;
			return true;
		}
		else if (getPosX() >= 105 * AMP) {
			setPosX(105 * AMP);
			move(UP);
		}
		else
		{
			move(RIGHT);
		}
		return false;
	case Clyde:
		if (getPosY() >= 165 * AMP) {
			direction = LEFT;
			return true;
		}
		else if (getPosX() <= 105 * AMP) {
			setPosX(105 * AMP);
			move(UP);
		}
		else
		{
			move(LEFT);
		}
		return false;
	}
	return false;
}