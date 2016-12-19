#pragma once
#include <vector>
#include "Drawable.h"

class Display
{
	std::vector<Drawable> drawables;

public:
	std::vector<Drawable> getDrawables();
	void setDrawables(std::vector<Drawable> drawables);
	void addDrawable(Drawable drawable);
	void removeDrawable(Drawable drawable);
};
