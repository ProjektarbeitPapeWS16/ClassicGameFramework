#pragma once
#include "EngineModel.h"

class DonkeyKongModel : public EngineModel
{
	
public:
	DonkeyKongModel(Session* session);

	~DonkeyKongModel() override;
	void initialization() override;
	void nextIteration() override;
};
