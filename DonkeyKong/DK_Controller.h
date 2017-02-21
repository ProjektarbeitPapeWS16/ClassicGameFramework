#pragma once
#include "EngineController.h"
class DK_Model;
class DK_View;

class DK_Controller : public EngineController
{
public:
	DK_Controller(DK_View* view, DK_Model* model);

	~DK_Controller() override;
	void cycle() override;
};
