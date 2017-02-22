#pragma once
#include "Session.h"
#include "SpacePanicModel.h"

class SpacePanicSession : public Session
{
	int oxygen;
	int defaultOxygen;
public:
	SpacePanicSession(SpacePanicModel* model, int defaultOxygen);
	SpacePanicSession(SpacePanicModel* model);
	void respawnIfPossible();
	Stage* getStage();
	void resetOxygen();
	SpacePanicModel* model;
	int getOxygen();
	void setOxygen(int oxygen);
};
