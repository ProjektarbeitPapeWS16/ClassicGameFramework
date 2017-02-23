#include "EnemyEntity.h"
#include "GameConfig.h"
#include "Image.h"
#include "SpacePanicModel.h"
#include "Session.h"
#include "PlayerEntity.h"
#include "LadderEntity.h"

void EnemyEntity::collideWith(PhysicalObject* physicalObject)
{
	if (dynamic_cast<EnemyEntity*>(physicalObject))
	{
		switch (currentRunningDirection)
		{
		case Stage::Cells::RIGHT:
			currentRunningDirection = Stage::Cells::LEFT;
			break;
		case Stage::Cells::LEFT:
			currentRunningDirection = Stage::Cells::RIGHT;
			break;
		case Stage::Cells::DOWN:
			currentRunningDirection = Stage::Cells::UP;
			break;
		case Stage::Cells::UP:
			currentRunningDirection = Stage::Cells::DOWN;
			break;
		default: break;
		}
	}
}

EnemyEntity::EnemyEntity(SpacePanicModel* model, Position* position, double difficulty) :
	MovableEntity(new Image*[0], 5, false, new Boundaries(
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


Stage::Cells::Direction EnemyEntity::getRandomAllowedDirection()
{
	auto stage = static_cast<Stage*>(model->getSession()->getLevel());
	auto playerPosition = stage->getPlayer()->getBoundaries()->position;
	//auto cells = stage->getCells();

	auto preferredDirection = Stage::Cells::Direction::NONE;
	int playerRow = ((playerPosition.y - 4 * model->getConfig()->getRasterHeight()) / model->getConfig()->getRasterHeight());
	int enemyRow = ((getPosY() - 4 * model->getConfig()->getRasterHeight()) / model->getConfig()->getRasterHeight());
	int rowDifference = playerRow - enemyRow;
	if (rowDifference < 0)
	{
		rowDifference *= -1;
	}

	if (rowDifference < 4)
	{
		if (playerPosition.x == this->getPosX())
		{
			if (playerRow > enemyRow)
			{
				preferredDirection = Stage::Cells::UP;
			}
			else
			{
				preferredDirection = Stage::Cells::DOWN;
			}
		}
		else if (playerPosition.x > this->getPosX())
		{
			preferredDirection = Stage::Cells::RIGHT;
		}
		else
		{
			preferredDirection = Stage::Cells::LEFT;
		}
	}
	else if (playerRow > enemyRow)
	{
		preferredDirection = Stage::Cells::UP;
	}
	else
	{
		preferredDirection = Stage::Cells::DOWN;
	}


	auto direction = Stage::Cells::Direction::NONE;
	PhysicalObject* directionalObject = nullptr;
	int max_tries = 100;
	while (direction == Stage::Cells::NONE && max_tries-- > 0)
	{
		auto random = rand() % 4;
		switch (random)
		{
		case 0:
			if ((directionalObject = canMoveUp()))
			{
				direction = Stage::Cells::UP;
			}
			break;
		case 1:
			if ((directionalObject = canMoveDown()))
			{
				direction = Stage::Cells::DOWN;
			}
			break;
		case 2:
			if ((directionalObject = canMoveLeft()))
			{
				direction = Stage::Cells::LEFT;
			}
			break;
		case 3: default:
			if ((directionalObject = canMoveRight()))
			{
				direction = Stage::Cells::RIGHT;
			}
			break;
		}
	}

	PhysicalObject* preferredDirectionalObject = nullptr;
	if ((rand() % 10000) < difficulty * 10000)
	{
		switch (preferredDirection)
		{
		case Stage::Cells::RIGHT:
			if ((preferredDirectionalObject = canMoveRight()))
			{
				//y-axis correction
				setPosition(getPosX(), preferredDirectionalObject->getBoundaries()->position.y + preferredDirectionalObject->getBoundaries()->height);
				return preferredDirection;
			}
			break;
		case Stage::Cells::LEFT:
			if ((preferredDirectionalObject = canMoveLeft()))
			{
				//y-axis correction
				setPosition(getPosX(), preferredDirectionalObject->getBoundaries()->position.y + preferredDirectionalObject->getBoundaries()->height);
				return preferredDirection;
			}
			break;
		case Stage::Cells::DOWN:
			if ((preferredDirectionalObject = canMoveDown()))
			{
				//x-axis correction
				setPosition(preferredDirectionalObject->getBoundaries()->position.x - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
				return preferredDirection;
			}
			break;
		case Stage::Cells::UP:
			if ((preferredDirectionalObject = canMoveUp()))
			{
				//x-axis correction
				setPosition(preferredDirectionalObject->getBoundaries()->position.x - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
				return preferredDirection;
			}
			break;
		default: break;
		}
	}

	switch (direction)
	{
	case Stage::Cells::RIGHT:
	case Stage::Cells::LEFT:
		//y-axis correction
		setPosition(getPosX(), directionalObject->getBoundaries()->position.y + directionalObject->getBoundaries()->height);
		break;
	case Stage::Cells::DOWN:
	case Stage::Cells::UP:
		//x-axis correction
		setPosition(directionalObject->getBoundaries()->position.x - getConfig()->getRasterWidth() / 2, getBoundaries()->position.y);
		break;
	default: break;;
	}
	return direction;
}

Stage::Cells::Direction EnemyEntity::getNextRunningDirection()
{
	auto behind = model->getPhysics()->backgroundOnPosition(Position(boundaries->real_x() + boundaries->real_width() / 2, boundaries->real_y() + boundaries->real_height() / 2));
	for(int i = 0; i < behind->size(); i++)
	{
		LadderEntity* ladder = dynamic_cast<LadderEntity*>(behind->at(i));
		if(ladder)
		{
			
		}
	}

	if (getBoundaries()->real_x() % (getConfig()->getRasterWidth()) != 0 &&
		getPosY() % (getConfig()->getRasterHeight()) != 0)
	{
		return Stage::Cells::NONE;
	}

	//auto cells = static_cast<Stage*>(model->getSession()->getLevel())->getCells();

	switch (currentRunningDirection)
	{
	case Stage::Cells::UP:
		if(canMoveLeft() || canMoveRight())
		{
			return getRandomAllowedDirection();
		} else if(canMoveUp())
		{
			return Stage::Cells::UP;
		} else
		{
			return Stage::Cells::DOWN;
		}
	case Stage::Cells::DOWN:
		if (canMoveLeft() || canMoveRight())
		{
			return getRandomAllowedDirection();
		}
		else if (canMoveDown())
		{
			return Stage::Cells::DOWN;
		}
		else
		{
			return Stage::Cells::UP;
		}
	case Stage::Cells::LEFT:
		if (canMoveUp() || canMoveDown())
		{
			return getRandomAllowedDirection();
		}
		else if (canMoveLeft())
		{
			return Stage::Cells::LEFT;
		}
		else
		{
			return Stage::Cells::RIGHT;
		}
	case Stage::Cells::RIGHT:
		if (canMoveUp() || canMoveDown())
		{
			return getRandomAllowedDirection();
		}
		else if (canMoveRight())
		{
			return Stage::Cells::RIGHT;
		}
		else
		{
			return Stage::Cells::LEFT;
		}
	case Stage::Cells::NONE: default:
		return getRandomAllowedDirection();
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
			Stage::Cells::Direction nextDirection = getNextRunningDirection();
			if (nextDirection != Stage::Cells::NONE)
			{
				currentRunningDirection = nextDirection;
			}

			switch (currentRunningDirection)
			{
			case Stage::Cells::RIGHT:
				setPosX(getPosX() + model->getConfig()->getRasterWidth() * 0.25);
				//setPosY((int)row * model->getConfig()->getRasterHeight());
				break;
			case Stage::Cells::LEFT:
				{
					setPosX(getPosX() - model->getConfig()->getRasterWidth() * 0.25);

					auto holePos = Position(boundaries->position);
					holePos.x += (boundaries->width / 2) - 1;
					holePos.y -= 1;
					HoleEntity::HoleState holeState = canFall(holePos);

					this->inHole = holeState;

					if (this->inHole == HoleEntity::STAGE3)
					{
						inHole = HoleEntity::STAGE0;
						state = EnemyState::FALLING;
					}
					else
					{
						state = EnemyState::IN_HOLE_WAITING;
						inHoleWaitingSince = Config::currentTimeMillis();
					}

					//setPosY((int)row * model->getConfig()->getRasterHeight());
				}
				break;
			case Stage::Cells::DOWN:
				//setPosX((int)column * model->getConfig()->getRasterWidth() - model->getConfig()->getRasterWidth() * 0.5);
				setPosY(getPosY() - model->getConfig()->getRasterHeight() * 0.25);
				break;
			case Stage::Cells::UP:
				//setPosX((int)column * model->getConfig()->getRasterWidth() - model->getConfig()->getRasterWidth() * 0.5);
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

SpacePanicModel* EnemyEntity::getModel() const
{
	return model;
}

Boundaries* EnemyEntity::getBoundaries()
{
	return boundaries;
}

GameConfig* EnemyEntity::getConfig() const
{
	return model->getConfig();
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

EnemyEntity::~EnemyEntity()
{
	delete lauf1;
	delete lauf2;
}
