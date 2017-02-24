#include "ScoreEntity.h"
#include "GameConfig.h"
#include "UI.h"

ScoreEntity::ScoreEntity(SpacePanicModel* model):
	Entity(new Image*[0], 0, false,

		new Boundaries(model->getConfig()->getRasterWidth() * 5, model->getConfig()->getRasterHeight() * 29, 0, model->getConfig()->getRasterHeight()),

		false, 0)
	, text(nullptr), lastScore(0), model(model)
{
}


Image* ScoreEntity::getImage()
{
	auto currentScore = static_cast<SpacePanicSession*>(model->getSession())->getScore();

	if (!this->text || lastScore != currentScore)
	{

		if (this->text)
		{
			delete this->text;
		}
		this->text = new Text(static_cast<Stage*>(model->getLevel())->getUI()->getDefaultFont(), std::to_string(currentScore).c_str(), new Position(boundaries->position.x, boundaries->position.y), model->getConfig()->getExternalFactor(), 0, 255, 255);
		this->boundaries->width = text->getWidth();
		this->boundaries->height = text->getHeight();
		this->lastScore = currentScore;
	}

	return text->getImage();
}

ScoreEntity::~ScoreEntity()
{
	if (text)
	{
		delete text;
	}

}
