#pragma once
#include <vector>

class Drawable;

class Display
{
	std::vector<Drawable*>* drawables = new std::vector<Drawable*>();
public:
	std::vector<Drawable*>* getDrawables() const;
	void setDrawables(std::vector<Drawable*>* drawables);
	void addDrawable(Drawable* drawable) const;
	void removeDrawable(Drawable* drawable) const;
	void clearDrawables() const;
};
