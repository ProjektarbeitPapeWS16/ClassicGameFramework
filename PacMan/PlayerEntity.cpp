#include "PlayerEntity.h"
#include "Image.h"


PlayerEntity::PlayerEntity(Boundaries* boundaries) : Entity(nullptr, 3 * 3, false, boundaries, true, 100)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	none = new Image("thisTextureDoenstExist", this, 0, 0, 0);
	move = new Image("textures/PacMan/pacman.bmp", this, 0, 0, 0);
	moveUp = new Image("textures/PacMan/pacmanUp.bmp", this, 0, 0, 0);
	moveDown = new Image("textures/PacMan/pacmanDown.bmp", this, 0, 0, 0);
	moveRight = new Image("textures/PacMan/pacmanRight.bmp", this, 0, 0, 0);
	moveLeft = new Image("textures/PacMan/pacmanLeft.bmp", this, 0, 0, 0);

	pacmanDeath[0] = new Image("textures/PacMan/pacmanDeath1.bmp", this, 0, 0, 0);
	pacmanDeath[1] = new Image("textures/PacMan/pacmanDeath2.bmp", this, 0, 0, 0);
	pacmanDeath[2] = new Image("textures/PacMan/pacmanDeath3.bmp", this, 0, 0, 0);
	pacmanDeath[3] = new Image("textures/PacMan/pacmanDeath4.bmp", this, 0, 0, 0);
	pacmanDeath[4] = new Image("textures/PacMan/pacmanDeath5.bmp", this, 0, 0, 0);
	pacmanDeath[5] = new Image("textures/PacMan/pacmanDeath6.bmp", this, 0, 0, 0);
	pacmanDeath[6] = new Image("textures/PacMan/pacmanDeath7.bmp", this, 0, 0, 0);
	pacmanDeath[7] = new Image("textures/PacMan/pacmanDeath8.bmp", this, 0, 0, 0);
	pacmanDeath[8] = new Image("textures/PacMan/pacmanDeath9.bmp", this, 0, 0, 0);

	this->image = &move;
	
}

void PlayerEntity::request(Request request)
{
	pufferRequest = request;
}

void PlayerEntity::requestPuffer()
{
	lastRequest = pufferRequest;
}

void PlayerEntity::requestMemory()
{
	lastRequest = memoryRequest;
	state = memoryState;
}

void PlayerEntity::setMemoryRequest()
{
	memoryRequest = lastRequest;
	memoryState = state;
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
	case DIE:
		animationCounter++;
		state = DEAD;
	default: break;
	}
}

void PlayerEntity::stepBack()
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
	//lastRequest = memoryRequest;
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
	case DEAD: return deadAnimation();
	default: return move;
	}
}

Image* PlayerEntity::deadAnimation()
{
	if (animationCounter == 1)
	{
		return moveUp;
	} 
	else if (animationCounter > 10)
	{
		return none;
	}
	return pacmanDeath[animationCounter - 2];
}

PlayerEntity::~PlayerEntity()
{
	delete none;
	delete move;
	delete moveUp;
	delete moveDown;
	delete moveRight;
	delete moveLeft;
	
	for (unsigned int i = 0; i < 9; i++)
	{
		delete pacmanDeath[i];
	}
}