#include "SpacePanicSession.h"
#include "Stage.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"

SpacePanicSession::SpacePanicSession(SpacePanicModel* model) :
	Session(2, 0), oxygen(2000), defaultOxygen(oxygen), model(model)
{
	level = new Stage(model, model->getStageFile(currentStage));
}

Stage* SpacePanicSession::nextStage()
{
	Stage* stage = model->getStage(currentStage+1);
	if(!stage)
	{
		return getStage();
	} else
	{
		currentStage++;
		return stage;
	}
}

void SpacePanicSession::resetLifes()
{
	setLifes(defaultLifes);
}

bool SpacePanicSession::resetLevelIfNecessary()
{
	Stage* stage = getStage();
	PlayerEntity* player = stage->getPlayer();

	if(player->isDead())
	{
		paused = true;
	}

	if (gameOver)
	{
		
		if(gameOverSince + 5 * 1000 < Config::currentTimeMillis())
		{
			level = nextStage();
			resetLevel();
			resetOxygen();
			resetLifes();
			gameOver = false;
		} else
		{
			stage->showGameOver();
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
	paused = false;
}

void SpacePanicSession::calcNext()
{
	if(gameOver || paused)
	{
		return;
	}

	if (lastOxygenUpdate + 1000 < Config::currentTimeMillis()) {
		lastOxygenUpdate = Config::currentTimeMillis();

		if (this->oxygen > 0)
		{
			this->oxygen -= 20;
		}
		if (this->oxygen < 0)
		{
			this->oxygen = 0;
		}
	}
}

bool SpacePanicSession::oxygenIsCritical() const
{
	return oxygen < 500;
}

int SpacePanicSession::getOxygen() const
{
	return oxygen;
}

void SpacePanicSession::setOxygen(int oxygen)
{
	this->oxygen = oxygen;
}
