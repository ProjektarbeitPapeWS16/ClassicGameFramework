#pragma once
#include "EngineModel.h"
#include "Stage.h"
#include "SpacePanicSession.h"
class GameConfig;

class SpacePanicModel : public EngineModel
{
	GameConfig* config;
	std::vector<const char*> stageFiles;
	std::map<long, Stage*> stages;
	typedef EngineModel super;
public:

	SpacePanicModel();
	Stage* getStage(int id);
	~SpacePanicModel() override;
	
	void initialization() override;
	static unsigned long long lastFrameDrawn;
	static long timePerCycle;
	void nextIteration() override;
	GameConfig* getConfig() const;
	const char* getStageFile(int i) const;
	//SpacePanicSession* getSpacePanicSession();
};
