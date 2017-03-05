#include "DK_Session.h"
#include "Physics.h"

DK_Session::DK_Session(std::vector<char*>* levelLayoutPaths, std::vector<char*>* uiLayoutPaths, int * highScores, GameConfig * config)
	: Session(this->INIT_LIVES, this->INIT_SCORE)
{
	this->config = config;
	this->bonus = INIT_BONUS;
	this->uiLayoutPaths = uiLayoutPaths;
	this->levelLayoutPaths = levelLayoutPaths;

	this->highScores = highScores;
	this->highScore = highScores[0]; // First place

	if (levelLayoutPaths != nullptr && uiLayoutPaths != nullptr)
	{
		// Init first level with default physics.
		this->level = new DK_Level(levelLayoutPaths->at(0), uiLayoutPaths->at(0), new Physics(), this->config);
	}
	
}

// HACK: Empty constructor for basic attributes.
DK_Session::DK_Session()
	: DK_Session(nullptr, nullptr, nullptr, nullptr)
{
}

void DK_Session::doEvent_Death()
{
}

void DK_Session::doEvent_nextLevel()
{
}

void DK_Session::increaseScore(int points)
{
}

void DK_Session::doEvent_TimePassed()
{
}

void DK_Session::doEvent_Reset()
{
}
