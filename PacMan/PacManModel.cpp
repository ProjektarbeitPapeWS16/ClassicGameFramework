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
#include "EnemyEntity.h"

PacManModel::PacManModel() : EngineModel()
{
	//physic = new Physics();
	session = new Session();
	level = new Level(100, 100, 1, 1, nullptr);

	entities = new std::vector<Entity*>();
	pacman = new PlayerEntity();
	blueGhost = new EnemyEntity();
	entities->push_back(pacman);
	entities->push_back(blueGhost);

	//physic->setLevel(level);
	session->setLevel(level);
	level->setEntities(entities);
}

PacManModel::~PacManModel()
{
}



void PacManModel::initialization()
{
	// Done in Constructor
}

void PacManModel::nextIteration()
{
	handleCollisions();

	// Ghosts
	//Level* level = getSession()->getLevel();
	//auto ghost = static_cast<StdLevel>(level)->getBlueGhost();
	switch (state) 
	{
	case STATE_1:
		state = STATE_2;
		blueGhost->request(EnemyEntity::MOVE_RIGHT);
		break;
	case STATE_2:
		state = STATE_3;
		blueGhost->request(EnemyEntity::MOVE_RIGHT);
		break;
	case STATE_3:
		state = STATE_4;
		blueGhost->request(EnemyEntity::MOVE_UP);
		break;
	case STATE_4:
		state = STATE_5;
		blueGhost->request(EnemyEntity::MOVE_UP);
		break;
	case STATE_5:
		state = STATE_6;
		blueGhost->request(EnemyEntity::MOVE_LEFT);
		break;
	case STATE_6:
		state = STATE_1;
		blueGhost->request(EnemyEntity::MOVE_LEFT);
		break;
	}
}


void PacManModel::handleCollisions()
{
	// TODO entities in PhysicalObjects casten, hier selber machen statt von level beziehen
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>> * collisionPairs = physic->checkCollisions(level->getPhysicalObjects());

	// Collision detection
	if (collisionPairs)
	{
		for (unsigned int i = 0; i < (*collisionPairs).size(); i++)
		{
			Entity* first = static_cast<Entity*>(collisionPairs->at(i).first);
			Entity* second = static_cast<Entity*>(collisionPairs->at(i).second);

			if (PlayerEntity* pacman = dynamic_cast<PlayerEntity*>(first))
			{
				// pacman collides
				pacman->request(PlayerEntity::NONE);
			}
		}
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



// getter
PlayerEntity* PacManModel::getPacman()
{
	return pacman;
}

EnemyEntity* PacManModel::getBlueGhost()
{
	return blueGhost;
}



// Kollisionshandler
void PacManModel::collisionPacGhost(PhysicalObject* collided) {
	//pacman->DEAD;
}