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
	oxygenLevel(nullptr), //new OxygenLevelEntity()),
	score(nullptr),
	lives(nullptr)
{
}

void UI::update()
{
	SpacePanicSession* session = static_cast<SpacePanicSession*>(model->getSession());

	if (oxygenLevelLast != session->getOxygen())
	{
		if (oxygenLevel != nullptr)
		{
			delete oxygenLevel;
		}
		oxygenLevelLast = session->getOxygen();
		oxygenLevel = new Text(defaultFont, ("Oxygen " + std::to_string(oxygenLevelLast)).c_str(), new Position(
			                       model->getConfig()->getRasterWidth() * 8,
			                       model->getConfig()->getRasterHeight() * 28), model->getConfig()->getExternalFactor(), 255, 0, 0);
	}

	if (scoreLast != session->getScore())
	{
		if (score != nullptr)
		{
			delete score;
		}
		scoreLast = session->getScore();
		score = new Text(defaultFont, ("Score " + std::to_string(scoreLast)).c_str(), new Position(
			                 model->getConfig()->getRasterWidth() * 12,
			                 model->getConfig()->getRasterHeight() * 2), model->getConfig()->getExternalFactor(), 255, 0, 0);
	}

	if (livesLast != session->getLifes())
	{
		if (lives != nullptr)
		{
			delete lives;
		}
		livesLast = session->getLifes();
		lives = new Text(defaultFont, ("Lives " + std::to_string(livesLast)).c_str(), new Position(
			                 model->getConfig()->getRasterWidth() * 1,
			                 model->getConfig()->getRasterHeight() * 2), model->getConfig()->getExternalFactor(), 255, 0, 0);
	}

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
