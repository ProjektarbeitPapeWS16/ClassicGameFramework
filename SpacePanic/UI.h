#pragma once
#include "Entity.h"
#include <vector>
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
	Entity* oxygenLevel;
	Entity* score;
	Entity* lives;
	int oxygenLevelLast = -1;
	int scoreLast = -1;
	int livesLast = -1;
	Entity* top;
public:
	UI(SpacePanicModel* model);
	void update();
	std::vector<Entity*>* getEntities() const;	
};
