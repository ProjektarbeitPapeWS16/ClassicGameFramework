#include "EngineModel.h"
#include "Session.h"

#include "Entity_Jumpman.h"
#include "Image.h"
#include "Level.h"
#include "DK_Level.h"

const int CONST_SPEED = 10;
const int CONST_SIZE = 16;
Entity_Jumpman::Entity_Jumpman(Position position)
	: Entity(new Image*[0], CONST_SPEED, false,
		new Boundaries(
			position.x, position.y,
			16, 16 // CONST_SIZE, CONST_SIZE
		), false, 0
	)
{
	this->image[0] = new Image("textures/DK_Mario.bmp", this, 0, 0, 0);
	//this->image[0] = new Image("textures/player_run1_right.bmp", this, 200, 80, 0); //HACK
}