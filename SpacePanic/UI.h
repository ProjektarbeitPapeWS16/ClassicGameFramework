#pragma once
#include "Entity.h"
#include <vector>
#include "GameOver.h"
class Font;
class Text;
class TopEntity;

class SpacePanicModel;
class Stage;
class GameConfig;

class UI
{
	SpacePanicModel* model;

	long currentOxygenLevel = 1000L;
	std::vector<Entity*>* entities;
	Font* defaultFont;
	Entity* oxygenCount;
	Entity* score;
	Entity* lives;
	int oxygenLevelLast = -1;
	int scoreLast = -1;
	int livesLast = -1;
	Entity* top;
	Entity* oxygenBar;
	GameOver* gameOver;
public:
	UI(SpacePanicModel* model);
	void reset() const;
	std::vector<Entity*>* getEntities() const;	
	~UI();
	Font* getDefaultFont() const;
	void showGameOver() const;
};
