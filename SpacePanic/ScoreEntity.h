#pragma once
#include "Entity.h"
#include "SpacePanicModel.h"
#include "Text.h"

class ScoreEntity : public Entity
{
public:
	ScoreEntity(SpacePanicModel* model);


	Image* getImage() override;
	~ScoreEntity() override;
	SpacePanicModel* model;
	int lastScore;
	Text* text;
};
