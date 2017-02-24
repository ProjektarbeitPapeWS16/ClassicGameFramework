#include "OxygenCount.h"
#include "GameConfig.h"
#include "UI.h"

OxygenCount::OxygenCount(SpacePanicModel* model): Entity(new Image*[0], 0, false,

                                                         new Boundaries(model->getConfig()->getRasterWidth() * 10, model->getConfig()->getRasterHeight() * 1, 0, model->getConfig()->getRasterHeight()),

                                                         false, 0)
,text(nullptr), lastOxygenLevel(0), model(model)
{
}

Image* OxygenCount::getImage()
{
	auto currentOxygen = static_cast<SpacePanicSession*>(model->getSession())->getOxygen();

	if(!this->text || lastOxygenLevel != currentOxygen)
	{
		
		if(this->text)
		{
			delete this->text;
		}
		this->text = new Text(static_cast<Stage*>(model->getLevel())->getUI()->getDefaultFont(), std::to_string(currentOxygen).c_str(), new Position(boundaries->position.x, boundaries->position.y), model->getConfig()->getExternalFactor(), 255, 0, 0);
		this->boundaries->width = text->getWidth();
		this->boundaries->height = text->getHeight();
		this->lastOxygenLevel = currentOxygen;
	}

	return text->getImage();
}

OxygenCount::~OxygenCount()
{
	if(text)
	{
		delete text;
	}
}
