#include "PlayerEntity.h"
#include "Image.h"
#include "GameConfig.h"

PlayerEntity::PlayerEntity(GameConfig* config, Position* position):
	config(config),	
Entity(
		nullptr,
		10,
		false,
		new Boundaries(
			config->applyFactor(position->x),
			config->applyFactor(position->y),
			config->applyFactor(11),
			config->applyFactor(16)
		),
		true,
		30
	)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	moveRight1 = new Image("textures/player_run1_right.bmp", this, 200, 80, 0);
	moveRight2 = new Image("textures/player_run2_right.bmp", this, 200, 80, 0);
	moveLeft1 = new Image("textures/player_run1_left.bmp", this, 200, 80, 0);
	moveLeft2 = new Image("textures/player_run2_left.bmp", this, 200, 80, 0);
	climb1 = new Image("textures/player_climb1.bmp", this, 200, 80, 0);
	climb2 = new Image("textures/player_climb2.bmp", this, 200, 80, 0);
	dig1 = new Image("textur.bmp", this);
	dig2 = dig1;
	dead = dig1;
}

void PlayerEntity::request(Request request)
{
	lastRequest = request;
}

int PlayerEntity::schrittweite() const
{
	return config->getRasterWidth() / 2;
}

void PlayerEntity::execute()
{
	switch (lastRequest)
	{
	case MOVE_RIGHT:
		switch (state)
		{
		case DEAD: break;
		case MOVE_RIGHT_1:
			this->setPosX(this->getPosX() + schrittweite());
			state = MOVE_RIGHT_2;
			break;
		case MOVE_RIGHT_2:
			this->setPosX(this->getPosX() + schrittweite());
			state = MOVE_RIGHT_1;
			break;
		default:
			this->setPosX(this->getPosX() + schrittweite());
			state = MOVE_RIGHT_1;
			break;
		}

		break;
	case MOVE_LEFT:
		switch (state)
		{
		case DEAD: break;
		case MOVE_LEFT_1:
			this->setPosX(this->getPosX() - schrittweite());
			state = MOVE_LEFT_2;
			break;
		case MOVE_LEFT_2:
			this->setPosX(this->getPosX() - schrittweite());
			state = MOVE_LEFT_1;
			break;
		default:
			this->setPosX(this->getPosX() - schrittweite());
			state = MOVE_LEFT_1;
			break;
		}
		break;
	case MOVE_UP:
		switch (state)
		{
		case DEAD: break;
		case CLIMB_1:
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_2;
			break;
		case CLIMB_2:
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_1;
			break;
		default:
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_1;
			break;
		}
		break;
	case MOVE_DOWN:
		switch (state)
		{
		case DEAD: break;
		case CLIMB_1:
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_2;
			break;
		case CLIMB_2:
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_1;
			break;
		default:
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_1;
			break;
		}
		break;
	case DO_ACTION:
		switch (state)
		{
		case DEAD: break;
		case DIG_1:
			state = DIG_2;
			break;
		case DIG_2:
			state = DIG_1;
			break;
		default:
			state = DIG_1;
			break;
		}
		break;
	default: break;
	}
	lastRequest = NONE;
}

Image* PlayerEntity::getImage()
{
	switch (state)
	{
	case MOVE_RIGHT_1: return moveRight1;
	case MOVE_RIGHT_2: return moveRight2;
	case MOVE_LEFT_1: return moveLeft1;
	case MOVE_LEFT_2: return moveLeft2;
	case CLIMB_1: return climb1;
	case CLIMB_2: return climb2;
	case DIG_1: return dig1;
	case DIG_2: return dig2;
	default: return dead;
	}
}
