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

void EnemyEntity::request(State request)
{
	state = request;
	if (request == ENERGIZED)
	{
		energizerTimer = 0;
		energizerTimer2 = 0;
	}
}


void EnemyEntity::execute()
{
	alternateVar();

	// if Ghost leaves screen
	if (getPosX() <= -(13 * 3)) {
		setPosX(219 * 3);
	}
	if (getPosX() >= 222 * 3) {
		setPosX(-(9 * 3));
	}


	if (cageState == NO)
	{
		findDirection();
		move(direction);
	} 
	else
	{
		moveInCage();
	}


	switch (state)
	{
	case NONE:
		break;
	case DEAD: // TODO revive animation
		if (getPosX() == 105 * AMP)
		{
			if (getPosY() == 165 * AMP)
			{
				cageState = IN;
			}
		}
		break;
	case ENERGIZED:
		if ((Config::currentTimeMillis() - energizerTimer) > 4500) // 4,5 sekunden
		{
			if (energizeAlt) { energizeAlt = false; }
			else { energizeAlt = true; }
			if ((Config::currentTimeMillis() - energizerTimer) > 6000)
			{
				state = NONE;
			}
		}
		break;
	}
}

void EnemyEntity::energize()
{
	if (state != DEAD)
	{
		state = ENERGIZED;
		energizeAlt = false;
		energizerTimer = Config::currentTimeMillis();
		invertDirection();
	}
}

void EnemyEntity::invertDirection()
{
	switch (direction)
	{
	case UP: direction = DOWN; break;
	case DOWN: direction = UP; break;
	case RIGHT: direction = LEFT; break;
	case LEFT: direction = RIGHT; break;
	}
}

Image* EnemyEntity::getImage()
{
	switch (state)
	{
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
	case ENERGIZED: 
		if (energizeAlt) { return energized2; }
		else { return energized1; }
	default: break;
	}

	switch (direction)
	{
	case UP:
		if (alternate) { return moveUp1; }
		else { return moveUp2; }
	case DOWN:
		if (alternate) { return moveDown1; }
		else { return moveDown2; }
	case RIGHT:
		if (alternate) { return moveRight1; }
		else { return moveRight2; }
	case LEFT:
		if (alternate) { return moveLeft1; }
		else { return moveLeft2; }
	default: return moveRight1;
	}
}


EnemyEntity::State EnemyEntity::getState()
{
	return state;
}

void EnemyEntity::move(Direction direction)
{
	switch (direction)
	{
	case UP:	setPosY(getPosY() + movementSpeed);	break;
	case DOWN:	setPosY(getPosY() - movementSpeed);	break;
	case RIGHT:	setPosX(getPosX() + movementSpeed);	break;
	case LEFT:	setPosX(getPosX() - movementSpeed); break;
	}
}

void EnemyEntity::alternateVar()
{
	if (alternate) {	alternate = false;	}
	else {	alternate = true;	}
}

