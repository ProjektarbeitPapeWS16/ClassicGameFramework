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
	Text* titleEntity;
	Entity* oxygenLevelEntity; //TODO
public:
	UI(SpacePanicModel* model);
	std::vector<Entity*>* getEntities() const;
	Entity* getOxygenLevelEntity();
	long getOxygenLevel();
	
};
