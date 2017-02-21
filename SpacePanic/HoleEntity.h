#pragma once
#include "Entity.h"
#include "SpacePanicModel.h"

class HoleEntity : Entity
{
public:
	typedef enum
	{
		STAGE0,
		STAGE1,
		STAGE2,
		STAGE3
	} HoleState;

	HoleState state;

	HoleEntity(SpacePanicModel* model, Position position);

};
