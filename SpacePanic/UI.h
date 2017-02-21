#pragma once
#include "Entity.h"
#include <vector>
#include "Level.h"
#include "Font.h"
#include "Text.h"

class SpacePanicModel;
class Stage;
class GameConfig;

class UI
{
	SpacePanicModel* model;

	long currentOxygenLevel = 1000L;
	std::vector<Entity*>* entities;
	Font* defaultFont;
	Entity* titleEntity;
	Entity* oxygenLevel;
	Entity* score;
	Entity* lives;
public:
	UI(SpacePanicModel* model);
	void update();
	std::vector<Entity*>* getEntities() const;	
};
