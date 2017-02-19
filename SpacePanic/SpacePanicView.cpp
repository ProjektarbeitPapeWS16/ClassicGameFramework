#include "SpacePanicView.h"
#include "Display.h"
#include "PlayerEntity.h"
#include "Text.h"
#include "Font.h"

SpacePanicView::SpacePanicView(SpacePanicModel* model, Display* display, Renderer* renderer, GameConfig* config)
	: EngineView(reinterpret_cast<EngineModel*>(model), display, renderer)
{
	Font* font = new Font("fonts/normal/", 8, 8, 200, 80, 0);

	Drawable* player = new PlayerEntity(config, new Position(5, 5));
	Drawable* text = new Text(font, "HELLO WORLD 2017", new Position(config->applyFactor(5), config->applyFactor(5)), config->applyFactor(1), 255, 0, 0);
	display->addDrawable(player);
	display->addDrawable(text);
}

void SpacePanicView::draw()
{
	
}
