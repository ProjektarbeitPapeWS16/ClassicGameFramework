#pragma once
#include "Session.h"
#include "SpacePanicModel.h"

class SpacePanicSession : public Session
{
	int oxygen;
	const int DEFAULT_OXYGEN = 100;
public:
	SpacePanicSession(SpacePanicModel* model);
	void respawnIfPossible();
	Stage* getStage();
	void resetOxygen();
	SpacePanicModel* model;
	int getOxygen();
	void setOxygen(int oxygen);
};
