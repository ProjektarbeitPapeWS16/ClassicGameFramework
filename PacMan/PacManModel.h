#pragma once
#include "E:\Joachim\Studium\Informatik Bachelor\Semester 5\Projektarbeit\Git\ClassicGameFramework\ClassicGameFramework\EngineModel.h"
class PacManModel : public EngineModel
{
public:
	PacManModel(Session* session);

	~PacManModel() override;
	void initialization() override;
	void nextIteration() override;
};

