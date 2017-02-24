#include "FloorEntity.h"
#include "Image.h"
#include "SpacePanicModel.h"
#include "GameConfig.h"

FloorEntity::FloorEntity(SpacePanicModel* model) : Entity(
	new Image*[1]{new Image("textures/floor.bmp", this, 200, 80, 0)},
	0,
	true,
	new Boundaries(
		0,
		0,
		model->getConfig()->getRasterColumnsCount() * model->getConfig()->getRasterWidth(),
		model->getConfig()->getRasterHeight() * 4),
	false,
	0)
{

}

FloorEntity::~FloorEntity()
{
}
