#include "EnemyEntity.h"
#include "Image.h"
#include "EngineView.h"
#include "PacManView.h"

EnemyEntity::EnemyEntity() : Entity(nullptr, 5*3, false, new Boundaries(200, 200, 14*3, 14*3), true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	moveUp1 = new Image("textures/Ghosts/blueGhost/blueGhostUp1.bmp", this, 0, 0, 0);
	moveUp2 = new Image("textures/Ghosts/blueGhost/blueGhostUp2.bmp", this, 0, 0, 0);
	moveDown1 = new Image("textures/Ghosts/blueGhost/blueGhostDown1.bmp", this, 0, 0, 0);
	moveDown2 = new Image("textures/Ghosts/blueGhost/blueGhostDown2.bmp", this, 0, 0, 0);
	moveRight1 = new Image("textures/Ghosts/blueGhost/blueGhostRight1.bmp", this, 0, 0, 0);
	moveRight2 = new Image("textures/Ghosts/blueGhost/blueGhostRight2.bmp", this, 0, 0, 0);
	moveLeft1 = new Image("textures/Ghosts/blueGhost/blueGhostLeft1.bmp", this, 0, 0, 0);
	moveLeft2 = new Image("textures/Ghosts/blueGhost/blueGhostLeft2.bmp", this, 0, 0, 0);
	energized1 = new Image("textures/Ghosts/energizedGhost1.bmp", this, 0, 0, 0);
	energized2 = new Image("textures/Ghosts/energizedGhost2.bmp", this, 0, 0, 0);
}

void EnemyEntity::request(Request request)
{
	lastRequest = request;
}

void EnemyEntity::execute()
{

	switch (lastRequest)
	{
	case MOVE_RIGHT:
		switch (state)
		{
		case DEAD: break;
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
		case DEAD: break;
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
		case DEAD: break;
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
		case DEAD: break;
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
	case DO_ACTION:
		
	default: break;
	}
	lastRequest = NONE;
}

Image* EnemyEntity::getImage()
{
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
	default: return moveUp1;
	}
}
