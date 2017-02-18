#include "PlayerEntity.h"
#include "Image.h"


PlayerEntity::PlayerEntity() : Entity(nullptr, 5*3, false, new Boundaries(100, 100, 13*3, 13*3), true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	move = new Image("textures/PacMan/pacman.bmp", this, 0, 0, 0);
	moveUp = new Image("textures/PacMan/pacmanUp.bmp", this, 0, 0, 0);
	moveDown = new Image("textures/PacMan/pacmanDown.bmp", this, 0, 0, 0);
	moveRight = new Image("textures/PacMan/pacmanRight.bmp", this, 0, 0, 0);
	moveLeft = new Image("textures/PacMan/pacmanLeft.bmp", this, 0, 0, 0);
	this->image = &move;
	
}

void PlayerEntity::request(Request request)
{
	lastRequest = request;
}

void PlayerEntity::execute()
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
		switch (state)
		{
			break;
		}
		break;
	default: break;
	}
	//lastRequest = NONE;
}

Image* PlayerEntity::getImage()
{
	switch (state)
	{
	case MOVE_RIGHT_1: return move;
	case MOVE_RIGHT_2: return moveRight;
	case MOVE_LEFT_1: return move;
	case MOVE_LEFT_2: return moveLeft;
	case MOVE_UP_1: return move;
	case MOVE_UP_2: return moveUp;
	case MOVE_DOWN_1: return move;
	case MOVE_DOWN_2: return moveDown;
	default: return move;
	}
}

