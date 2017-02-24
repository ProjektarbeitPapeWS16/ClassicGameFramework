#include "DK_Model.h"
#include "Physics.h"
#include "EngineController.h"

/*
#include "EngineView.h"
#include "EngineController.h"
#include "Drawable.h"
#include "Display.h"
#include "Physics.h"
#include "Session.h"
#include "PhysicalObject.h"
#include "Entity.h"
#include "Level.h"
*/

// Empty constructor
DK_Model::DK_Model()
{
}

// Constructor for custom session
DK_Model::DK_Model(DK_Session* session) : EngineModel(new Physics(), session)
{
}

DK_Model::DK_Model(DK_Session * session, GameConfig * config, char ** levelFilepaths) : EngineModel(new Physics(), session)
{
	this->config = config;
	this->levelFilepaths = levelFilepaths;
}

DK_Model::~DK_Model()
{
}

// Unneeded: Done in constructor; all underlying classes are created through Model.
void DK_Model::initialization()
{
}

// Game loop
void DK_Model::nextIteration()
{
	if (session->getLives <= 0)
	{
		//session->
	}

	// session->getLevel()->gameLoop();
}


// KeyListener Events
void DK_Model::keyUpPress()
{
	// request(PlayerEntity::MOVE_UP);
}

void DK_Model::keyDownPress()
{
	
}

void DK_Model::keyLeftPress()
{
	// check if obstacle left
	// then move left
}

void DK_Model::keyRightPress()
{
	// check if obstacle right
	// then move right
}

void DK_Model::keySpacePress()
{
	// check player state
	// if on ground, change to jump state

}

void DK_Model::keyEscPress()
{
	EngineModel::getInstance()->shouldClose = true;
}



// Getters:

GameConfig * DK_Model::getConfig() const
{
	return this->config;
}

const char * DK_Model::getLevelLayout(int i) const
{
	return this->levelFilepaths[i];
}

const char * DK_Model::getUiLayout() const
{
	return this->uiLayoutFilepaths;
}

const char * DK_Model::getHighscoreInfo() const
{
	return nullptr;
}

std::vector<Entity*>* DK_Model::getDrawables() const
{
	return this->session->getLevel()->getEntities();
}
