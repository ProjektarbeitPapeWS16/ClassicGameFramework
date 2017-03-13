#pragma once
#include "DK_Model.h"

// Possible player actions.
	enum Request {
		NONE,
		MOVE_RIGHT,
		MOVE_LEFT,
		CLIMB_UP,
		CLIMB_DOWN,
		JUMP,
		JUMP_LEFT,
		JUMP_RIGHT,
	};
// Class for scheduling controller inputs to translate into model manipulation on iteration.
class DK_RequestHandler {
protected:
	DK_Model* model;
	Request lastRequest = NONE;
	Request currentRequest = NONE;
public:
	static bool up;
	static bool down;
	static bool left;
	static bool right;
	static bool space;
	static bool esc;		// Possible future use: Pause/Confirm exit
	explicit DK_RequestHandler(DK_Model* model);
	~DK_RequestHandler();

	static void keyUpPress();
	static void keyDownPress();
	static void keyLeftPress();
	static void keyRightPress();
	static void keySpacePress();
	static void keyEscPress();
	static void resetKeyInputs();
	Request getRequest();
};