#pragma once
#include <vector>

class Drawable;

class Display
{
	std::vector<Drawable*>* drawables = new std::vector<Drawable*>();

public:
	std::vector<Drawable*>* getDrawables() ;
	void setDrawables(std::vector<Drawable*>* drawables);
	void addDrawable(Drawable* drawable) ;
	void removeDrawable(Drawable* drawable) ;
};
