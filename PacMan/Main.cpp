#pragma once
#include <windows.h>
#include "Config.h"

#include "Level.h"
#include "Session.h"
#include "Renderer.h"
#include "Display.h"


#include "PacManModel.h"
#include "PacManView.h"
#include "PacManController.h"


//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	std::string x = getexepath();


	auto model = new PacManModel();
	auto view = new PacManView(model);
	auto controller = new PacManController(view, model);

	controller->gameLoop();

	return 0;
}
