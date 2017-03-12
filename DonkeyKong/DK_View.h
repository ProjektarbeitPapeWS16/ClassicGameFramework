#pragma once
#include "EngineView.h"

class DK_Model;

// View class with customized draw function for DK
class DK_View : public EngineView
{
public:
	//explicit DK_View(DK_Model* model, Display* display, Renderer* renderer);	
	explicit DK_View(DK_Model * model);

	void draw() override; // updates view
};
