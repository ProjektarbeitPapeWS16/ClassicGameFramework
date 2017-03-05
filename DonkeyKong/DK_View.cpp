#include "Renderer.h"
#include "Display.h"

#include "DK_View.h"
#include "DK_Model.h"

// Standard constructor for custom model, display, and renderer.
// (No custom Display and Renderer required for DK)
DK_View::DK_View(DK_Model * model, Display * display, Renderer * renderer) 
	: EngineView(static_cast<EngineModel*>(model), display, renderer)
{
	this->config = model->getConfig(); // FIXME: Unneeded after renderer init?
}

// Simple constructor for custom model
// Renderer settings are determined by given model.
DK_View::DK_View(DK_Model* model)
	: DK_View(model,
		new Display(),
		new Renderer(model->getConfig()->getWidth(),
			model->getConfig()->getHeight(), model->getConfig()->getTitle()
		)
	)
{
}

// Method for updating view.
// Draws all current entities derived from level
// Assumes: vector containing entities was ordered to ensure that respective entities are in the foreground
void DK_View::draw()
{
	auto drawables = model->getEntities();
	//display->setDrawables(drawables);
	display->clearDrawables();
	if (drawables != nullptr)
	{		
		for (unsigned int i = 0; i < drawables->size(); i++)
		{	
			// draw from first to last
			// TODO: add layer-info to vector, then get	them from model method?
			display->addDrawable(drawables->at(i));
		}
	}
}