#pragma once
#include "Entity.h"
#include "SpacePanicController.h"

class FloorEntity : public Entity
{
public:
	FloorEntity(SpacePanicModel* model);
	~FloorEntity();
};
