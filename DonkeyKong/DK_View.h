#pragma once
#include "EngineView.h"
#include "GameConfig.h"

class DK_Model;

// View class with customized draw function for DK
// TODO: Config needed? 
class DK_View : public EngineView
{
protected:
	GameConfig* config; // Derived from model.

	//DK_Model* model;
	// Display* display;
	// Renderer* renderer;
public:
	DK_View(DK_Model* model, Display* display, Renderer* renderer);	
	DK_View(DK_Model * model);

	void draw() override; // updates view
};
