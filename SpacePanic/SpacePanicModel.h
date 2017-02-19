#pragma once
#include "EngineModel.h"

class SpacePanicModel : public EngineModel
{
	
public:
	SpacePanicModel(Session* session);

	~SpacePanicModel() override;
	void initialization() override;
	void nextIteration() override;
};
