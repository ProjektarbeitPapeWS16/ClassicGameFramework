#include "LadderEntity.h"

LadderEntity::LadderEntity(SpacePanicModel* model, Position* position): Entity(
	new Image*[1] {
		new Image("textures/ladder.bmp", this, 200, 80, 0)
	}
	, 0, false, new Boundaries(
		position->x * model->getConfig()->getRasterWidth(),
		position->y * model->getConfig()->getRasterHeight(),
		model->getConfig()->getRasterWidth(),
		model->getConfig()->getRasterHeight()
	), false, 0)
{
}
