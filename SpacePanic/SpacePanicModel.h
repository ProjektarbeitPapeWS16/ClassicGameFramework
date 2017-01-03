#pragma once
#include "EngineModel.h"

class SpacePanicModel : public EngineModel
{
public:
	SpacePanicModel(Session& session, Physics& physics)
		: EngineModel(session, physics)
	{
	}
};
