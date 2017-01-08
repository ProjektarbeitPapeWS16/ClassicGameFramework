#pragma once

class Renderer;
class Display;
class EngineModel;

class EngineView
{
protected:
	EngineModel* model = nullptr;

public:
	Display* display = nullptr;
	Renderer* renderer = nullptr;
	EngineView( EngineModel* model,  Display* display,  Renderer* renderer);


	~EngineView();

	/// <summary>
	/// Updates the view components
	/// </summary>
	void update();

};

