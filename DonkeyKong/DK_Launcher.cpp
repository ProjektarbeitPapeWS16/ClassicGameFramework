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


//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	/*
	char* levelLayout1 = "\\level\\level_25m.txt";
	//Original Aufl�sung: 192x256; 8x8 Pixel Raster; 24x32 K�stchen
	//Skalierung x3
	auto config = new GameConfig(192, 256, 2, 8, 8, "Donkey Kong");

	//std::string x = getexepath();

	auto session = new DK_Session();
	auto display = new Display();
	auto renderer = new Renderer(config->getWidth(), config->getHeight(), "Donkey Kong");

	//std::vector<Level*> levels;
	//levels.push_back(new DK_Level(config));


	auto model = new DK_Model(session, config, levelLayout1[0]);
	auto view = new DK_View(model, display, renderer, config);
	auto controller = new DK_Controller(view, model);


	controller->gameLoop();

	return 0;
	*/
}
