#include "Renderer.h"
#include "Display.h"

#include "DK_View.h"
#include "DK_Model.h"
#pragma once

// Standard constructor for custom model, display, and renderer.
// (No custom Display and Renderer required for DK)
/*DK_View::DK_View(DK_Model * model, Display * display, Renderer * renderer) 
	: EngineView(static_cast<EngineModel*>(model), display, renderer)
{
	this->config = model->getConfig(); // FIXME: Unneeded after renderer init?
}*/

/*
DK_View::DK_View(DK_Model * model, Display * display, Renderer * renderer) :
EngineView(model, display, renderer)
{
}
*/

// Simple constructor for custom model
// Renderer configurations are determined by given model.
DK_View::DK_View(DK_Model* model)
	: EngineView( reinterpret_cast<EngineModel*>(model), //#n
		new Display(),
		new Renderer(model->config->width, model->config->height, model->config->title
		)
	)
{
}

// Method for updating view.
// Draws all current entities derived from level
// Assumes: vector containing entities was ordered to ensure that respective entities are in the foreground
void DK_View::draw()
{
	display->clearDrawables();

	//TODO: drawables
	auto drawables = model->getEntities();
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