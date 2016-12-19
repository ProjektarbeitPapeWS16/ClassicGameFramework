#pragma once
#include "EngineModel.h"
#include "EngineView.h"

class EngineController
{
protected:
	EngineView view;
	EngineModel model;
public:
	EngineController(const EngineView& view, const EngineModel& model);

	virtual void gameLoop();
	virtual ~EngineController();

};

