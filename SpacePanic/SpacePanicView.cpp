#include "SpacePanicView.h"
#include "Level.h"
#include "SpacePanicModel.h"
#include "Renderer.h"
#include "Display.h"
#include "Session.h"
#include "Entity.h"

SpacePanicView::SpacePanicView(SpacePanicModel* model)
	: EngineView(
		reinterpret_cast<EngineModel*>(model),
		new Display(),
		new Renderer(
			model->getConfig()->getWidth(),
			model->getConfig()->getHeight(),
			model->getConfig()->getTitle()
		)
	)
{
}

void SpacePanicView::draw()
{
	display->clearDrawables();

	auto level = model->getSession()->getLevel();

	if (level != nullptr)
	{
		//static_cast<Stage*>(level)->generateSortedEntities();
		auto entities = level->getEntities();

		for (auto i = 0; i < entities->size(); i++)
		{
			display->addDrawable(entities->at(i));
		}
	}
}
