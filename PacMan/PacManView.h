#pragma once
#include "EngineView.h"

class PacManModel;

class PacManView : public EngineView
{
public:
	PacManView(PacManModel* model);
	void draw() override;
};

