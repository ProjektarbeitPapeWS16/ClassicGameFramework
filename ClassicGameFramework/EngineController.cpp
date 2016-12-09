#include "EngineController.h"

EngineController::EngineController(EngineView* view)
{
	
}

EngineController::EngineController(EngineView * view, EngineModel * model)
{
	this->view = view;
	this->model = model;
	gameLoop();
}

EngineController::~EngineController()
{
}
