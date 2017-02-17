#include "PacManView.h"
#include "PacManModel.h"
#include "Display.h"
#include "PlayerEntity.h"
#include "WallEntity.h"
#include "EnemyEntity.h"
#include "Session.h"
#include "StdLevel.h"
#include "Image.h"

PacManView::PacManView(PacManModel* model, Display* display, Renderer* renderer)
	: EngineView((EngineModel*)(model), display, renderer)
{
	Level* level = static_cast<PacManModel*>(model)->getSession()->getLevel();

	// add entities from level to display
	std::vector<Entity>* entities = level->getEntities();
	for (int i = 0; i < entities->size(); i++)
	{
		display->addDrawable(&(entities->at(i)));
		PlayerEntity* pacman = dynamic_cast<PlayerEntity*>(&((*entities)[i]));
		if (pacman)
		{
			display->addDrawable(pacman);
			
			/*
			this->imageCount = 0;
			this->image = new Image*[0];
			move = new Image(renderer, "textures/PacMan/pacman.bmp", this, 0, 0, 0);
			moveUp = new Image(renderer, "textures/PacMan/pacmanUp.bmp", this, 0, 0, 0);
			moveDown = new Image(renderer, "textures/PacMan/pacmanDown.bmp", this, 0, 0, 0);
			moveRight = new Image(renderer, "textures/PacMan/pacmanRight.bmp", this, 0, 0, 0);
			moveLeft = new Image(renderer, "textures/PacMan/pacmanLeft.bmp", this, 0, 0, 0);
			*/
		}
		else if (auto ghost = dynamic_cast<EnemyEntity*>(&(entities->at(i))))
		{
			display->addDrawable(ghost);
		}
	}

	

}

void PacManView::draw()
{

}
