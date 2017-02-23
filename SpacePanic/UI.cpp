#include "UI.h"
#include "SpacePanicModel.h"
#include "Text.h"
#include "Font.h"
#include "GameConfig.h"
#include <string>
#include "TopEntity.h"
#include "LivesEntity.h"

UI::UI(SpacePanicModel* model) :
	model(model),
	entities(new std::vector<Entity*>()),
	defaultFont(new Font("fonts/normal/", 8, 8, 200, 80, 0)),
	oxygenLevel(nullptr),
	score(nullptr),
	lives(new LivesEntity(model))
{
	top = new TopEntity(model);
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
		oxygenLevel = new Text(defaultFont, std::to_string(oxygenLevelLast).c_str(), new Position(
			model->getConfig()->getRasterWidth() * 10,
			model->getConfig()->getRasterHeight() * 1), model->getConfig()->getExternalFactor(), 255, 0, 0);

		
	}

	if (scoreLast != session->getScore())
	{
		if (score != nullptr)
		{
			delete score;
		}
		scoreLast = session->getScore();
		score = new Text(defaultFont, (std::to_string(scoreLast)).c_str(), new Position(
			                 model->getConfig()->getRasterWidth() * 5,
			                 model->getConfig()->getRasterHeight() * 29), model->getConfig()->getExternalFactor(), 0, 255, 255);
	}

	if (livesLast != session->getLifes())
	{
		if (lives != nullptr)
		{
			delete lives;
		}
		livesLast = session->getLifes();
		lives = new Text(defaultFont, (std::to_string(livesLast) + " Lives").c_str(), new Position(
			                 model->getConfig()->getRasterWidth() * 1,
			                 model->getConfig()->getRasterHeight() * 1), 1, 255, 0, 0);
	}

	entities->clear();
	entities->push_back(top);
	entities->push_back(oxygenLevel);
	entities->push_back(score);
	entities->push_back(lives);
}

std::vector<Entity*>* UI::getEntities() const
{
	return entities;
}
