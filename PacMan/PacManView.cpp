#include "PacManView.h"
#include "PacManModel.h"
#include "Display.h"
#include "PlayerEntity.h"
#include "WallEntity.h"
#include "EnemyEntity.h"
#include "Session.h"
#include "Image.h"

PacManView::PacManView(PacManModel* model, Display* display, Renderer* renderer)
	: EngineView((EngineModel*)(model), display, renderer)
{

	// add entities from level to display
	std::vector<Entity*>* entities = model->getEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		display->addDrawable(entities->at(i));
		/*
		PlayerEntity* pacman = static_cast<PlayerEntity*>(entities->at(i));
		if (pacman)
		{
			display->addDrawable(pacman);
		}
		else if (auto ghost = entities->at(i))
		{
			display->addDrawable(ghost);
		}
		*/
	}

}

void PacManView::draw()
{
	display->getDrawables()->clear();

	std::vector<Entity*>* entities = model->getEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		display->addDrawable(entities->at(i));
	}
}
