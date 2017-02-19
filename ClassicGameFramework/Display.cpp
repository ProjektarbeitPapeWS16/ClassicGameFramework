#include "Display.h"

std::vector<Drawable*>* Display::getDrawables() 
{
	return this->drawables;
}

void Display::setDrawables(std::vector<Drawable*>* drawables)
{
	delete this->drawables;
	this->drawables = drawables;
}

void Display::addDrawable(Drawable* drawable) 
{
	this->drawables->push_back(drawable);
}

void Display::removeDrawable(Drawable* drawable) 
{
	for (unsigned int i = 0; i < drawables->size(); i++)
	{
		if (drawables->at(i) == drawable)
		{
			drawables->erase(drawables->begin() + i);
			break;
		}
	}
}
