#pragma once
#include "EngineView.h"

class SpacePanicModel;

class SpacePanicView : public EngineView
{
public:
	SpacePanicView(SpacePanicModel* model, Display* display, Renderer* renderer);
	void draw() override;
};
