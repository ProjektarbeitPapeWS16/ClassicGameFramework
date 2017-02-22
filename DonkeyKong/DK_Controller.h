#pragma once
#include "EngineController.h"
class DK_Model;
class DK_View;

class DK_Controller : public EngineController
{
public:
	typedef enum Input
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		JUMP,
		LEFT_JUMP, // both left and jump button pressed
		RIGHT_JUMP, // both right and jump button pressed
	};
	DK_Controller(DK_View* view, DK_Model* model);

	~DK_Controller() override;
	void cycle() override;

	// Checks input of latest tick and handles player entity accordingly.
	void handleRequest(Input input);
};

