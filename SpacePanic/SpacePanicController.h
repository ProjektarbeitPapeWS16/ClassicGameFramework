#pragma once
#include "EngineController.h"
#include "Action.h"
//#include <set>

class SpacePanicModel;
class SpacePanicView;

class SpacePanicController : public EngineController
{
	
public:

	//static set<Key> keys;
	SpacePanicController(const SpacePanicView& view, const SpacePanicModel& model);

	void gameLoop() override;
	~SpacePanicController() override;
	
};
