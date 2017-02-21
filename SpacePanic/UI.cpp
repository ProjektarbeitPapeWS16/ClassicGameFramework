#include "UI.h"
#include "SpacePanicModel.h"
#include "Text.h"
#include "Font.h"
#include "GameConfig.h"
#include <string>

UI::UI(SpacePanicModel* model) :
	model(model),
	entities(new std::vector<Entity*>()),
	defaultFont(new Font("fonts/normal/", 8, 8, 200, 80, 0)),
	titleEntity(new Text(defaultFont, "SPACE PANIC", new Position(
		model->getConfig()->getRasterWidth() * 6, 
			model->getConfig()->getRasterHeight() * 30), model->getConfig()->applyFactor(1), 255, 0, 0)),
	oxygenLevel(nullptr),//new OxygenLevelEntity()),
	score(nullptr),
	lives(nullptr)
{
	//GameConfig* config = model->getConfig();

}

void UI::update()
{
	if (oxygenLevel != nullptr)
	{
		delete oxygenLevel;
	}
	oxygenLevel = new Text(defaultFont, std::to_string(static_cast<SpacePanicSession*>(model->getSession())->getOxygen()).c_str(), new Position(
		model->getConfig()->getRasterWidth() * 8,
		model->getConfig()->getRasterHeight() * 28), model->getConfig()->getExternalFactor(), 255, 0, 0);

	if (score != nullptr)
	{
		delete score;
	}
	score = new Text(defaultFont, std::to_string(static_cast<SpacePanicSession*>(model->getSession())->getScore()).c_str(), new Position(
		model->getConfig()->getRasterWidth() * 8,
		model->getConfig()->getRasterHeight() * 1), model->getConfig()->getExternalFactor(), 255, 0, 0);

	if (lives != nullptr)
	{
		delete lives;
	}
	lives = new Text(defaultFont, std::to_string(static_cast<SpacePanicSession*>(model->getSession())->getLifes()).c_str(), new Position(
		model->getConfig()->getRasterWidth() * 1,
		model->getConfig()->getRasterHeight() * 1), model->getConfig()->getExternalFactor(), 255, 0, 0);


	entities->clear();
	entities->push_back(titleEntity);
	entities->push_back(oxygenLevel);
	entities->push_back(score);
	entities->push_back(lives);
}

std::vector<Entity*>* UI::getEntities() const
{
	return entities;
}
