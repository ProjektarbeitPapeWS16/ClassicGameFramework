#pragma once
#include "Entity.h"
#include "Text.h"
#include "SpacePanicModel.h"

class GameOver : public Entity
{
	std::string lettersToShow;
	int countLettersShown = 0;
	Text text;
	SpacePanicModel* model;
public:
	GameOver(SpacePanicModel* model, const char* text, Font* font);
	bool isFinished() const;
	bool showNext();
	void reset();
	Image* getImage() override;

	int getWidth() override;
	int getHeight() override;
	int getPosX() override;
	int getPosY() override;
	void setPosition(int xPos, int yPos) override;
	void setPosX(int posX) override;
	void setPosY(int posY) override;
};
