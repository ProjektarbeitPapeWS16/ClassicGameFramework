#include "SpacePanicModel.h"
#include "GameConfig.h"
#include "Stage.h"
#include "Session.h"

SpacePanicModel::SpacePanicModel(): 
EngineModel(), 
config(new GameConfig("Space Panic", 192, 256, 2, 8, 8))
{
	session = new Session();
	session->setLevel(new Stage(this, "levels/stage1.txt", "levels/stage1_movement.txt"));

}

SpacePanicModel::~SpacePanicModel()
{

}

void SpacePanicModel::initialization()
{

}

void SpacePanicModel::nextIteration()
{

}

GameConfig* SpacePanicModel::getConfig() const
{
	return config;
}
