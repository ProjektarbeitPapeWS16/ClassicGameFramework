#include "SpacePanicView.h"
#include "Display.h"
#include "PlayerEntity.h"

SpacePanicView::SpacePanicView(SpacePanicModel* model, Display* display, Renderer* renderer, GameConfig* config)
	: EngineView((EngineModel*)(model), display, renderer)
{
	Drawable* drawable = new PlayerEntity(config, new Position(15, 15));
	display->addDrawable(drawable);
	
}

void SpacePanicView::draw()
{
	
}
