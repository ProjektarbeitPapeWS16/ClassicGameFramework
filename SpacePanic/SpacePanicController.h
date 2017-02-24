#pragma once
#include "EngineController.h"
class SpacePanicModel;
class SpacePanicView;

class SpacePanicController : public EngineController
{
	SpacePanicModel* model;
public:
	SpacePanicController(SpacePanicView* view, SpacePanicModel* model);

	~SpacePanicController() override;
	//unsigned long cycles = 0L;
	void cycle() override;
};
