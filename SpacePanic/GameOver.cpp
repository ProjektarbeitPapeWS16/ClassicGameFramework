#include "GameOver.h"
#include "GameConfig.h"


GameOver::GameOver(SpacePanicModel* model, const char* text, Font* font):
	Entity(new Image*[0], 0, false,
	       new Boundaries(7 * model->getConfig()->getRasterWidth(),
	                      15 * model->getConfig()->getRasterHeight(),
	                      0,
	                      0),
	       false, 0),
	lettersToShow(std::string(text)),
	text(Text(font, "", new Position(boundaries->position.x, boundaries->position.y), Text::CENTER, model->getConfig()->getExternalFactor(), 255, 0, 0, 0, 0, 0)),
	model(model)
{
}

bool GameOver::isFinished() const
{
	return countLettersShown >= lettersToShow.length();
}

bool GameOver::showNext()
{
	if (isFinished())
	{
		return true;
	}

	text.setText(lettersToShow.substr(0, ++countLettersShown).c_str());

	return isFinished();
}

void GameOver::reset()
{
	countLettersShown = 0;
	text.setText("");
}

Image* GameOver::getImage()
{
	return text.getImage();
}

int GameOver::getWidth()
{
	return text.getWidth();
}

int GameOver::getHeight()
{
	return text.getHeight();
}

int GameOver::getPosX()
{
	return text.getPosX();
}

int GameOver::getPosY()
{
	return text.getPosY();
}

void GameOver::setPosition(int xPos, int yPos)
{
	text.setPosition(xPos, yPos);
}

void GameOver::setPosX(int posX)
{
	text.setPosX(posX);
}

void GameOver::setPosY(int posY)
{
	text.setPosY(posY);
}
