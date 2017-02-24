#include "DK_View.h"
#include "Level.h"
#include "DK_Model.h"
#include "Renderer.h"
#include "Display.h"
#include "Session.h"
#include "Entity.h"

const char* TITLE = "Donkey Kong";

DK_View::DK_View(DK_Model* model)
	: EngineView(
		reinterpret_cast<EngineModel*>(model),
		new Display(),
		new Renderer(model->getConfig()->getWidth(),
			model->getConfig()->getHeight(), TITLE
		)
	)
{
}

// Method for updating view.
// Draws all current entities derived from level
// Assumes: vector containing entities was ordered to ensure that respective entities are in the foreground
void DK_View::draw()
{
	auto drawables = model->getDrawables();
	//display->setDrawables(drawables);
	display->clearDrawables();
	if (drawables != nullptr)
	{		
		for (int i = 0; i < drawables->size(); i++)
		{	
			// draw from first to last
			// TODO: add layer-info to vector, then get	them from model method?
			display->addDrawable(drawables->at(i));
		}
	}
}