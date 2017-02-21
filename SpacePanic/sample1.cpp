#include <windows.h>
#include "Config.h"

#include "Level.h"
#include "Session.h"
#include "Renderer.h"
#include "Display.h"


#include "SpacePanicModel.h"
#include "SpacePanicView.h"
#include "SpacePanicController.h"
#include "GameConfig.h"
#include "Stage.h"


//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	auto model = new SpacePanicModel();
	auto view = new SpacePanicView(model);
	auto controller = new SpacePanicController(view, model);
	
	controller->gameLoop();

	return 0;
}
