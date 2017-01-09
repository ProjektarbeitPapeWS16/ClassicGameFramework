#include "SpacePanicView.h"
#include "Display.h"
#include "PlayerEntity.h"

SpacePanicView::SpacePanicView(SpacePanicModel* model, Display* display, Renderer* renderer)
	: EngineView((EngineModel*)(model), display, renderer)
{
	Drawable* drawable = new PlayerEntity(renderer);
	display->addDrawable(drawable);
	
}

void SpacePanicView::draw()
{
	
}
