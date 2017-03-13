#include "EngineModel.h"
#include "Session.h"

#include "Entity_Jumpman.h"
#include "Image.h"
#include "Level.h"
#include "DK_Level.h"

const int CONST_SPEED = 10;
const int CONST_SIZE = 16;
Entity_Jumpman::Entity_Jumpman(Position position)
	: Entity(new Image*[0], CONST_SPEED, false,
		new Boundaries(
			position.x, position.y,
			16, 16 // CONST_SIZE, CONST_SIZE
		), false, 0
	)
{
	this->image[0] = new Image("textures/jumpman/DK_Jumpman_walk_1r.bmp", this, 0, 91, 127);

	this->moveLeft1 = new Image("textures/jumpman/DK_Jumpman_walk_1l.bmp", this, 0, 91, 127);
	this->moveLeft2 = new Image("textures/jumpman/DK_Jumpman_walk_2l.bmp", this, 0, 91, 127);
	this->moveLeft3 = new Image("textures/jumpman/DK_Jumpman_walk_3l.bmp", this, 0, 91, 127);
	this->moveRight1 = new Image("textures/jumpman/DK_Jumpman_walk_1r.bmp", this, 0, 91, 127);
	this->moveRight2 = new Image("textures/jumpman/DK_Jumpman_walk_2r.bmp", this, 0, 91, 127);
	this->moveRight3 = new Image("textures/jumpman/DK_Jumpman_walk_3r.bmp", this, 0, 91, 127);

	this->jumpLeft = new Image("textures/jumpman/DK_Jumpman_jump_l.bmp", this, 0, 91, 127);
	this->jumpRight = new Image("textures/jumpman/DK_Jumpman_jump_r.bmp", this, 0, 91, 127);

	this->fallLeftEnd = new Image("textures/jumpman/DK_Jumpman_fallend_l.bmp", this, 0, 91, 127);
	this->fallRightEnd = new Image("textures/jumpman/DK_Jumpman_fallend_r.bmp", this, 0, 91, 127);

	this->climb1 = new Image("textures/jumpman/DK_Jumpman_climb_l.bmp", this, 0, 91, 127);
	this->climb2 = new Image("textures/jumpman/DK_Jumpman_climb_2.bmp", this, 0, 91, 127);
	this->climbEnd1 = new Image("textures/jumpman/DK_Jumpman_climbupend_1.bmp", this, 0, 91, 127);
	this->climbEnd2 = new Image("textures/jumpman/DK_Jumpman_climbupend_2.bmp", this, 0, 91, 127);
	this->climbEnd3 = new Image("textures/jumpman/DK_Jumpman_climbupend_3.bmp", this, 0, 91, 127);

	this->death1 = new Image("textures/jumpman/DK_Jumpman_death1.bmp", this, 0, 91, 127);
	this->death2 = new Image("textures/jumpman/DK_Jumpman_death2.bmp", this, 0, 91, 127);
	this->death3 = new Image("textures/jumpman/DK_Jumpman_death3.bmp", this, 0, 91, 127);
	this->death4 = new Image("textures/jumpman/DK_Jumpman_death4.bmp", this, 0, 91, 127);
	this->death5 = new Image("textures/jumpman/DK_Jumpman_death5r.bmp", this, 0, 91, 127);
}
// Externally Updates player position and sprite
void Entity_Jumpman::update(unsigned int xOffset, unsigned int yOffset, PlayerState newState)
{
	// 1. update player-state; consider animation state switch
	if (state == newState) {
		animationStateCount++;
		jumpStateCount--;
	}
	else {
		animationStateCount = 0;
		jumpStateCount = JUMPSTATE_TICKS;	// reset jump velocity to max
	}
	// Update sprite to state
	switch (newState)
	{
	case MOVE_RIGHT:
		switch (animationStateCount%3)
		{
		case 0:	
		default:
			image[0] = moveRight1; break;
		case 1:
			image[0] = moveRight2; break;
		case 2:
			image[0] = moveRight3; break;
		}
		break;
	case MOVE_LEFT:
		switch (animationStateCount % 3)
		{
		case 0:
		default:
			image[0] = moveLeft1; break;
		case 1:
			image[0] = moveLeft2; break;
		case 2:
			image[0] = moveLeft3; break;
		}
		break;
	case CLIMB:
		switch (animationStateCount % 3)
		{
		case 0:
		default:
			image[0] = climb1; break;
		case 1:
			image[0] = climb2; break;
		}
		break;
	case JUMP:
		switch (state) //check last state
		{
		case MOVE_LEFT:
		default:
			image[0] = jumpLeft; break;
		case MOVE_RIGHT:
			image[0] = jumpRight; break;
		}
		break;
	case JUMP_LEFT:
		image[0] = jumpLeft;
		break;
	case JUMP_RIGHT:
		image[0] = jumpRight;
		break;
	case DEAD:
		switch (animationStateCount % 9)
		{
		case 0:
		case 4:
		default:
			image[0] = death1; break;
		case 1:
		case 5:
			image[0] = death2; break;
		case 2:
		case 6:
			image[0] = death3; break;
		case 3:
		case 7:
			image[0] = death4; break;
		case 8:
			image[0] = death5; break;
		}
		break;
	default: // no input? no change.
		break;		
	}
	state = newState;

	// 2. Move player
	this->setPosition(this->getPosX() + xOffset, this->getPosY() + yOffset);
}

// Returns the amount of upwards movement left to perform from the jump.
// Decrements it
bool Entity_Jumpman::jumpVelocityLeft() const
{
	return jumpStateCount > 0;
}
