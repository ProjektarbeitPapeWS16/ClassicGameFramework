#pragma once
#include "Entity.h"
class DotEntity :
	public Entity
{
public:
	DotEntity(int xPos, int yPos);
	Image* getImage() override;
	~DotEntity();

private: 
	Image* helper;
};

