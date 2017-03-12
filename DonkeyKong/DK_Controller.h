#pragma once
#include "EngineController.h"
#include "DK_Model.h"
#include "DK_View.h"
//class DK_Model;
//class DK_View;

class DK_Controller : public EngineController
{
	DK_Model* model;
public:
	typedef enum 
	{
		UP,			// climb ladder upwards
		DOWN,		// climb ladder downwards
		LEFT,		// walk left
		RIGHT,		// walk right
		JUMP,		// jump horizontally upwards
		LEFT_JUMP,	// both left and jump button pressed
		RIGHT_JUMP, // both right and jump button pressed
	} Input;
	DK_Controller(DK_View* view, DK_Model* model);
	~DK_Controller() override;

	void cycle() override;

	// Checks input of latest tick and handles player entity accordingly.
	void handleRequest(Input input);
};

