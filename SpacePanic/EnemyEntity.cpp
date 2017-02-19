#include "EnemyEntity.h"
#include "GameConfig.h"
#include "Image.h"

EnemyEntity::EnemyEntity(GameConfig* config, Position* position) :
	Entity(new Image*[0], 5, false, new Boundaries(
		       position->x * config->getRasterWidth(),
		       position->y * config->getRasterHeight(),
		       config->getRasterWidth() * 2,
		       config->getRasterHeight() * 2
	       ), true, 3),
	state(LAUF_1)
{
	lauf1 = new Image("textures/enemy_lauf1.bmp", this, 200, 80, 0);
	lauf2 = new Image("textures/enemy_lauf2.bmp", this, 200, 80, 0);
}

void EnemyEntity::execute()
{
	switch (state)
	{
	case LAUF_1: 
		if (counter % 4 < 2)
		{
			state = LAUF_1;
		} else
		{
			state = LAUF_2;
		}
		break;
	case LAUF_2:
	default: 
		if (counter % 4 < 2)
		{
			state = LAUF_1;
		}
		else
		{
			state = LAUF_2;
		}
		break;
	}
	// TODO: do some move

	counter++;
}

Image* EnemyEntity::getImage()
{
	switch (state)
	{
	case LAUF_1: 
		return lauf1;
		break;
	case LAUF_2: 
	default: 
		return lauf2;
		break;
	}
}
