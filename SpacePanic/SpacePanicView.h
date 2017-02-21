#pragma once
#include "EngineView.h"
#include "GameConfig.h"

class SpacePanicModel;

class SpacePanicView : public EngineView
{
public:
	SpacePanicView(SpacePanicModel* model);
	void draw() override;
};
