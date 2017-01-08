#pragma once
#include "EngineController.h"
class SpacePanicModel;
class SpacePanicView;

class SpacePanicController : public EngineController
{
public:
	SpacePanicController(SpacePanicView* view, SpacePanicModel* model);

	~SpacePanicController() override;
};
