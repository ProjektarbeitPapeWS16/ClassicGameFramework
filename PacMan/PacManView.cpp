#include "PacManView.h"
#include "PacManModel.h"

PacManView::PacManView(PacManModel* model, Display* display, Renderer* renderer)
	: EngineView((EngineModel*)(model), display, renderer)
{
}
