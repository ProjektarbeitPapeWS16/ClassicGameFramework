#pragma once
#include "EngineController.h"
class DonkeyKongModel;
class DonkeyKongView;

class DonkeyKongController : public EngineController
{
public:
	DonkeyKongController(DonkeyKongView* view, DonkeyKongModel* model);

	~DonkeyKongController() override;
	void cycle() override;
};
