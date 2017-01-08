#pragma once
#include "E:\Joachim\Studium\Informatik Bachelor\Semester 5\Projektarbeit\Git\ClassicGameFramework\ClassicGameFramework\EngineView.h"
class PacManModel;

class PacManView : public EngineView
{
public:
	PacManView(PacManModel* model, Display* display, Renderer* renderer);
};

