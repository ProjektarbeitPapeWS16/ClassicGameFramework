#include "DK_Session.h"
#include "Physics.h"

DK_Session::DK_Session(DK_Model* model) // (std::vector<char*>* levelLayoutPaths, std::vector<char*>* uiLayoutPaths, int * highScores, GameConfig * config)
	: Session(this->INIT_LIVES, this->INIT_SCORE)
{
	this->model = model;
	this->bonus = INIT_BONUS;
	this->lifes = INIT_LIVES;
	this->score = INIT_SCORE;
	//this->uiLayoutPaths = uiLayoutPaths;
	//this->levelLayoutPaths = levelLayoutPaths;

	//this->highScores = highScores;
	//this->highScore = highScores[0]; // First place

	//if (levelLayoutPaths != nullptr && uiLayoutPaths != nullptr)
		// Init first level with default physics.
		this->level = new DK_Level(model, 1);// levelLayoutPaths->at(0), uiLayoutPaths->at(0), new Physics(), this->config);	
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
