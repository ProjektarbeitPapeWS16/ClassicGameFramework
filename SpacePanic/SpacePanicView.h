#pragma once
#include "EngineView.h"
#include "SpacePanicModel.h"

class SpacePanicView : public EngineView
{
public:
	SpacePanicView( SpacePanicModel& model,  Display& display,  Renderer& renderer);
};
