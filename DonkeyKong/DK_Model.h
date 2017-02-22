#pragma once
#include "EngineModel.h"

#include "Level_25m.h"
#include "Entity_Jumpman.h"

class DK_Model : public EngineModel
{
public:
	DK_Model(Session* session);

	~DK_Model() override;
	void initialization() override;
	void nextIteration() override;

	// Getter for player entity
	// Used by:		Controller
	Entity_Jumpman* getPlayer();
};
