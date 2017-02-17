#include "PacManModel.h"
#include "PlayerEntity.h"
#include "EngineView.h"
#include "EngineController.h"
#include "Drawable.h"
#include "Display.h"
#include "EnemyEntity.h"
#include "Physics.h"
#include "Session.h"
#include "PhysicalObject.h"
#include "Entity.h"
#include "Level.h"
#include "stdLevel.h"

PacManModel::PacManModel() : EngineModel()
{
	physic = new Physics();
	initialization();
}

void PacManModel::initialization()
{
	//pacman = static_cast<PlayerEntity*>(EngineView::getInstance()->display->getDrawables()->at(0));
	//ghost = static_cast<EnemyEntity*>(EngineView::getInstance()->display->getDrawables()->at(0));
	//ghost->execute();

	// Level erzeugen und Session sagen
	getSession()->setLevel(new StdLevel(100, 100, 1, 1, nullptr));

	physic->setLevel(this->getSession()->getLevel());

}

std::vector<Entity*> * PacManModel::getEntities()
{
	return entities;
}

PacManModel::~PacManModel()
{
}

void PacManModel::collisionPacGhost(PhysicalObject* collided) {
	//pacman->DEAD;
}


void PacManModel::nextIteration()
{
	// Collision detection
	if (std::vector<std::pair<PhysicalObject*, PhysicalObject*>> * collisionPairs = physic->checkCollisions())
	{

		for (unsigned int i = 0; i < (*collisionPairs).size(); i++)
		{
			Entity* ent = static_cast<Entity*>(collisionPairs->at(i).first);

			if (PlayerEntity* pacman = dynamic_cast<PlayerEntity*>(ent))
			{
				// pacman collides
				pacman->DEAD;
			}

		}
	}

	// Ghosts
	switch (state) 
	{
	case STATE_1:
		state = STATE_2;
		//ghost->request(MOVE_RIGHT);
		break;
	case STATE_2:
		state = STATE_3;
		break;
	case STATE_3:
		state = STATE_4;
		break;
	case STATE_4:
		state = STATE_5;
		break;
	case STATE_5:
		state = STATE_6;
		break;
	case STATE_6:
		state = STATE_1;
		break;
	}
}


// Functions for the KeyListeners
void PacManModel::keyUpPress()
{
	static_cast<PacManModel*>(EngineModel::getInstance())->getPacman()->request(PlayerEntity::MOVE_UP);
}

void PacManModel::keyDownPress()
{
	static_cast<PacManModel*>(EngineModel::getInstance())->getPacman()->request(PlayerEntity::MOVE_DOWN);
}

void PacManModel::keyLeftPress()
{
	static_cast<PacManModel*>(EngineModel::getInstance())->getPacman()->request(PlayerEntity::MOVE_LEFT);
}

void PacManModel::keyRightPress()
{
	static_cast<PacManModel*>(EngineModel::getInstance())->getPacman()->request(PlayerEntity::MOVE_RIGHT);
}

void PacManModel::keyEscPress()
{
	EngineController::getInstance()->closeWindow();
}

PlayerEntity* PacManModel::getPacman()
{
	return static_cast<StdLevel*>(getSession()->getLevel())->getPacman();
}