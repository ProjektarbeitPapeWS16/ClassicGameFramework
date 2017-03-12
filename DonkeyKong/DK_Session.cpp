#include "DK_Session.h"
#include "Physics.h"

DK_Session::DK_Session(DK_Model* model)
	: Session(this->INIT_LIVES, this->INIT_SCORE) // Note: Base class gets initialzed before derived class const variables.
{
	this->model = model;
	this->bonus = INIT_BONUS;
	this->lifes = INIT_LIVES;	// Base class gets
	this->score = INIT_SCORE;

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
