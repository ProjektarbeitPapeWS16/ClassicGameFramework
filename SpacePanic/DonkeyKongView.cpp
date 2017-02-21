#include "DonkeyKongView.h"
#include "Display.h"
#include "PlayerEntity.h"
#include "Text.h"
#include "Font.h"
#include "Stage1.h"
#include "DonkeyKongModel.h"
#include "Session.h"

DonkeyKongView::DonkeyKongView(DonkeyKongModel* model, Display* display, Renderer* renderer, GameConfig* config)
	: EngineView(reinterpret_cast<EngineModel*>(model), display, renderer)
{
	//Font* font = new Font("fonts/normal/", 8, 8, 200, 80, 0);

	//Drawable* player = new PlayerEntity(config, new Position(5, 5));
	//Drawable* text = new Text(font, "HELLO WORLD 2017", new Position(config->applyFactor(5), config->applyFactor(5)), config->applyFactor(1), 255, 0, 0);
	//display->addDrawable(player);
	//display->addDrawable(text);

	Stage1* stage1 = new Stage1(config);
	std::vector<Entity*>* entities = stage1->getEntities();

	for (int i = 0; i < entities->size(); i++)
	{
		display->addDrawable(entities->at(i));
	}

	model->getSession()->setLevel(stage1);

}

void DonkeyKongView::draw()
{
	
}
