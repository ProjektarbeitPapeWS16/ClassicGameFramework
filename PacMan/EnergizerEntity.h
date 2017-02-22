#pragma once
#include "Entity.h"
#include "Config.h"
class Image;

class EnergizerEntity : public Entity
{
public:
	EnergizerEntity(int xPos, int yPos);
	Image* getImage() override;
	~EnergizerEntity();

private:
	bool alter = false;
	__int64 timer = Config::currentTimeMillis();
	Image* ret;
	Image* helper;
	Image* none;
};

