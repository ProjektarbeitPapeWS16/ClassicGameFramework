#pragma once
#include <windows.h>
#include "Config.h"

#include "Renderer.h"
#include "Display.h"

#include "DK_Model.h"
#include "DK_View.h"
#include "DK_Controller.h"
#pragma once

//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	auto model = new DK_Model();
	auto view = new DK_View(model);
	auto controller = new DK_Controller(view, model);

	controller->gameLoop();

	delete controller;
	delete view;
	delete model;

	return 0;
}
/*
	
	char* levelLayout1 = DK_Model::DK_LEVELLAYOUTPATH_1;// "\\level\\level_25m.txt";
	std::vector<char*>* levelLayout = new std::vector<char*>();
	levelLayout->push_back(DK_Model::DK_LEVELLAYOUTPATH_1);
	//Original Auflösung: 192x256; 8x8 Pixel Raster; 24x32 Kästchen
	//Skalierung x3
	auto config = new GameConfig("Donkey Kong", 192, 256, 2, 8, 8);

	//std::string x = getexepath();

	auto session = new DK_Session();
	auto display = new Display();
	auto renderer = new Renderer(config->getWidth(), config->getHeight(), config->getTitle());

*/
