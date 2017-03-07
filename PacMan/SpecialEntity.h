#pragma once
#include "Entity.h"

class SpecialEntity :	public Entity
{
private:
	Image *img;
public:
	SpecialEntity(int);
	~SpecialEntity();
	Image* getImage() override;
};

