#include "SpacePanicSession.h"
#include "Stage.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"

SpacePanicSession::SpacePanicSession(SpacePanicModel* model) :
	Session(2, 0), oxygen(2000), defaultOxygen(oxygen), model(model)
{
	level = new Stage(model, model->getStageFile(0));
}

Stage* SpacePanicSession::nextStage() const
{
	return model->getStage(0);
}

bool SpacePanicSession::resetLevelIfNecessary()
{
	Stage* stage = getStage();
	PlayerEntity* player = stage->getPlayer();

	if (gameOver)
	{
		// TODO?
		if(gameOverSince + 3 * 1000 < Config::currentTimeMillis())
		{
			level = model->getStage(0);
			getStage()->reset();
			resetOxygen();
			setLifes(2);
		}
		
	}
	else if (player->isDead() && player->getDeadSince() < getPassedTime() - 3 * 1000)
	{
		if (lifes-- > 0)
		{
			stage->reset();
		}
		else
		{
			stage->gameOver();
			gameOverSince = Config::currentTimeMillis();
			gameOver = true;
		}

		return true;
	}
	else {
		auto enemys = stage->getEnemys();
		int cnt = 0;
		for (int i = 0; i < enemys->size(); i++)
		{
			if(enemys->at(i)->getState() != EnemyEntity::DEAD)
			{
				cnt++;
				break;
			}
		}

		if(cnt == 0)
		{
			auto newStage = nextStage();
			level = newStage;
			newStage->reset();
		}
	}
	return false;
}

Level* SpacePanicSession::getLevel()
{
	if (!level)
	{
		level = new Stage(model, model->getStageFile(0));
	}

	return level;
}

Stage* SpacePanicSession::getStage()
{
	return static_cast<Stage*>(getLevel());
}

void SpacePanicSession::resetLevel()
{
	getStage()->reset();
}

void SpacePanicSession::resetOxygen()
{
	oxygen = defaultOxygen;
	creationTime = Config::currentTimeMillis();
}

int SpacePanicSession::getOxygen()
{
	int oxygen = defaultOxygen - (getPassedTime() / 1000) * 20;
	return oxygen < 0 ? 0 : oxygen;
}

void SpacePanicSession::setOxygen(int oxygen)
{
	this->oxygen = oxygen;
}
