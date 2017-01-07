#include "EngineController.h"

EngineController::EngineController( EngineView& view,  EngineModel& model): view(view),
                                                                                      model(model)
{
}

void EngineController::gameLoop()
{
	while (model.gameloopShouldEnd == false) 
	{
		// TODO
		// model.nextIteration(); 
		view.update();
	}
	
}

EngineController::~EngineController()
{
}
