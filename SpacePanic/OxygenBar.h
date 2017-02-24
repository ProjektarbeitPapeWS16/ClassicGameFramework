#pragma once
#include "Entity.h"
#include "FloorEntity.h"

class OxygenBar : public Entity
{
public:
	SpacePanicModel* model;
	OxygenBar(SpacePanicModel* model);
	Image* getImage() override;
};
