#pragma once
#include "EngineModel.h"
#include "EngineView.h"

class EngineController
{
protected:
	EngineView view;
	EngineModel model;
public:
	EngineController( EngineView& view,  EngineModel& model);

	virtual void gameLoop();
	virtual ~EngineController();

};

