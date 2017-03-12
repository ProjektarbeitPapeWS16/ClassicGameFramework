#pragma once
#include "Entity.h"
#include "Image.h"

class BonusEntity :
	public Entity
{
	Image *img;
public:
	BonusEntity();
	Image* getImage() override;
	~BonusEntity();
};

