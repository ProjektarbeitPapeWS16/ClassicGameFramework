#include "DK_Model.h"

DK_Model::DK_Model(Session* session) : EngineModel()
{
}

DK_Model::~DK_Model()
{



}

void DK_Model::initialization()
{
}

void DK_Model::nextIteration()
{
}

Entity_Jumpman * DK_Model::getPlayer()
{
	
	Entity_Jumpman* player = static_cast<Level_25m*>(session->getLevel())->getPlayer();
	player->request(Entity_Jumpman::MOVE_UP);
}
	return nullptr;
}
