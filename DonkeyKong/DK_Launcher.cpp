#pragma once
#include <windows.h>
#include "Config.h"

#include "Level.h"
#include "Session.h"
#include "Renderer.h"
#include "Display.h"

#include "DK_Model.h"
#include "DK_View.h"
#include "DK_Controller.h"
#include "GameConfig.h"
#include "DK_Level.h"
#include "DK_Session.h"



//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	
	char* levelLayout1 = "\\level\\level_25m.txt";
	std::vector<char*>* levelLayout = new std::vector<char*>();
	levelLayout->push_back(levelLayout1);
	//Original Auflösung: 192x256; 8x8 Pixel Raster; 24x32 Kästchen
	//Skalierung x3
	auto config = new GameConfig("Donkey Kong", 192, 256, 2, 8, 8);

	//std::string x = getexepath();

	auto session = new DK_Session();
	auto display = new Display();
	auto renderer = new Renderer(config->getWidth(), config->getHeight(), "Donkey Kong");

	//std::vector<Level*> levels;
	//levels.push_back(new DK_Level(config));


	auto model = new DK_Model(session, config, levelLayout);
	auto view = new DK_View(model, display, renderer);
	auto controller = new DK_Controller(view, model);


	controller->gameLoop();

	return 0;
	
}
