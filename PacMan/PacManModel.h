#pragma once
#include "EngineModel.h"

class PlayerEntity;
class EnemyEntity;
class PhysicalObject;

class PacManModel : public EngineModel
{
public:
	PacManModel();
	
	~PacManModel() override;

	void initialization() override;
	void nextIteration() override;

	// keys
	void static keyUpPress();
	void static keyDownPress();
	void static keyLeftPress();
	void static keyRightPress();
	void static keyEscPress();
	
};

