#include "SpacePanicController.h"

#include "EngineModel.h"
#include "EngineView.h"

//set<Key> SpacePanicController::keys = set<Key>();


void   upPress()
{
}

void   upRelease()
{
}

void   downPress()
{
}

void   downRelease()
{
}

void  leftPress()
{
}

void  leftRelease()
{
}

void   rightPress()
{
}

void   rightRelease()
{
}

void escPress()
{
	EngineModel::gameloopShouldEnd = true;
}



SpacePanicController::SpacePanicController(SpacePanicView* view, SpacePanicModel* model)
	: EngineController(reinterpret_cast<EngineView*>(view), reinterpret_cast<EngineModel*>(model))
{
	this->model->getKeyPressedListeners()->insert_or_assign(256, new std::function<void()>(escPress));

	this->model->getKeyPressedListeners()->insert_or_assign(265, new std::function<void()>(upPress));
	this->model->getKeyPressedListeners()->insert_or_assign(264, new std::function<void()>(downPress));
	this->model->getKeyPressedListeners()->insert_or_assign(263, new std::function<void()>(leftPress));
	this->model->getKeyPressedListeners()->insert_or_assign(262, new std::function<void()>(rightPress));
 
	this->model->getKeyReleasedListeners()->insert_or_assign(265, new std::function<void()>(upRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(264, new std::function<void()>(downRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(263, new std::function<void()>(leftRelease));
	this->model->getKeyReleasedListeners()->insert_or_assign(262, new std::function<void()>(rightRelease));
}

void SpacePanicController::gameLoop()
{
	while (!EngineModel::gameloopShouldEnd)
	{
		this->view->update();
		//this->model->nextIteration();
	}
}

SpacePanicController::~SpacePanicController()
{
}
