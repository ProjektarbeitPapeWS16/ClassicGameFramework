#include "DK_RequestHandler.h"

DK_RequestHandler::DK_RequestHandler(DK_Model * model) : model(model)
{
}

DK_RequestHandler::~DK_RequestHandler() {}

// Key input for climbing up a ladder.
void DK_RequestHandler::keyUpPress()
{
	this->up = true;
}

// Key input for climbing down a ladder.
void DK_RequestHandler::keyDownPress()
{
	this->down = true;
}


// Key input for walking left.
void DK_RequestHandler::keyLeftPress()
{
	this->left = true;
	// check if obstacle left
	// then move left
}

// Key input for walking right.
void DK_RequestHandler::keyRightPress()
{
	this->right = true;
	// check if obstacle right
	// then move right
}

// Key input for jump.
void DK_RequestHandler::keySpacePress()
{
	this->space = true;
	// check player state
	// if on ground, change to jump state

}

// Key input for closing the game.
void DK_RequestHandler::keyEscPress() const
{
	model->shouldClose = true;
}

// Sets all previously registered inputs as false for next iteration.
// Usage: After finishing one iteration
void DK_RequestHandler::resetKeyInputs()
{
	up = false;
	down = false;
	left = false;
	right = false;
	space = false;
}

// Translates current key inputs into player action for model logic.
// Note: Some inputs have precedence over others:
// Jump > Move Left > Move Right > Climb up > Climb down
Request DK_RequestHandler::getRequest()
{
	lastRequest = currentRequest;
	
	if (space)
	{
		if (left)
			currentRequest = JUMP_LEFT;
		else if (right)
			currentRequest = JUMP_RIGHT;
		else
			currentRequest = JUMP;
	}
	else if (right)
		currentRequest = MOVE_RIGHT;
	else if (left)
		currentRequest = MOVE_LEFT;
	else if (up)
		currentRequest = CLIMB_UP;
	else if (down)
		currentRequest = CLIMB_DOWN;
	else
		currentRequest = NONE;

	return currentRequest;
}

