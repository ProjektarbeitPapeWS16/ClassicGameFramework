#include "EnemyEntity.h"
#include "GameConfig.h"
#include "Image.h"
#include "SpacePanicModel.h"
#include "Session.h"
#include "PlayerEntity.h"

EnemyEntity::EnemyEntity(SpacePanicModel* model, Position* position, double difficulty) :
	Entity(new Image*[0], 5, false, new Boundaries(
		       position->x * model->getConfig()->getRasterWidth(),
		       position->y * model->getConfig()->getRasterHeight(),
		       model->getConfig()->getRasterWidth() * 2,
		       model->getConfig()->getRasterHeight() * 2,
				   model->getConfig()->applyFactor(2),
		model->getConfig()->applyFactor(1),
		model->getConfig()->applyFactor(2),
		model->getConfig()->applyFactor(5)
	       ), true, 3),
	currentRunningDirection(Stage::Cells::NONE),
	state(LAUF_1),
	model(model),
	difficulty(difficulty),
	lastDecision(0, 0)
{
	lauf1 = new Image("textures/enemy_lauf1.bmp", this, 200, 80, 0);
	lauf2 = new Image("textures/enemy_lauf2.bmp", this, 200, 80, 0);
}


Stage::Cells::Direction EnemyEntity::getRandomAllowedDirection(double row, double column)
{
	auto stage = static_cast<Stage*>(model->getSession()->getLevel());
	auto playerPosition = stage->getPlayer()->getBoundaries()->position;
	auto cells = stage->getCells();

	auto preferredDirection = Stage::Cells::Direction::NONE;
	if (playerPosition.y > getPosY())
	{
		preferredDirection = Stage::Cells::Direction::UP;
	}
	else if (playerPosition.y < getPosY())
	{
		preferredDirection = Stage::Cells::Direction::DOWN;
	}
	else if (playerPosition.x > getPosX())
	{
		preferredDirection = Stage::Cells::Direction::RIGHT;
	}
	else
	{
		preferredDirection = Stage::Cells::Direction::LEFT;
	}


	auto direction = Stage::Cells::Direction::NONE;
	int max_tries = 100;
	while (direction == Stage::Cells::NONE && max_tries-- > 0)
	{
		auto random = rand() % 4;
		switch (random)
		{
		case 0:
			direction = Stage::Cells::UP;
			break;
		case 1:
			direction = Stage::Cells::DOWN;
			break;
		case 2:
			direction = Stage::Cells::LEFT;
			break;
		case 3: default:
			direction = Stage::Cells::RIGHT;
			break;
		}

		if (direction == Stage::Cells::UP && !cells->canMove(direction, row - 0.25, column) ||
			direction != Stage::Cells::UP && !cells->canMove(direction, row, column))
		{
			direction = Stage::Cells::NONE;
		}
	}

	if ((rand() % 10000) < difficulty * 10000)
	{
		if (preferredDirection == Stage::Cells::UP && cells->canMove(preferredDirection, row - 0.25, column))
		{
			return preferredDirection;
		}
		else if (preferredDirection != Stage::Cells::UP && cells->canMove(preferredDirection, row, column))
		{
			return preferredDirection;
		}
	}


	return direction;
}

Stage::Cells::Direction EnemyEntity::getNextRunningDirection(double row, double column)
{
	auto cells = static_cast<Stage*>(model->getSession()->getLevel())->getCells();

	switch (currentRunningDirection)
	{
	case Stage::Cells::UP:
		if (cells->canMove(Stage::Cells::LEFT, row - 0.25, column) ||
			cells->canMove(Stage::Cells::RIGHT, row, column))
		{
			return getRandomAllowedDirection(row, column);
		}
		else if (cells->canMove(Stage::Cells::UP, row - 0.25, column))
		{
			return Stage::Cells::UP;
		}
		else
		{
			return Stage::Cells::DOWN;
		}
	case Stage::Cells::DOWN:
		if (cells->canMove(Stage::Cells::LEFT, row, column) ||
			cells->canMove(Stage::Cells::RIGHT, row, column))
		{
			return getRandomAllowedDirection(row, column);
		}
		else if (cells->canMove(Stage::Cells::DOWN, row, column))
		{
			return Stage::Cells::DOWN;
		}
		else
		{
			return Stage::Cells::UP;
		}
	case Stage::Cells::LEFT:
		if (cells->canMove(Stage::Cells::UP, row - 0.25, column) ||
			cells->canMove(Stage::Cells::DOWN, row, column))
		{
			return getRandomAllowedDirection(row, column);
		}
		else if (cells->canMove(Stage::Cells::LEFT, row, column))
		{
			return Stage::Cells::LEFT;
		}
		else
		{
			return Stage::Cells::RIGHT;
		}
	case Stage::Cells::RIGHT:
		if (cells->canMove(Stage::Cells::UP, row - 0.25, column) ||
			cells->canMove(Stage::Cells::DOWN, row, column))
		{
			return getRandomAllowedDirection(row, column);
		}
		else if (cells->canMove(Stage::Cells::RIGHT, row, column))
		{
			return Stage::Cells::RIGHT;
		}
		else
		{
			return Stage::Cells::LEFT;
		}
	case Stage::Cells::NONE: default:
		return getRandomAllowedDirection(row, column);
	}
}

void EnemyEntity::execute()
{
	if (static_cast<Stage*>(model->getSession()->getLevel())->getPlayer()->isDead())
	{
		return;
	}

	double row = static_cast<double>(this->getPosY()) / model->getConfig()->getRasterHeight();
	double column = (static_cast<double>(this->getPosX()) + (0.5 * model->getConfig()->getRasterWidth())) / model->getConfig()->getRasterWidth();


	switch (state)
	{
	case LAUF_1:
	case LAUF_2:
		{
			Stage::Cells::Direction nextDirection = getNextRunningDirection(row, column);
			if (nextDirection != Stage::Cells::NONE)
			{
				currentRunningDirection = nextDirection;
			}

			switch (currentRunningDirection)
			{
			case Stage::Cells::RIGHT:
				setPosX(getPosX() + model->getConfig()->getRasterWidth() * 0.25);
				setPosY((int)row * model->getConfig()->getRasterHeight());
				break;
			case Stage::Cells::LEFT:
				setPosX(getPosX() - model->getConfig()->getRasterWidth() * 0.25);
				setPosY((int)row * model->getConfig()->getRasterHeight());
				break;
			case Stage::Cells::DOWN:
				setPosX((int)column * model->getConfig()->getRasterWidth() - model->getConfig()->getRasterWidth() * 0.5);
				setPosY(getPosY() - model->getConfig()->getRasterHeight() * 0.25);
				break;
			case Stage::Cells::UP:
				setPosX((int)column * model->getConfig()->getRasterWidth() - model->getConfig()->getRasterWidth() * 0.5);
				setPosY(getPosY() + model->getConfig()->getRasterHeight() * 0.25);
				break;
			default: break;
			}
		}
		break;
	default: break;
	}


	switch (state)
	{
	case LAUF_1:
		if (counter % 4 < 2)
		{
			state = LAUF_1;
		}
		else
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
