#pragma once
#include "Session.h"
#include "SpacePanicModel.h"

class SpacePanicSession : public Session
{
	int currentStage = 0;
	int oxygen;
	int defaultOxygen;
	bool gameOver;
	long long gameOverSince;
	bool paused;
	long long lastOxygenUpdate;
public:
	SpacePanicSession(SpacePanicModel* model);
	Stage* nextStage();
	void resetLifes();
	bool resetLevelIfNecessary();
	Level* getLevel();
	Stage* getStage();
	void resetLevel();
	void resetOxygen();
	void calcNext();
	bool oxygenIsCritical() const;
	SpacePanicModel* model;
	int getOxygen() const;
	void setOxygen(int oxygen);
};
