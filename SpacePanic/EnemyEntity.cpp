#include "EnemyEntity.h"
#include "GameConfig.h"

EnemyEntity::EnemyEntity(GameConfig* config, Position* position) : Entity(nullptr, 5, false, new Boundaries(
	position->x,
	position->y,
	config->applyFactor(1),
	config->applyFactor(1)
), true, 3)
{
}

void EnemyEntity::execute()
{
	// TODO: do some move
}
