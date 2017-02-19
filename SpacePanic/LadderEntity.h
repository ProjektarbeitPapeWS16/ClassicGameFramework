#pragma once
#include "Entity.h"
#include "Image.h"
#include "GameConfig.h"

class LadderEntity : public Entity
{
public:

	LadderEntity(GameConfig* config, Position* position);
};
