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
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
	//bool esc = false;		Possible future use: Pause/Confirm exit
	DK_Model* model;
	Request lastRequest = NONE;
	Request currentRequest = NONE;
public:
	DK_RequestHandler(DK_Model* model);
	~DK_RequestHandler();

	void keyUpPress();
	void keyDownPress();
	void keyLeftPress();
	void keyRightPress();
	void keySpacePress();
	void keyEscPress() const;
	void resetKeyInputs();
	Request getRequest();
};