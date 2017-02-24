#pragma once
#include "EngineView.h"
#include "GameConfig.h"

class DonkeyKongModel;

class DonkeyKongView : public EngineView
{
public:
	DonkeyKongView(DonkeyKongModel* model, Display* display, Renderer* renderer);
	DonkeyKongView(DonkeyKongModel* model, Display* display, Renderer* renderer, GameConfig* config);
	void draw() override;
};
