#include "Display.h"
#include "Session.h"
#include "Text.h"
#include "Font.h"

#include "DK_View.h"
#include "DK_Model.h"
#include "Entity_Jumpman.h"
#include "Level_25m.h"

DK_View::DK_View(DK_Model* model, Display* display, Renderer* renderer, GameConfig* config)
	: EngineView(reinterpret_cast<EngineModel*>(model), display, renderer)
{

	Level_25m* level_25m = new Level_25m(config);
	std::vector<Entity*>* entities = level_25m->getEntities();

	for (int i = 0; i < entities->size(); i++)
	{
		display->addDrawable(entities->at(i));
	}

	model->getSession()->setLevel(level_25m);

}

void DK_View::draw()
{

}
