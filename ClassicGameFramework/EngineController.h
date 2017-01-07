#pragma once
#include "EngineModel.h"
#include "EngineView.h"

class EngineController
{
protected:
	EngineView view;
	EngineModel model;
public:

	static void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode);

	EngineController( EngineView& view,  EngineModel& model);

	virtual void gameLoop();
	virtual ~EngineController();

};

