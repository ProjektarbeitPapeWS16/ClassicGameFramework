#include "UI.h"
#include "SpacePanicModel.h"
#include "Text.h"
#include "Font.h"
#include "GameConfig.h"
#include <string>
#include "TopEntity.h"
#include "LivesEntity.h"
#include "OxygenCount.h"
#include "ScoreEntity.h"
#include "OxygenBar.h"

UI::UI(SpacePanicModel* model) :
	model(model),
	entities(new std::vector<Entity*>()),
	defaultFont(new Font("fonts/normal/", 8, 8, 200, 80, 0)),
	oxygenCount(new OxygenCount(model)),
	score(new ScoreEntity(model)),
	lives(new LivesEntity(model)),
	top(new TopEntity(model)),
	oxygenBar(new OxygenBar(model))
{
	entities->push_back(top);
	entities->push_back(score);
	entities->push_back(lives);
	entities->push_back(oxygenCount);
	entities->push_back(oxygenBar);
}


std::vector<Entity*>* UI::getEntities() const
{
	return entities;
}

UI::~UI()
{
	delete top;
	delete lives;
	delete score;
	delete oxygenCount;
	delete defaultFont;
	delete entities;
}

Font* UI::getDefaultFont() const
{
	return defaultFont;
}
