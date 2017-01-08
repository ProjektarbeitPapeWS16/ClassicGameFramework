#include "EngineView.h"
#include "Renderer.h"
//#include <functional>
//#include <glfw3.h>

EngineView::EngineView(EngineModel* model, Display* display, Renderer* renderer): model(model),
                                                                                  display(display),
                                                                                  renderer(renderer)
{
}

EngineView::~EngineView()
{
}


void EngineView::update()
{
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	
	//TODO generate display
	renderer->render(this->display);
}
