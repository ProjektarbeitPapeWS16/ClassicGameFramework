#pragma once
#include "EngineModel.h"
class PacManModel : public EngineModel
{
public:
	PacManModel(Session* session);

	~PacManModel() override;
	void initialization() override;
	void nextIteration() override;
};

