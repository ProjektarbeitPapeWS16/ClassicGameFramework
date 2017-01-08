#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(): Entity(nullptr, 10, false, new Boundaries(0, 0, 50, 50), true, 3)
{
}

