#include "PacManView.h"
#include "PacManModel.h"
#include "Display.h"
#include "PlayerEntity.h"
#include "WallEntity.h"
#include "EnemyEntity.h"

PacManView::PacManView(PacManModel* model, Display* display, Renderer* renderer)
	: EngineView((EngineModel*)(model), display, renderer)
{
	Drawable* drawable = new WallEntity(renderer, new Boundaries(200, 300, 100, 100));
	display->addDrawable(drawable);

	drawable = new PlayerEntity(renderer);
	display->addDrawable(drawable);

}

void PacManView::draw()
{

}
