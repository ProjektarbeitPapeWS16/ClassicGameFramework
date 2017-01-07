#pragma once

#include "EngineModel.h"
#include "Renderer.h"


using namespace std;

class EngineView
{
protected:
	EngineModel model;

public:
	Display display;
	Renderer renderer;
	EngineView( EngineModel& model,  Display& display,  Renderer& renderer);

	

	~EngineView();

	/// <summary>
	/// Updates the view components
	/// </summary>
	void update();

};

