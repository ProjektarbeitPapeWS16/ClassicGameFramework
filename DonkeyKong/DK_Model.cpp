#include "DK_Model.h"
#include "Physics.h"
#include "DK_Session.h"

// TODO: Put in custom DK_CONFIG
static const unsigned int DK_CELLSIZE = 8;		// Pixels used for grid cell subdivision in a level (for 8x8px tiles)
static const unsigned int DK_ROWCOUNT = 32;	// Amount of horizontal grid subdivisions
static const unsigned int DK_COLCOUNT = 28;	// Amount of vertical grid subdivisions
static const unsigned int DK_WIDTH = 224;		// Window width --	28 x 8px tiles
static const unsigned int DK_HEIGHT = 256;		// Window height --	32 x 8px tiles
static const char* DK_TITLE = "DONKEY KONG";	// Game Title

static const char* DK_LEVELLAYOUTPATH_1 = "..\\levels\\level_25m.txt"; // Relative PJ path to first level						
static const char* DK_UILAYOUTPATH_1 = "..\\levels\\level_ui.txt"; // Relative PJ path to ui layout for first level

std::vector<const char*>* DK_LEVELLAYOUTPATHS = (DK_LEVELLAYOUTPATH_1, nullptr); // HACK doesitwork?
std::vector<const char*>* DK_UILAYOUTPATHS = (DK_UILAYOUTPATH_1, nullptr); // HACK

// Constructor for custom session; and otherwise default values
DK_Model::DK_Model()
	: DK_Model(session, new GameConfig(DK_TITLE, DK_WIDTH, DK_HEIGHT, 3, DK_CELLSIZE, DK_CELLSIZE), DK_LEVELLAYOUTPATHS, DK_UILAYOUTPATHS, nullptr) // HACK
{
}

/* Main Constructor.
 * Notes: Creates no physics engine, which instead gets used within a level class.
 * @param session			Game-Session containing general game information to keep track of, like High Score or Lives left.
 * @param config			Game Configuration determining window size, pixel and grid dimensions, game title, etc.
 * @param levelLayoutPaths	VList of relative paths to the files containing interactive entity layout information for a level.
 * @param uiLayouPaths		VList of relative paths to the files containing UI entity layout information for a level.
 * @highscoreEntriesPath	Relative path to the file containing high score information.
 */
DK_Model::DK_Model(GameConfig* config, std::vector<const char*>* levelLayoutPaths, std::vector<const char*>* uiLayoutPaths, const char* highscoreEntriesPath)
{
	this->config = config;
	this->levelLayoutPaths = levelLayoutPaths;
	this->uiLayoutPaths = uiLayoutPaths;
	this->highscoreEntriesPath = highscoreEntriesPath;
	this->session = new DK_Session(levelLayoutPaths, uiLayoutPaths, highscoreEntriesPath, config);	//Create from parameters
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
	// 1. Check if session is still active.
	if (session != nullptr && session->getLives() <= 0)
	{
		// [1A] Start new session
		session = new DK_Session(this->levelLayoutPaths, this->uiLayoutPaths, nullptr, this->config, this->getPhysics());
	}
	// 2. Make session update for current cycle.
	
	// session->sessionLoop() TODO
	// session->getLevel()->gameLoop();
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

// Returns a level's current entities (both ui and interactive)
// Used by: View, for update()
std::vector<Entity*>* DK_Model::getDrawables() const
{
	return this->session->getLevel()->getEntities();
}
