#include "DK_Model.h"
#include "Physics.h"
#include "DK_Session.h"
//#include "DK_Config.h"
#pragma once

// Constructor for default values
DK_Model::DK_Model() : DK_Model(new DK_Config())
{ 
}

/* Main Constructor.
 * Notes: Creates no physics engine, which instead gets used within the level class.
 * @param session			Game-Session containing general game information to keep track of, like High Score or Lives left.
 * @param config			Game Configuration determining window size, pixel and grid dimensions, game title, etc.
 * @param levelLayoutPaths	VList of relative paths to the files containing interactive entity layout information for a level.
 * @param uiLayouPaths		VList of relative paths to the files containing UI entity layout information for a level.
 * @highscoreEntriesPath	Relative path to the file containing high score information.
 */
DK_Model::DK_Model(DK_Config* config) // std::vector<const char*>* levelLayoutPaths, std::vector<const char*>* uiLayoutPaths, const char* highscoreEntriesPath
{
	this->config = config;
	this->timer = new Timer();
	this->session = new DK_Session(this);
}

DK_Model::~DK_Model()
{
}

// Unneeded: Done in constructor; all underlying classes are created through Model.
void DK_Model::initialization()
{
}

// Game loop for world simulation.
void DK_Model::nextIteration()
{
	if(timer->hasTickTimePassed())
	{
		// 1. Check session
	if (session != nullptr && session->getLives() <= 0)
	{
		// 1A	Session over? Start new session
		session = new DK_Session(this);
	} else 
		// 1B	Update session.
	{
		//session->update(); TODO
	}
	// 2. Update level
	/*
	 * - update entities
	 * - move player according to controller request.
	 */
	}
	
	
}


// Key input for climbing up a ladder.
void DK_Model::keyUpPress()
{
	// request(PlayerEntity::MOVE_UP);
}

// Key input for climbing down a ladder.
void DK_Model::keyDownPress()
{
	
}

// Key input for walking left.
void DK_Model::keyLeftPress()
{
	// check if obstacle left
	// then move left
}

// Key input for walking right.
void DK_Model::keyRightPress()
{
	// check if obstacle right
	// then move right
}

// Key input for jump.
void DK_Model::keySpacePress()
{
	// check player state
	// if on ground, change to jump state

}

// Key input for closing the game.
void DK_Model::keyEscPress()
{
	EngineModel::getInstance()->shouldClose = true;
}



// Getters:

	/*
	GameConfig * DK_Model::getConfig() const
	{
		return this->config;
	}

	// Returns vector with all relative paths for a level's entity layout
	const std::vector<char*> * DK_Model::getLevelLayoutPaths(int i) const
	{
		return this->levelLayoutPaths;
	}

	// Returns vector with all relative paths for a level's UI layout
	const std::vector<char*> * DK_Model::getUiLayoutPaths() const
	{
		return this->uiLayoutPaths;
	}

	const char * DK_Model::getHighscoreInfo() const
	{
		return this->highscoreEntriesPath;
	}
	*/

// Returns a level's current entities (both ui and interactive)
// Used by: View, for update()
std::vector<Entity*>* DK_Model::getDrawables() const
{
	return this->session->getLevel()->getEntities();
}
