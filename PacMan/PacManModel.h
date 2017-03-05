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
	static void keyUpPress();
	static void keyDownPress();
	static void keyLeftPress();
	static void keyRightPress();
	static void keyEscPress();
	
};

