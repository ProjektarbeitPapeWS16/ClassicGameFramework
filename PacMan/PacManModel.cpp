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
	blueGhost = new EnemyEntity(new Boundaries(200, 200, 14 * 3, 14 * 3));
	blueGhost->setTextures("textures/Ghosts/blueGhost/blueGhostUp1.bmp",
		"textures/Ghosts/blueGhost/blueGhostUp2.bmp",
		"textures/Ghosts/blueGhost/blueGhostDown1.bmp",
		"textures/Ghosts/blueGhost/blueGhostDown2.bmp",
		"textures/Ghosts/blueGhost/blueGhostRight1.bmp",
		"textures/Ghosts/blueGhost/blueGhostRight2.bmp",
		"textures/Ghosts/blueGhost/blueGhostLeft1.bmp",
		"textures/Ghosts/blueGhost/blueGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	blueGhost->request(EnemyEntity::MOVE_UP);
	redGhost = new EnemyEntity(new Boundaries(300, 200, 14 * 3, 14 * 3));
	redGhost->setTextures("textures/Ghosts/redGhost/redGhostUp1.bmp",
		"textures/Ghosts/redGhost/redGhostUp2.bmp",
		"textures/Ghosts/redGhost/redGhostDown1.bmp",
		"textures/Ghosts/redGhost/redGhostDown2.bmp",
		"textures/Ghosts/redGhost/redGhostRight1.bmp",
		"textures/Ghosts/redGhost/redGhostRight2.bmp",
		"textures/Ghosts/redGhost/redGhostLeft1.bmp",
		"textures/Ghosts/redGhost/redGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	orangeGhost = new EnemyEntity(new Boundaries(200, 300, 14 * 3, 14 * 3));
	orangeGhost->setTextures("textures/Ghosts/orangeGhost/orangeGhostUp1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostUp2.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostDown1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostDown2.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostRight1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostRight2.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostLeft1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	pinkGhost = new EnemyEntity(new Boundaries(300, 300, 14 * 3, 14 * 3));
	pinkGhost->setTextures("textures/Ghosts/pinkGhost/pinkGhostUp1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostUp2.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostDown1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostDown2.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostRight1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostRight2.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostLeft1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");

	entities->push_back(pacman);
	entities->push_back(blueGhost);
	entities->push_back(redGhost);
	entities->push_back(orangeGhost);
	entities->push_back(pinkGhost);

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
	
	slowit++;
	if (slowit % 7 == 0)
	{
		
		
		gamecounter++;
		gamecounter = gamecounter % 16;
		switch (gamecounter)
		{
		case  0: 
		case  1: 
		case  2: 
		case  3: 
		case  4: blueGhost->request(EnemyEntity::MOVE_RIGHT);	break;
		case  5: 
		case  6: 
		case  7: 
		case  8: blueGhost->request(EnemyEntity::MOVE_UP);		break;
		case  9: 
		case 10: 
		case 11: 
		case 12: blueGhost->request(EnemyEntity::MOVE_LEFT);	break;
		case 13:
		case 14:
		case 15: 
		default: blueGhost->request(EnemyEntity::MOVE_DOWN);	break;;
		}
		pacman->execute();
		handleCollisions();
	}
	blueGhost->execute();

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
				// if collides, has to take a step back
				pacman->stepBack();
				//pacman->request(PlayerEntity::NONE);
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

EnemyEntity* PacManModel::getRedGhost()
{
	return redGhost;
}

EnemyEntity* PacManModel::getOrangeGhost()
{
	return orangeGhost;
}

EnemyEntity* PacManModel::getPinkGhost()
{
	return pinkGhost;
}



// Kollisionshandler
void PacManModel::collisionPacGhost(PhysicalObject* collided) {
	//pacman->DEAD;
}