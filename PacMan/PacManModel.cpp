#include "PacManModel.h"
#include "PlayerEntity.h"
#include "EngineView.h"
#include "EngineController.h"
#include "Drawable.h"
#include "Display.h"
#include "EnemyEntity.h"
#include "Physics.h"
#include "MySession.h"
#include "PhysicalObject.h"
#include "Entity.h"
#include "Level.h"
#include "EnemyEntity.h"
#include "WallEntity.h"
#include "DotEntity.h"
#include "EnergizerEntity.h"
#include "MyLevel.h"

#define AMP 3

PacManModel::PacManModel() : EngineModel()
{
	session = new MySession();
}

PacManModel::~PacManModel()
{
}


void PacManModel::initialization()
{
}

void PacManModel::nextIteration()
{
	static_cast<MySession*>(session)->nextIteration();
}


// Functions for the KeyListeners
void PacManModel::keyUpPress()
{
	static_cast<MyLevel*>(static_cast<PacManModel*>(EngineModel::getInstance())->getLevel())->getPacman()->request(PlayerEntity::MOVE_UP);
}

void PacManModel::keyDownPress()
{
	static_cast<MyLevel*>(static_cast<PacManModel*>(EngineModel::getInstance())->getLevel())->getPacman()->request(PlayerEntity::MOVE_DOWN);
}

void PacManModel::keyLeftPress()
{
	static_cast<MyLevel*>(static_cast<PacManModel*>(EngineModel::getInstance())->getLevel())->getPacman()->request(PlayerEntity::MOVE_LEFT);
}

void PacManModel::keyRightPress()
{
	static_cast<MyLevel*>(static_cast<PacManModel*>(EngineModel::getInstance())->getLevel())->getPacman()->request(PlayerEntity::MOVE_RIGHT);
}

void PacManModel::keyEscPress()
{
	EngineModel::getInstance()->shouldClose = true;
}
