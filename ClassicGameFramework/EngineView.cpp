#include "EngineView.h"
#include "Renderer.h"
//#include <functional>
//#include <glfw3.h>

EngineView* EngineView::instance = nullptr;

EngineView::EngineView(EngineModel* model, Display* display, Renderer* renderer): model(model),
                                                                                  display(display),
                                                                                  renderer(renderer)
{
	instance = this;
}

EngineView* EngineView::getInstance()
{
	return instance;
}

EngineView::~EngineView()
{
}


void EngineView::update()
{
	draw();
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	
	//TODO generate display
	renderer->render(this->display);
}
