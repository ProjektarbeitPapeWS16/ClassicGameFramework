#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Image.h"
#include "GameConfig.h"
#include "EngineModel.h"
#include "Session.h"
#include "Level.h"
#include "Stage.h"

PlayerEntity::PlayerEntity(SpacePanicModel* model, Position* position):
	Entity(
		nullptr,
		10,
		false,
		new Boundaries(
			position->x * model->getConfig()->getRasterWidth(),
			position->y * model->getConfig()->getRasterHeight(),
			model->getConfig()->getRasterWidth() * 2,
			model->getConfig()->getRasterHeight() * 2
		),
		true,
		30
	),
	config(model->getConfig()),
	model(model)
{
	this->imageCount = 0;
	this->image = new Image*[0];
	moveRight1 = new Image("textures/player_run1_right.bmp", this, 200, 80, 0);
	moveRight2 = new Image("textures/player_run2_right.bmp", this, 200, 80, 0);
	moveLeft1 = new Image("textures/player_run1_left.bmp", this, 200, 80, 0);
	moveLeft2 = new Image("textures/player_run2_left.bmp", this, 200, 80, 0);
	climb1 = new Image("textures/player_climb1.bmp", this, 200, 80, 0);
	climb2 = new Image("textures/player_climb2.bmp", this, 200, 80, 0);
	digLeft1 = new Image("textures/player_dig1_left.bmp", this, 200, 80, 0);
	digLeft2 = new Image("textures/player_dig2_left.bmp", this, 200, 80, 0);
	digRight1 = new Image("textures/player_dig1_right.bmp", this, 200, 80, 0);
	digRight2 = new Image("textures/player_dig2_right.bmp", this, 200, 80, 0);
	deadLeft = new Image("textures/player_dead_left.bmp", this, 200, 80, 0);
	deadRight = new Image("textures/player_dead_right.bmp", this, 200, 80, 0);
	deadLadder = new Image("textures/player_dead_ladder.bmp", this, 200, 80, 0);
}

void PlayerEntity::request(Request request)
{
	lastRequest = request;
}

int PlayerEntity::schrittweite() const
{
	return config->getRasterWidth() / 2;
}

bool PlayerEntity::canMove()
{

	Stage::Cells* cells = static_cast<SpacePanicSession*>(model->getSession())->getStage()->getCells();

	double row = static_cast<double>(getPosY()) / config->getRasterHeight();
	double column = (static_cast<double>(getPosX()) + (0.5 * config->getRasterWidth())) / config->getRasterWidth();

	switch (lastRequest)
	{
	case MOVE_RIGHT:
		return cells->canMove(Stage::Cells::RIGHT, row, column);
	case MOVE_LEFT:
		return cells->canMove(Stage::Cells::LEFT, row, column);
	case MOVE_UP:
		return cells->canMove(Stage::Cells::UP, row, column);
	case MOVE_DOWN:
		return cells->canMove(Stage::Cells::DOWN, row, column);
	case DO_ACTION:
		return cells->canDig(row, column);
	default: return true;
	}
	return false;
}

void PlayerEntity::execute()
{
	if (!canMove())
	{
		lastRequest = NONE;
		return;
	}
	int row = this->getPosY() / config->getRasterHeight();
	int column = (static_cast<double>(this->getPosX()) + (0.5 * config->getRasterWidth())) / config->getRasterWidth();


	switch (lastRequest)
	{
	case MOVE_RIGHT:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case MOVE_RIGHT_1:
			this->setPosX(this->getPosX() + schrittweite());
			this->setPosY(row * config->getRasterHeight());
			state = MOVE_RIGHT_2;
			break;
		case MOVE_RIGHT_2: default:
			this->setPosX(this->getPosX() + schrittweite());
			this->setPosY(row * config->getRasterHeight());
			state = MOVE_RIGHT_1;
			break;
		}

		break;
	case MOVE_LEFT:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case MOVE_LEFT_1:
			this->setPosX(this->getPosX() - schrittweite());
			this->setPosY(row * config->getRasterHeight());
			state = MOVE_LEFT_2;
			break;
		case MOVE_LEFT_2: default:
			this->setPosX(this->getPosX() - schrittweite());
			this->setPosY(row * config->getRasterHeight());
			state = MOVE_LEFT_1;
			break;
		}
		break;
	case MOVE_UP:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case CLIMB_1:
			this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_2;
			break;
		case CLIMB_2: default:
			this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() + schrittweite());
			state = CLIMB_1;
			break;
		}
		break;
	case MOVE_DOWN:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case CLIMB_1:
			this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_2;
			break;
		case CLIMB_2: default:
			this->setPosX(column * config->getRasterWidth() - 0.5 * config->getRasterWidth());
			this->setPosY(this->getPosY() - schrittweite());
			state = CLIMB_1;
			break;
		}
		break;
	case DO_ACTION:
		switch (state)
		{
		case DEAD_LADDER:
		case DEAD_LEFT:
		case DEAD_RIGHT: break;
		case DIG_LEFT_1:
			state = DIG_LEFT_2;
			break;
		case DIG_LEFT_2: default:
			state = DIG_LEFT_1;
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
	case DIG_LEFT_1: return digLeft1;
	case DIG_LEFT_2: return digLeft2;
	case DIG_RIGHT_1: return digRight1;
	case DIG_RIGHT_2: return digRight2;
	case DEAD_LEFT: return deadLeft;
	case DEAD_RIGHT: return deadRight;
	case DEAD_LADDER: default: return deadLadder;
	}
}

bool PlayerEntity::isDead() const
{
	return state == DEAD_LEFT || state == DEAD_RIGHT || state == DEAD_LADDER;
}

void PlayerEntity::collideWith(PhysicalObject* physicalObject)
{
	if (isDead())
	{
		return;
	}

	EnemyEntity* enemy;
	if ((enemy = dynamic_cast<EnemyEntity*>(physicalObject->getEntity())))
	{
		if (enemy->getPosX() < getPosX())
		{
			state = DEAD_RIGHT;
		}
		else if (enemy->getPosX() > getPosX())
		{
			state = DEAD_LEFT;
		}
		else
		{
			state = DEAD_LADDER;
		}

		deadSince = model->getSession()->getPassedTime();
	}
}

unsigned long long PlayerEntity::getDeadSince() const
{
	return deadSince;
}
