#include "SpacePanicModel.h"
#include "GameConfig.h"
#include "Stage.h"
#include "Session.h"
#include "SpacePanicSession.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"

SpacePanicModel::SpacePanicModel():
	EngineModel(),
	config(new GameConfig("Space Panic", 192, 256, 2, 8, 8))
//stage1(new Stage(this, getStageFile(1)))
{
	stageFiles.push_back("levels/stage1.txt");
	session = new SpacePanicSession(this);
}

Stage* SpacePanicModel::getStage(int id)
{
	if(stages.find(id) == stages.end())
	{
		if(id >= stageFiles.size())
		{
			return nullptr;
		} else
		{
			Stage* stage = new Stage(this, getStageFile(id));
			stages.insert_or_assign(id, stage);
			return stage;
		}
	} else
	{
		return stages.at(id);
	}
}

SpacePanicModel::~SpacePanicModel()
{
}

void SpacePanicModel::initialization()
{
}

unsigned long long SpacePanicModel::lastFrameDrawn = 0L;
long SpacePanicModel::timePerCycle = 0L;

void SpacePanicModel::nextIteration()
{
	auto currentTime = Config::currentTimeMillis();
	timePerCycle = currentTime - lastFrameDrawn;
	if (lastFrameDrawn + (1.0 / 10.0) * 1000.0 - timePerCycle > currentTime)
	{
		return;
	}
	lastFrameDrawn = currentTime;

	auto session = static_cast<SpacePanicSession*>(this->session);
	bool reset = session->resetLevelIfNecessary();

	session->calcNext();
	
	auto player = session->getStage()->getPlayer();
	if (player != nullptr)
	{
		player->execute();
	}

	auto enemys = session->getStage()->getEnemys();
	for (auto i = 0; i < enemys->size(); i++)
	{
		enemys->at(i)->execute();
	}

	delete session->getStage()->getCollisions();
}

GameConfig* SpacePanicModel::getConfig() const
{
	return config;
}

const char* SpacePanicModel::getStageFile(int i) const
{
	return stageFiles[i];
}
