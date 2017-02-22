#include "EnergizerEntity.h"
#include "Image.h"

EnergizerEntity::EnergizerEntity(int xPos, int yPos)
	: Entity(nullptr, 0, false, new Boundaries(xPos, yPos, 8*3, 8*3), false, 0)
{
	helper = new Image("textures/energizer.bmp", this, 0, 0, 0);
	none = new Image("thisTextureDoesntExist.bmp", this, 0, 0, 0);
	ret = helper;
}

Image* EnergizerEntity::getImage()
{
	if ((Config::currentTimeMillis() - timer) > 150)
	{
		timer = Config::currentTimeMillis();
		if (alter)
		{
			alter = false;
			ret = helper;
		}
		else
		{
			alter = true;
			ret = none;
		}
	}
	return ret;
}

EnergizerEntity::~EnergizerEntity()
{
	delete helper;
}
