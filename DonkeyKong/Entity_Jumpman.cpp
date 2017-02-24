#include "EngineModel.h"
#include "Session.h"

#include "Entity_Jumpman.h"
#include "Image.h"
#include "GameConfig.h"
#include "Level.h"
#include "DK_Level.h"

const int CONST_SPEED = 10;
const int CONST_SIZE = 16;
Entity_Jumpman::Entity_Jumpman(Position * position)
	: Entity(new Image*[1], CONST_SPEED, false,
		new Boundaries(
			position->x, position->y,
			CONST_SIZE, CONST_SIZE
		), false, 0
	)
{
	this->image[0] = new Image("textures/DK_Mario.bmp", this, 0, 0, 0);
}