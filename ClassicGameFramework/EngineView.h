#pragma once

class Renderer;
class Display;
class EngineModel;

// View of MVC paradigm, for translating the information of a given model into graphics on the window.
class EngineView
{
protected:
	//static EngineView* instance;
	EngineModel* model = nullptr;

public:

	Display* display = nullptr;		// window area for rendering
	Renderer* renderer = nullptr;	// renders image information on display
	EngineView(EngineModel* model, Display* display, Renderer* renderer);

	//static EngineView* getInstance();

	virtual ~EngineView();

	virtual void draw() = 0; // updates view

	/// <summary>
	/// Updates the view components
	/// </summary>
	void update();
};
