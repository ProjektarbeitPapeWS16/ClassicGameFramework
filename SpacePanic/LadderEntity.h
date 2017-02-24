#pragma once
#include "Entity.h"
#include "Image.h"
#include "GameConfig.h"
#include "SpacePanicModel.h"

class LadderEntity : public Entity
{
public:

	LadderEntity(SpacePanicModel* model, Position* position);
};
