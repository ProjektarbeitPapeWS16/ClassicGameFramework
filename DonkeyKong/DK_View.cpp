#include "DK_View.h"
#include "Display.h"
#include "Entity_Jumpman.h"
#include "Text.h"
#include "Font.h"
#include "Level_25m.h"
#include "DK_Model.h"
#include "Session.h"

DK_View::DK_View(DK_Model* model, Display* display, Renderer* renderer, DK_Config* config)
	: EngineView(reinterpret_cast<EngineModel*>(model), display, renderer)
{
	//Font* font = new Font("fonts/normal/", 8, 8, 200, 80, 0);

	//Drawable* player = new Entity_Jumpman(config, new Position(5, 5));
	//Drawable* text = new Text(font, "HELLO WORLD 2017", new Position(config->applyFactor(5), config->applyFactor(5)), config->applyFactor(1), 255, 0, 0);
	//display->addDrawable(player);
	//display->addDrawable(text);

	Level_25m* Level_25m = new Level_25m(config);
	std::vector<Entity*>* entities = Level_25m->getEntities();

	for (int i = 0; i < entities->size(); i++)
	{
		display->addDrawable(entities->at(i));
	}

	model->getSession()->setLevel(Level_25m);

}

void DK_View::draw()
{

}
