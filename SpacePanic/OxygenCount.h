#pragma once
#include "Entity.h"
#include "SpacePanicModel.h"
#include "Text.h"

class OxygenCount : public Entity
{
public:

	OxygenCount(SpacePanicModel* model);

	Image* getImage() override;
	~OxygenCount() override;
	SpacePanicModel* model;
	Text* text;
	int lastOxygenLevel = 0;
};
