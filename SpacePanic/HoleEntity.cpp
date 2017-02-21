#include "HoleEntity.h"
#include "GameConfig.h"

HoleEntity::HoleEntity(
	SpacePanicModel* model,
	Position position
):
	Entity(
		new Image*[0],
		0,
		true,
		new Boundaries(
			position.x,
			position.y,
			model->getConfig()->getRasterWidth() * 3,
			model->getConfig()->getRasterHeight()),
		false,
		0
	)
{

}
