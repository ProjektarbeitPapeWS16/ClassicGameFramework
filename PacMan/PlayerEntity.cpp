#include "PlayerEntity.h"
#include "Image.h"


PlayerEntity::PlayerEntity(Boundaries* boundaries) 
	: Entity(nullptr, 3 * 3, false, boundaries, true, 100)
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

void PlayerEntity::request(PlayerState request)
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
	// teleportpath
	if (getPosX() <= -(11 * 3)) {
		setPosX(220 * 3);
	}
	if (getPosX() >= 223 * 3) {
		setPosX(-(8 * 3));
	}


	state = lastRequest;
	switch (state)
	{
	case MOVE_RIGHT:
		this->setPosX(this->getPosX() + movementSpeed); break;
	case MOVE_LEFT:
		this->setPosX(this->getPosX() - movementSpeed); break;
	case MOVE_UP:
		this->setPosY(this->getPosY() + movementSpeed); break;
	case MOVE_DOWN:
		this->setPosY(this->getPosY() - movementSpeed); break;
	case DIE:
		animationCounter++;
		if (animationCounter > 10)
		{
			state = DEAD;
		}
	case DEAD:
	default: break;
	}
}

void PlayerEntity::stepBack()
{
	switch (state)
	{
	case MOVE_RIGHT: this->setPosX(this->getPosX() - movementSpeed); break;
	case MOVE_LEFT: this->setPosX(this->getPosX() + movementSpeed); break;
	case MOVE_UP: this->setPosY(this->getPosY() - movementSpeed); break;
	case MOVE_DOWN: this->setPosY(this->getPosY() + movementSpeed); break;
	default: break;
	}
	//lastRequest = memoryRequest;
}

Image* PlayerEntity::getImage()
{
	switch (state)
	{
	case MOVE_RIGHT:
		if (alternate) {return move;}
		else {return moveRight;}
	case MOVE_LEFT:
		if (alternate) {return move;}
		else {return moveLeft;}
	case MOVE_UP: 
		if (alternate) {return move;}
		else {return moveUp;}
	case MOVE_DOWN: 
		if (alternate) {return move;}
		else {return moveDown;}
	case DIE: return deadAnimation();
	case DEAD:
	default: return move;
	}
}

PlayerEntity::PlayerState PlayerEntity::getState()
{
	return state;
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

void PlayerEntity::alternateMovement()
{
	if (alternate)
	{
		alternate = false;
	}
	else 
	{
		alternate = true;
	}
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