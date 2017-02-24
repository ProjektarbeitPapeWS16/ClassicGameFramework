#pragma once
#include "EngineModel.h"
#include "Stage.h"
#include "SpacePanicSession.h"
class GameConfig;

class SpacePanicModel : public EngineModel
{
	GameConfig* config;
	const char** stageFiles;
	Stage* stage0;
	typedef EngineModel super;
public:
	SpacePanicModel();
	Stage* getStage(int id) const;
	~SpacePanicModel() override;
	
	void initialization() override;
	static unsigned long long lastFrameDrawn;
	static long timePerCycle;
	void nextIteration() override;
	GameConfig* getConfig() const;
	const char* getStageFile(int i) const;
	//SpacePanicSession* getSpacePanicSession();
};
