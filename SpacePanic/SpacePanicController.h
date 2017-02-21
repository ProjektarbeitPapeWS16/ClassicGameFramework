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
	void cycle() override;
};
