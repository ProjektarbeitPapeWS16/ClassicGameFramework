#pragma once
#include "EngineModel.h"
#include "EngineView.h"

class EngineController
{
private:
	virtual void gameLoop() = 0;
	EngineView* view;
	EngineModel* model;
public:
	EngineController(EngineView* view, EngineModel* model);
	~EngineController();


	
};

