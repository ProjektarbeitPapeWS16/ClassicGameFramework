#include "WallEntity.h"

WallEntity::WallEntity(): Entity(nullptr, 0, true, new Boundaries(3, 3, 30, 30), false, 0)
{
}
