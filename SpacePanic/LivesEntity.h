#pragma once
#include "Entity.h"
#include "SpacePanicModel.h"

class LivesEntity : public Entity
{
	SpacePanicModel* model;
	Image* lives0;
	Image* lives1;
	Image* lives2;
	Image* lives3;
public:
	LivesEntity(SpacePanicModel* model);
	Image* getImage() override;
	~LivesEntity() override;
};