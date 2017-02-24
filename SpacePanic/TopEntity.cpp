#include "TopEntity.h"
#include "GameConfig.h"

TopEntity::TopEntity(SpacePanicModel* model):
	Entity(
		new Image*[1] {new Image("textures/top.bmp", this, 200, 80, 0)},
		0,
		false,
		new Boundaries(
			0,
			27 * model->getConfig()->getRasterHeight(),
			model->getConfig()->getRasterWidth() * model->getConfig()->getRasterColumnsCount(),
			model->getConfig()->getRasterHeight() * 5), false, 0)
{
}
