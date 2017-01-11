#pragma once
#include "Config.h"

#include "Level.h"
#include "Session.h"
#include "Renderer.h"
#include "Display.h"


#include "PacManModel.h"
#include "PacManView.h"
#include "PacManController.h"

int main()
{
	auto session = new Session();
	auto display = new Display();
	auto renderer = new Renderer(800, 600, "Space Panic");

	std::vector<Level*> levels;
	levels.push_back(new Level(0, 0, 0, 0, new std::string("menu.txt")));
	levels.push_back(new Level(0, 0, 0, 0, new std::string("level1.txt")));
	levels.push_back(new Level(0, 0, 0, 0, new std::string("level2.txt")));
	levels.push_back(new Level(0, 0, 0, 0, new std::string("level3.txt")));


	auto model = new PacManModel(session);
	auto view = new PacManView(model, display, renderer);
	auto controller = new PacManController(view, model);



	controller->gameLoop();

	return 0;
}