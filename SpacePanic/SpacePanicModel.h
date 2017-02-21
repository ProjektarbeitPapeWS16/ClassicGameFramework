#pragma once
#include "EngineModel.h"
#include "Stage.h"
class GameConfig;

class SpacePanicModel : public EngineModel
{
	GameConfig* config;
public:
	SpacePanicModel();
	~SpacePanicModel() override;
	
	void initialization() override;
	void nextIteration() override;
	GameConfig* getConfig() const;
};
