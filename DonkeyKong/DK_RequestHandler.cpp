#include "DK_RequestHandler.h"

// Init static variables.
bool DK_RequestHandler::up = false;
bool DK_RequestHandler::down = false;
bool DK_RequestHandler::left = false;
bool DK_RequestHandler::right = false;
bool DK_RequestHandler::space = false;
bool DK_RequestHandler::esc = false;

// Basic constructor
DK_RequestHandler::DK_RequestHandler(DK_Model * model) : model(model) {}

DK_RequestHandler::~DK_RequestHandler() {}

// Key input for climbing up a ladder.
void DK_RequestHandler::keyUpPress()
{
	up = true;
}

// Key input for climbing down a ladder.
void DK_RequestHandler::keyDownPress()
{
	down = true;
}


// Key input for walking left.
void DK_RequestHandler::keyLeftPress()
{
	left = true;
	// check if obstacle left
	// then move left
}

// Key input for walking right.
void DK_RequestHandler::keyRightPress()
{
	right = true;
	// check if obstacle right
	// then move right
}

// Key input for jump.
void DK_RequestHandler::keySpacePress()
{
	space = true;
	// check player state
	// if on ground, change to jump state

}

// Key input for closing the game.
void DK_RequestHandler::keyEscPress() 
{
	esc = true;
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
