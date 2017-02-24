#pragma once
#include "Session.h"
#include "SpacePanicModel.h"

class SpacePanicSession : public Session
{
	int oxygen;
	int defaultOxygen;
	bool gameOver;
	long long gameOverSince;
public:
	SpacePanicSession(SpacePanicModel* model);
	Stage* nextStage() const;
	bool resetLevelIfNecessary();
	Level* getLevel();
	Stage* getStage();
	void resetLevel();
	void resetOxygen();
	SpacePanicModel* model;
	int getOxygen();
	void setOxygen(int oxygen);
};
