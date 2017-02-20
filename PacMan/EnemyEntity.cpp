#include "EnemyEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "PacManView.h"

EnemyEntity::EnemyEntity() : Entity(nullptr, 3*3, false, new Boundaries(200, 200, 14*3, 14*3), true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
}

EnemyEntity::EnemyEntity(Boundaries * boundaries) : Entity(nullptr, 5 * 3, false, boundaries, true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
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
	specialState = request;
}

void EnemyEntity::execute()
{

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
	case DEAD: break;
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


