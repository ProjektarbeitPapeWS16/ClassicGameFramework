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

	//auto session = new Session();
	auto display = new Display();
	auto renderer = new Renderer(800, 600, "PacMan");

	//std::vector<Level*> levels;
	//levels.push_back(new Level(0, 0, 0, 0, new std::string("menu.txt")));
	//levels.push_back(new Level(0, 0, 0, 0, new std::string("level1.txt")));
	//levels.push_back(new Level(0, 0, 0, 0, new std::string("level2.txt")));
	//levels.push_back(new Level(0, 0, 0, 0, new std::string("level3.txt")));

	auto model = new PacManModel();
	auto view = new PacManView(model, display, renderer);
	auto controller = new PacManController(view, model);

	controller->gameLoop();

	return 0;
}
