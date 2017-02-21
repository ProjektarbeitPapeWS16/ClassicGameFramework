#include "UI.h"
#include "SpacePanicModel.h"
#include "Text.h"
#include "Font.h"
#include "GameConfig.h"

UI::UI(SpacePanicModel* model) :
	model(model),
	entities(new std::vector<Entity*>()),
	defaultFont(new Font("fonts/normal/", 8, 8, 200, 80, 0)),
	titleEntity(new Text(model->getConfig(), defaultFont, "SPACE PANIC", new Position(6, 30), model->getConfig()->applyFactor(1), 255, 0, 0))
//,	oxygenLevelEntity(nullptr)//new OxygenLevelEntity())
{
	GameConfig* config = model->getConfig();

	entities->push_back(titleEntity);

}

std::vector<Entity*>* UI::getEntities() const
{
	return entities;
}

Entity* UI::getOxygenLevelEntity()
{
	return oxygenLevelEntity;
}

long UI::getOxygenLevel()
{
	return 0L;
}
