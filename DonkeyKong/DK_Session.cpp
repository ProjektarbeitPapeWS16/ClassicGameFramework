#include "DK_Session.h"

DK_Session::DK_Session(std::vector<char*>* levelLayoutPaths, std::vector<char*>* uiLayoutPaths, int * highScores, GameConfig * config, Physics * physics) :
	Session(this->INIT_LIVES, this->INIT_SCORE)
{
	this->bonus = INIT_BONUS;
	this->uiLayoutPaths = uiLayoutPaths;
	this->levelLayoutPaths = levelLayoutPaths;
	this->highScores = highScores;
	this->highScore = highScores[0];
}

// Empty constructor for basic attributes.
DK_Session::DK_Session()
{
}

DK_Level* DK_Session::getLevel()
{
	return this->level;
}
