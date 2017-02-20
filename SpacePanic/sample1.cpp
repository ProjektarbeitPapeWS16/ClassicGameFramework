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
#include "Stage1.h"


//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	//Original Auflösung: 192x256; 8x8 Pixel Raster; 24x32 Kästchen
	//Skalierung x3
	auto config = new GameConfig(192, 256, 2, 8, 8);

	//std::string x = getexepath();

	auto session = new Session();
	auto display = new Display();
	auto renderer = new Renderer(config->getWidth(), config->getHeight(), "Space Panic");

	//std::vector<Level*> levels;
	//levels.push_back(new Stage1(config));
	

	auto model = new SpacePanicModel(session);
	auto view = new SpacePanicView(model, display, renderer, config);
	auto controller = new SpacePanicController(view, model);

	
	controller->gameLoop();

	return 0;
}
