#pragma once
#include "EngineModel.h"
#include "Stage.h"
#include "SpacePanicSession.h"
class GameConfig;

class SpacePanicModel : public EngineModel
{
	GameConfig* config;
	const char** stageFiles;
	const char** movementFiles;
	EngineModel* super();
public:
	SpacePanicModel();
	~SpacePanicModel() override;
	
	void initialization() override;
	void nextIteration() override;
	GameConfig* getConfig() const;
	const char* getStageFile(int i) const;
	const char* getMovementFile(int i) const;
	
	//SpacePanicSession* getSpacePanicSession();
};
