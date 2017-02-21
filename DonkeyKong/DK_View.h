#pragma once
#include "EngineView.h"
#include "GameConfig.h"

class DK_Model;

class DK_View : public EngineView
{
public:
	DK_View(DK_Model* model, Display* display, Renderer* renderer);
	DK_View(DK_Model* model, Display* display, Renderer* renderer, DK_Config* config);
	void draw() override;
};
