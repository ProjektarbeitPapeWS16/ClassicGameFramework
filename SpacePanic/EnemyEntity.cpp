#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(): Entity(nullptr, 5, false, new Boundaries(5, 5, 30, 30), true, 3)
{
}
