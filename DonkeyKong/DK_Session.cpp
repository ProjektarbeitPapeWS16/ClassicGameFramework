#include "DK_Session.h"

DK_Session::DK_Session(char * levels, char * uiLayout, int * highScores, GameConfig * config, Physics* physics) :
	Session(this->INIT_LIVES, this->INIT_SCORE)
{
	this->bonus = INIT_BONUS;
	this->levels = levels;
	this->uiLayout = uiLayout;
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
