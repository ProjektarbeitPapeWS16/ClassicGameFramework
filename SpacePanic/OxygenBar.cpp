#include "OxygenBar.h"
#include "SpacePanicModel.h"
#include "Image.h"
#include "GameConfig.h"


OxygenBar::OxygenBar(SpacePanicModel* model) :
	Entity(
		new Image*[1]{new Image("textures/0lives.bmp", this)},
		0, false,

		new Boundaries(
			model->getConfig()->getRasterWidth(),
			model->getConfig()->getRasterHeight() * 27,
			0,
			model->getConfig()->getRasterHeight()),

		false, 0)
	, model(model)
{
}

Image* OxygenBar::getImage()
{
	auto maxWidth = (22.0 * model->getConfig()->getRasterWidth());
	auto actualWidth = (maxWidth / 2000.0) * (2000 - static_cast<SpacePanicSession*>(model->getSession())->getOxygen());

	boundaries->width = actualWidth;
	return __super::getImage();
}