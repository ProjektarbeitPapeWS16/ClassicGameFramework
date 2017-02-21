#include "SpacePanicModel.h"
#include "GameConfig.h"
#include "Stage.h"
#include "Session.h"
#include "SpacePanicSession.h"

SpacePanicModel::SpacePanicModel():
	EngineModel(nullptr, nullptr, nullptr),
	config(new GameConfig("Space Panic", 192, 256, 2, 8, 8)),
	stageFiles(new const char*[1] {
		"levels/stage1.txt"
	}),
	movementFiles(new const char*[1] {
		"levels/stage1_movement.txt"
	})
{
	setSession(new SpacePanicSession(this));
	//session->setLevel(new Stage(this, "levels/stage1.txt", "levels/stage1_movement.txt"));
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

const char* SpacePanicModel::getStageFile(int i) const
{
	return stageFiles[i];
}

const char* SpacePanicModel::getMovementFile(int i) const
{
	return movementFiles[i];
}

EngineModel* SpacePanicModel::super()
{
	return this;
}

//SpacePanicSession* SpacePanicModel::getSpacePanicSession()
//{
//	return static_cast<SpacePanicSession*>(getSession());
//}
