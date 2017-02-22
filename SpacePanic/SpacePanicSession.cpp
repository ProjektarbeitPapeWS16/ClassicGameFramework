#include "SpacePanicSession.h"
#include "Stage.h"
#include "PlayerEntity.h"

SpacePanicSession::SpacePanicSession(SpacePanicModel* model, int defaultOxygen) : Session(2, 0), oxygen(defaultOxygen), defaultOxygen(defaultOxygen), model(model)
{
	
}

SpacePanicSession::SpacePanicSession(SpacePanicModel* model) : SpacePanicSession(model, 10000)
{
}

void SpacePanicSession::respawnIfPossible()
{
	PlayerEntity* player;
	if (getLevel() == nullptr || ((player = getStage()->getPlayer())->isDead() && player->getDeadSince() < getPassedTime() - 3 * 1000))
	{
		setLevel(new Stage(model, model->getStageFile(0), model->getMovementFile(0)));
	}
}

Stage* SpacePanicSession::getStage()
{
	return static_cast<Stage*>(getLevel());
}

void SpacePanicSession::resetOxygen()
{
	oxygen = defaultOxygen;
	creationTime = Config::currentTimeMillis();
}

int SpacePanicSession::getOxygen()
{
	int oxygen = defaultOxygen - (getPassedTime() / 1000) * 50;
	return oxygen < 0 ? 0 : oxygen;
}

void SpacePanicSession::setOxygen(int oxygen)
{
	this->oxygen = oxygen;
}
