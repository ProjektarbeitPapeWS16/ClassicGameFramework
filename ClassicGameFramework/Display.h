#pragma once
#include <vector>
#include <memory>

class Drawable;

class Display
{
	typedef std::shared_ptr<Drawable> drawable_ptr;
	std::vector<Drawable*>* drawables = new std::vector<Drawable*>();

public:
	std::vector<Drawable*>* getDrawables() const;
	void setDrawables(std::vector<Drawable*>* drawables);
	void addDrawable(Drawable* drawable) const;
	void removeDrawable(Drawable* drawable) const;
	void clearDrawables() const;
};
