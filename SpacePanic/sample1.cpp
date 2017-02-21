#include <windows.h>
#include "Config.h"

#include "SpacePanicModel.h"
#include "SpacePanicView.h"
#include "SpacePanicController.h"

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

	delete controller;
	delete view;
	delete model;

	return 0;
}
