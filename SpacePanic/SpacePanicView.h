#pragma once
#include "EngineView.h"
#include "GameConfig.h"

class SpacePanicModel;

class SpacePanicView : public EngineView
{
public:
	SpacePanicView(SpacePanicModel* model, Display* display, Renderer* renderer);
	SpacePanicView(SpacePanicModel* model, Display* display, Renderer* renderer, GameConfig* config);
	void draw() override;
};
