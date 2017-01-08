#pragma once
#include "EngineController.h"

class PacManView;
class PacManModel;

class PacManController : public EngineController
{
public:
	PacManController(PacManView *view, PacManModel* model);

	void gameLoop() override;
	~PacManController() override;
};
