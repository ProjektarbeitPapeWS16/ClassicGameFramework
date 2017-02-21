#pragma once
#include "Entity.h"
class Image;

class EnergizerEntity : public Entity
{
public:
	EnergizerEntity(int xPos, int yPos);
	Image* getImage() override;
	~EnergizerEntity();

private:
	Image* helper;
};