void EnemyEntity::findDirection()
{
	if (isCrossing())
	{
		if (isSpecialCrossing())
		{
			if (direction == RIGHT || direction == LEFT)
			{
				return;
			}
		}

		switch (state)
		{
		case NONE: 
		case DEAD:
			findTargetTile();
			break;
		case ENERGIZED:
			switch (rand() % 4)
			{
			case 0: //  UP
				if (canMove(UP)) { direction = UP; return; }
			case 1: // DOWN
				if (canMove(DOWN)) { direction = DOWN; return; }
			case 2: // RIGHT
				if (canMove(RIGHT)) { direction = RIGHT; return; }
			case 3: // LEFT
				if (canMove(LEFT)) { direction = LEFT; return; }
				if (canMove(DOWN)) { direction = DOWN; return; }
				if (canMove(UP)) { direction = UP; return; }
				if (canMove(RIGHT)) { direction = RIGHT; return; }
			}
			return;
		}


		// Pfad finden
		double zDown = std::numeric_limits<int>::max();
		double zUp = std::numeric_limits<int>::max();
		double zRight = std::numeric_limits<int>::max();
		double zLeft = std::numeric_limits<int>::max();
		if (canMove(UP))
		{
			int x = abs(getPosX() + 3 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP + 8 * AMP - targetTile->real_y());
			zUp = sqrt(pow(x, 2) + pow(y, 2));
		}
		if (canMove(DOWN))
		{
			int x = abs(getPosX() + 3 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP - 8 * AMP - targetTile->real_y());
			zDown = sqrt(pow(x, 2) + pow(y, 2));
		}
		if (canMove(RIGHT))
		{
			int x = abs(getPosX() + 3 * AMP + 8 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP - targetTile->real_y());
			zRight = sqrt(pow(x, 2) + pow(y, 2));
		}
		if (canMove(LEFT))
		{
			int x = abs(getPosX() + 3 * AMP - 8 * AMP - targetTile->real_x());
			int y = abs(getPosY() + 3 * AMP - targetTile->real_y());
			zLeft = sqrt(pow(x, 2) + pow(y, 2));
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
	switch (state)
	{
	case DEAD:
		targetTile = new Boundaries((105 + 3) * AMP, (165 + 3) * AMP, 8 * AMP, 8 * AMP);
		return;
	case NONE:
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
				case PlayerEntity::MOVE_UP:
					targetTile = new Boundaries(pacman->getPosX() + 2 * AMP, pacman->getPosY() + (3 + 32) * AMP, 8 * AMP, 8 * AMP);
					break;
				case PlayerEntity::MOVE_DOWN:
					targetTile = new Boundaries(pacman->getPosX() + 2 * AMP, pacman->getPosY() + (3 - 32) * AMP, 8 * AMP, 8 * AMP);
					break;
				case PlayerEntity::MOVE_RIGHT:
					targetTile = new Boundaries(pacman->getPosX() + (2 + 32) * AMP, pacman->getPosY() + 3 * AMP, 8 * AMP, 8 * AMP);
					break;
				case PlayerEntity::MOVE_LEFT:
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
				case PlayerEntity::MOVE_UP:
					x = pacman->getPosX() + 2 * AMP;
					y = pacman->getPosY() + (3 + 16) * AMP;
					break;
				case PlayerEntity::MOVE_DOWN:
					x = pacman->getPosX() + 2 * AMP;
					y = pacman->getPosY() + (3 - 16) * AMP;
					break;
				case PlayerEntity::MOVE_RIGHT:
					x = pacman->getPosX() + (2 + 16) * AMP;
					y = pacman->getPosY() + 3 * AMP;
					break;
				case PlayerEntity::MOVE_LEFT:
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

bool EnemyEntity::isSpecialCrossing()
{
	// +- 2 Genauigkeit

	// xPos 90 
	if (abs(getPosX() - 91 * AMP) < 3 * AMP)
	{
		// yPos 165
		if (abs(getPosY() - 165 * AMP) < 3 * AMP)
		{
			return true;
		}

		// yPos 69
		if (abs(getPosY() - 69 * AMP) < 3 * AMP)
		{
			return true;
		}
	}

	// xPos 120
	// yPos 165
	if (abs(getPosX() - 115 * AMP) < 3 * AMP)
	{
		if (abs(getPosY() - 165 * AMP) < 3 * AMP)
		{
			return true;
		}

		// yPos 69
		if (abs(getPosY() - 69 * AMP) < 3 * AMP)
		{
			return true;
		}
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

void EnemyEntity::setMovementMode(EnemyEntity::MovementMode mode)
{
	movementMode = mode;
}

void EnemyEntity::setDirection(Direction dir)
{
	direction = dir;
}

EnemyEntity::Cage EnemyEntity::getCageState()
{
	return cageState;
}

void EnemyEntity::setCageState(Cage cage)
{
	cageState = cage;
}

void EnemyEntity::moveInCage()
{
	switch (cageState)
	{
	case IN:
		move(DOWN);
		if (getPosY() <= 141 * AMP)
		{
			setPosY(141 * AMP);
			cageState = OUT;
			if (state = DEAD)
			{
				state = NONE;
			}
		}
		break;
	case OUT:
		move(UP);
		if (getPosY() >= 165 * AMP) 
		{
			direction = LEFT;
			cageState = NO;
		}
		break;
	case LEFTPLACE:
		move(RIGHT);
		if (getPosX() >= 105 * AMP) 
		{
			setPosX(105 * AMP);
			cageState = OUT;
		}
		break;
	case RIGHTPLACE:
		move(LEFT);
		if (getPosX() <= 105 * AMP) 
		{
			setPosX(105 * AMP);
			cageState = OUT;
		}
		break;
	case LOCKED:
		break;
	case NO:
		break;
	}
}