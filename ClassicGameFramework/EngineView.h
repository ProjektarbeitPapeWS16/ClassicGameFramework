#pragma once

class Renderer;
class Display;
class EngineModel;

class EngineView
{
protected:
	//static EngineView* instance;
	EngineModel* model = nullptr;

public:

	Display* display = nullptr;
	Renderer* renderer = nullptr;
	EngineView(EngineModel* model, Display* display, Renderer* renderer);

	//static EngineView* getInstance();

	virtual ~EngineView();

	virtual void draw() = 0;

	/// <summary>
	/// Updates the view components
	/// </summary>
	void update();
};
