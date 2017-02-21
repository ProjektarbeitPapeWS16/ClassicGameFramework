#pragma once
#include "EngineModel.h"

class DK_Model : public EngineModel
{

public:
	DK_Model(Session* session);

	~DK_Model() override;
	void initialization() override;
	void nextIteration() override;
};
