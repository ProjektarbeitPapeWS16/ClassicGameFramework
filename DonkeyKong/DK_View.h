#pragma once
#include "EngineView.h"
#include "GameConfig.h"

class DK_Model;

class DK_View : public EngineView
{
private:
	DK_Model* model;
	GameConfig* config; // Derived from model.
	Display* display;
	Renderer* renderer;
public:
	DK_View(DK_Model* model, Display* display, Renderer* renderer);	
	DK_View(DK_Model * model);

	void draw() override; // updates view
};
