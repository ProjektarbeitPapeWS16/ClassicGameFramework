#pragma once
#include "EngineModel.h"

class SpacePanicModel : public EngineModel
{
	
public:
	SpacePanicModel(Session* session)
		: EngineModel(session)
	{
		session->level.
	}

	~SpacePanicModel() override;
	void initialization() override;
	void nextIteration() override;
};
