#include "MyLevel.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "WallEntity.h"
#include "DotEntity.h"
#include "EnergizerEntity.h"
#include "Physics.h"
#include "PacManModel.h"
#include "Config.h"
#include "Font.h"
#include "Text.h"
#include "SpecialEntity.h"
#include "BonusEntity.h"

#define AMP 3

MyLevel::MyLevel(int colsGrid, int rowsGrid, int xTileSize, int yTileSize) 
	: Level(colsGrid, rowsGrid, xTileSize, yTileSize, new Physics())
{
	initializeLevel();
	start();
}

void MyLevel::initializeLevel()
{
	entities = new std::vector<Entity*>();
	walls = new std::vector<WallEntity*>();

	// Left Wall, from bottom to top
	walls->push_back(new WallEntity("textures/Walls/wallCornerDL5x5.bmp", new Boundaries(0 * AMP, 16 * AMP, 5 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall5x38.bmp", new Boundaries(0 * AMP, 21 * AMP, 5 * AMP, 38 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall5x10L.bmp", new Boundaries(0 * AMP, 59 * AMP, 5 * AMP, 10 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall15x8L.bmp", new Boundaries(5 * AMP, 60 * AMP, 15 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall5x38.bmp", new Boundaries(0 * AMP, 69 * AMP, 5 * AMP, 38 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUL5x5.bmp", new Boundaries(0 * AMP, 107 * AMP, 5 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(5 * AMP, 108 * AMP, 35 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerDR4x4.bmp", new Boundaries(40 * AMP, 108 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(40 * AMP, 112 * AMP, 4 * AMP, 24 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUR4x4.bmp", new Boundaries(40 * AMP, 136 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(0 * AMP, 136 * AMP, 40 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(0 * AMP, 156 * AMP, 40 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerDR4x4.bmp", new Boundaries(40 * AMP, 156 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(40 * AMP, 160 * AMP, 4 * AMP, 24 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUR4x4.bmp", new Boundaries(40 * AMP, 184 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(5 * AMP, 184 * AMP, 35 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerDL5x5.bmp", new Boundaries(0 * AMP, 184 * AMP, 5 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall5x70.bmp", new Boundaries(0 * AMP, 189 * AMP, 5 * AMP, 70 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUL5x5.bmp", new Boundaries(0 * AMP, 259 * AMP, 5 * AMP, 5 * AMP)));

	// Down Wall
	walls->push_back(new WallEntity("textures/Walls/wall214x4.bmp", new Boundaries(5 * AMP, 16 * AMP, 214 * AMP, 4 * AMP)));

	// Upper Wall
	walls->push_back(new WallEntity("textures/Walls/wall102x4.bmp", new Boundaries(5 * AMP, 260 * AMP, 102 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall10x5.bmp", new Boundaries(107 * AMP, 259 * AMP, 10 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x31.bmp", new Boundaries(108 * AMP, 228 * AMP, 8 * AMP, 31 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall102x4.bmp", new Boundaries(117 * AMP, 260 * AMP, 102 * AMP, 4 * AMP)));

	// Right Wall, from bottom to top
	walls->push_back(new WallEntity("textures/Walls/wallCornerDR5x5.bmp", new Boundaries(219 * AMP, 16 * AMP, 5 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x38.bmp", new Boundaries(220 * AMP, 21 * AMP, 4 * AMP, 38 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall5x10R.bmp", new Boundaries(219 * AMP, 59 * AMP, 5 * AMP, 10 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall15x8R.bmp", new Boundaries(204 * AMP, 60 * AMP, 15 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x38.bmp", new Boundaries(220 * AMP, 69 * AMP, 4 * AMP, 38 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUR5x5.bmp", new Boundaries(219 * AMP, 107 * AMP, 5 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(184 * AMP, 108 * AMP, 35 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerDL4x4.bmp", new Boundaries(180 * AMP, 108 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(180 * AMP, 112 * AMP, 4 * AMP, 24 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUL4x4.bmp", new Boundaries(180 * AMP, 136 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(184 * AMP, 136 * AMP, 40 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(184 * AMP, 156 * AMP, 40 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerDL4x4.bmp", new Boundaries(180 * AMP, 156 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(180 * AMP, 160 * AMP, 4 * AMP, 24 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUL4x4.bmp", new Boundaries(180 * AMP, 184 * AMP, 4 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(184 * AMP, 184 * AMP, 35 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerDR5x5.bmp", new Boundaries(219 * AMP, 184 * AMP, 5 * AMP, 5 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x70.bmp", new Boundaries(220 * AMP, 189 * AMP, 4 * AMP, 70 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wallCornerUR5x5.bmp", new Boundaries(219 * AMP, 259 * AMP, 5 * AMP, 5 * AMP)));

	// first row of rectangles from top
	walls->push_back(new WallEntity("textures/Walls/wall24x16.bmp", new Boundaries(20 * AMP, 228 * AMP, 24 * AMP, 16 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall32x16.bmp", new Boundaries(60 * AMP, 228 * AMP, 32 * AMP, 16 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall32x16.bmp", new Boundaries(132 * AMP, 228 * AMP, 32 * AMP, 16 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall24x16.bmp", new Boundaries(180 * AMP, 228 * AMP, 24 * AMP, 16 * AMP)));

	// second row of rectangles from top
	walls->push_back(new WallEntity("textures/Walls/wall24x8.bmp", new Boundaries(20 * AMP, 204 * AMP, 24 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall24x8.bmp", new Boundaries(180 * AMP, 204 * AMP, 24 * AMP, 8 * AMP)));

	// |
	// |-  upper left
	// |
	walls->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(60 * AMP, 189 * AMP, 8 * AMP, 23 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall9x10L.bmp", new Boundaries(60 * AMP, 179 * AMP, 9 * AMP, 10 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(60 * AMP, 156 * AMP, 8 * AMP, 23 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(69 * AMP, 180 * AMP, 23 * AMP, 8 * AMP)));

	// ___ upper mid
	//  |
	walls->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(84 * AMP, 204 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall10x9U.bmp", new Boundaries(107 * AMP, 203 * AMP, 10 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(117 * AMP, 204 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(108 * AMP, 180 * AMP, 8 * AMP, 23 * AMP)));

	//  |
	// -|  upper right
	//  |
	walls->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(156 * AMP, 189 * AMP, 8 * AMP, 23 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall9x10R.bmp", new Boundaries(155 * AMP, 179 * AMP, 9 * AMP, 10 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(156 * AMP, 156 * AMP, 8 * AMP, 23 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(132 * AMP, 180 * AMP, 23 * AMP, 8 * AMP)));

	// TODO box mid
	walls->push_back(new WallEntity("textures/Walls/wall56x4.bmp", new Boundaries(84 * AMP, 132 * AMP, 56 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(84 * AMP, 136 * AMP, 4 * AMP, 24 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(136 * AMP, 136 * AMP, 4 * AMP, 24 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall20x4L.bmp", new Boundaries(84 * AMP, 160 * AMP, 20 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall20x4R.bmp", new Boundaries(120 * AMP, 160 * AMP, 20 * AMP, 4 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall16x4special.bmp", new Boundaries(104 * AMP, 160 * AMP, 16 * AMP, 4 * AMP)));

	// rectangles mid
	walls->push_back(new WallEntity("textures/Walls/wall8x32.bmp", new Boundaries(60 * AMP, 108 * AMP, 8 * AMP, 32 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x32.bmp", new Boundaries(156 * AMP, 108 * AMP, 8 * AMP, 32 * AMP)));

	// ___ mid mid
	//  |
	walls->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(84 * AMP, 108 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall10x9U.bmp", new Boundaries(107 * AMP, 107 * AMP, 10 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(117 * AMP, 108 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(108 * AMP, 84 * AMP, 8 * AMP, 23 * AMP)));

	// __ bottom left
	//  |
	walls->push_back(new WallEntity("textures/Walls/wall15x8R.bmp", new Boundaries(20 * AMP, 84 * AMP, 15 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall9x9L.bmp", new Boundaries(35 * AMP, 83 * AMP, 9 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(36 * AMP, 60 * AMP, 8 * AMP, 23 * AMP)));

	// rectangles bottom
	walls->push_back(new WallEntity("textures/Walls/wall32x8.bmp", new Boundaries(60 * AMP, 84 * AMP, 32 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall32x8.bmp", new Boundaries(132 * AMP, 84 * AMP, 32 * AMP, 8 * AMP)));

	// __ bottom left
	//  |
	walls->push_back(new WallEntity("textures/Walls/wall15x8L.bmp", new Boundaries(189 * AMP, 84 * AMP, 15 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall9x9R.bmp", new Boundaries(180 * AMP, 83 * AMP, 9 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(180 * AMP, 60 * AMP, 8 * AMP, 23 * AMP)));

	// __|_ down left
	walls->push_back(new WallEntity("textures/Walls/wall39x8o--.bmp", new Boundaries(20 * AMP, 36 * AMP, 39 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall10x9D.bmp", new Boundaries(59 * AMP, 36 * AMP, 10 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(69 * AMP, 36 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(60 * AMP, 45 * AMP, 8 * AMP, 23 * AMP)));

	// ___ bottom mid
	//  |
	walls->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(84 * AMP, 60 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall10x9U.bmp", new Boundaries(107 * AMP, 59 * AMP, 10 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(117 * AMP, 60 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(108 * AMP, 36 * AMP, 8 * AMP, 23 * AMP)));

	// _|__ down right
	walls->push_back(new WallEntity("textures/Walls/wall39x8--o.bmp", new Boundaries(165 * AMP, 36 * AMP, 39 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall10x9D.bmp", new Boundaries(155 * AMP, 36 * AMP, 10 * AMP, 9 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(132 * AMP, 36 * AMP, 23 * AMP, 8 * AMP)));
	walls->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(156 * AMP, 45 * AMP, 8 * AMP, 23 * AMP)));

	// adding walls to entities
	for (unsigned int i = 0; i < walls->size(); i++)
	{
		entities->push_back(walls->at(i));
	}

	createDots();

	entities->push_back(&text);

	pacLife1 = new SpecialEntity(0);
	pacLife2 = new SpecialEntity(1);
	pacLife3 = new SpecialEntity(2);
	entities->push_back(pacLife1);
	entities->push_back(pacLife2);
	entities->push_back(pacLife3);
}

void MyLevel::start()
{
	gameState = NORMAL;
	pacman = new PlayerEntity(new Boundaries(106 * AMP, 69 * AMP, 13 * AMP, 13 * AMP));

	redGhost = new EnemyEntity(new Boundaries(105 * AMP, 165 * AMP, 14 * AMP, 14 * AMP));
	redGhost->setTextures("textures/Ghosts/redGhost/redGhostUp1.bmp",
		"textures/Ghosts/redGhost/redGhostUp2.bmp",
		"textures/Ghosts/redGhost/redGhostDown1.bmp",
		"textures/Ghosts/redGhost/redGhostDown2.bmp",
		"textures/Ghosts/redGhost/redGhostRight1.bmp",
		"textures/Ghosts/redGhost/redGhostRight2.bmp",
		"textures/Ghosts/redGhost/redGhostLeft1.bmp",
		"textures/Ghosts/redGhost/redGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	redGhost->setDirection(EnemyEntity::LEFT);
	redGhost->setName(EnemyEntity::Blinky);
	redGhost->setPacman(pacman);
	redGhost->setPhysics(getPhysics());
	redGhost->setLevel(this);
	redGhost->setCageState(EnemyEntity::NO);

	pinkGhost = new EnemyEntity(new Boundaries(105 * AMP, 141 * AMP, 14 * AMP, 14 * AMP));
	pinkGhost->setTextures("textures/Ghosts/pinkGhost/pinkGhostUp1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostUp2.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostDown1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostDown2.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostRight1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostRight2.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostLeft1.bmp",
		"textures/Ghosts/pinkGhost/pinkGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	pinkGhost->setDirection(EnemyEntity::DOWN);
	pinkGhost->setName(EnemyEntity::Pinky);
	pinkGhost->setPacman(pacman);
	pinkGhost->setPhysics(getPhysics());
	pinkGhost->setLevel(this);
	pinkGhost->setCageState(EnemyEntity::OUT);

	blueGhost = new EnemyEntity(new Boundaries(89 * AMP, 141 * AMP, 14 * AMP, 14 * AMP));
	blueGhost->setTextures("textures/Ghosts/blueGhost/blueGhostUp1.bmp",
		"textures/Ghosts/blueGhost/blueGhostUp2.bmp",
		"textures/Ghosts/blueGhost/blueGhostDown1.bmp",
		"textures/Ghosts/blueGhost/blueGhostDown2.bmp",
		"textures/Ghosts/blueGhost/blueGhostRight1.bmp",
		"textures/Ghosts/blueGhost/blueGhostRight2.bmp",
		"textures/Ghosts/blueGhost/blueGhostLeft1.bmp",
		"textures/Ghosts/blueGhost/blueGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	blueGhost->setDirection(EnemyEntity::UP);
	blueGhost->setName(EnemyEntity::Inky);
	blueGhost->setPacman(pacman);
	blueGhost->setPhysics(getPhysics());
	blueGhost->setLevel(this);

	blueGhost->setBlinky(redGhost);

	orangeGhost = new EnemyEntity(new Boundaries(121 * AMP, 141 * AMP, 14 * AMP, 14 * AMP));
	orangeGhost->setTextures("textures/Ghosts/orangeGhost/orangeGhostUp1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostUp2.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostDown1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostDown2.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostRight1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostRight2.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostLeft1.bmp",
		"textures/Ghosts/orangeGhost/orangeGhostLeft2.bmp",
		"textures/Ghosts/energizedGhost1.bmp",
		"textures/Ghosts/energizedGhost2.bmp");
	orangeGhost->setDirection(EnemyEntity::UP);
	orangeGhost->setName(EnemyEntity::Clyde);
	orangeGhost->setPacman(pacman);
	orangeGhost->setPhysics(getPhysics());
	orangeGhost->setLevel(this);


	entities->push_back(pacman);
	entities->push_back(blueGhost);
	entities->push_back(redGhost);
	entities->push_back(orangeGhost);
	entities->push_back(pinkGhost);
}

void MyLevel::restart()
{
	// 
	for (unsigned int i = entities->size()-1; i >= 0; i--)
	{
		if (entities->at(i) == pacman) {
			entities->erase(entities->begin() + i);
			delete pacman;
			break;
		}
	}
	for (unsigned int i = entities->size()-1; i >= 0; i--)
	{
		if (entities->at(i) == blueGhost) {
			entities->erase(entities->begin() + i);
			delete blueGhost;
			break;
		}
	}
	for (unsigned int i = entities->size()-1; i >= 0; i--)
	{
		if (entities->at(i) == redGhost) {
			entities->erase(entities->begin() + i);
			delete redGhost;
			break;
		}
	}
	for (unsigned int i = entities->size()-1; i >= 0; i--)
	{
		if (entities->at(i) == orangeGhost) {
			entities->erase(entities->begin() + i);
			delete orangeGhost;
			break;
		}
	}
	for (unsigned int i = entities->size()-1; i >= 0; i--)
	{
		if (entities->at(i) == pinkGhost) {
			entities->erase(entities->begin() + i);
			delete pinkGhost;
			break;
		}
	}
	ghostTimer = Config::currentTimeMillis();
	movementMode = EnemyEntity::SCATTER;

	for (unsigned int i = 0; i < entities->size(); i++)
	{
		if (entities->at(i) == bonus1)
		{
			entities->erase(entities->begin() + i);
			delete bonus1;
			bbonus1 = false;
			break;
		}
	}
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		if (entities->at(i) == bonus2)
		{
			entities->erase(entities->begin() + i);
			delete bonus2;
			bbonus2 = false;
			break;
		}
	}

	start();
}


MyLevel::~MyLevel()
{
}


void MyLevel::gameLoop()
{
	
	if ((Config::currentTimeMillis() - timer) > 60)
	{
		timer = Config::currentTimeMillis();

		if (dotCounter == 0 && energizerCounter == 0)
		{
			bbonus1 = true;
			bbonus2 = true;
			createDots();
			restart();
			//gameState = MyLevel::RESTARTGAME; // tell the guy above
			return;
		}


		// Bonus
		if (dotCounter < 240 - 70 && bbonus1 == false)
		{
			bonus1 = new BonusEntity();
			entities->push_back(bonus1);
			bbonus1 = true;
			bonusTimer1 = Config::currentTimeMillis();
		}
		if (dotCounter < 240 - 170 && bbonus2 == false)
		{
			bonus2 = new BonusEntity();
			entities->push_back(bonus2);
			bbonus2 = true;
			bonusTimer2 = Config::currentTimeMillis();
		}
		if (Config::currentTimeMillis() - bonusTimer1 > 10000)
		{
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				if (entities->at(i) == bonus1)
				{
					entities->erase(entities->begin() + i);
					delete bonus1;
					break;
				}
			}
		}
		if (Config::currentTimeMillis() - bonusTimer2 > 10000)
		{
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				if (entities->at(i) == bonus2)
				{
					entities->erase(entities->begin() + i);
					delete bonus2;
					break;
				}
			}
		}



		// pacman dies
		if (pacman->getState() == PlayerEntity::DIE)
		{
			// deathanimation
			pacman->execute();
			return;
		}

		if (pacman->getState() == PlayerEntity::DEAD)
		{
			life--;
			switch (life)
			{
			case 2:
				for (unsigned int i = 0; i < entities->size(); i++)
				{
					if (entities->at(i) == pacLife3)
					{
						entities->erase(entities->begin() + i);
					}
				}
				restart();
				break;
			case 1:
				for (unsigned int i = 0; i < entities->size(); i++)
				{
					if (entities->at(i) == pacLife2)
					{
						entities->erase(entities->begin() + i);
					}
				}
				restart();
				break;
			case 0:
				for (unsigned int i = 0; i < entities->size(); i++)
				{
					if (entities->at(i) == pacLife1)
					{
						entities->erase(entities->begin() + i);
					}
				}
				restart();
				break;
			default:
				gameState = MyLevel::RESTARTGAME;
				break;
			}
			return;
		}

		// pacman behaviour
		pacManExecution();


		// ghost behaviour
		// TODO switch direction
		// TODO special crossing
		switch (movementMode)
		{
		case EnemyEntity::SCATTER:
			if (Config::currentTimeMillis() - ghostTimer > 7000)
			{
				ghostTimer = Config::currentTimeMillis();
				movementMode = EnemyEntity::CHASE;
				blueGhost->setMovementMode(EnemyEntity::CHASE);
				redGhost->setMovementMode(EnemyEntity::CHASE);
				pinkGhost->setMovementMode(EnemyEntity::CHASE);
				orangeGhost->setMovementMode(EnemyEntity::CHASE);
				blueGhost->invertDirection();
				redGhost->invertDirection();
				orangeGhost->invertDirection();
				pinkGhost->invertDirection();
			}
			break;
		case EnemyEntity::CHASE:
			if (Config::currentTimeMillis() - ghostTimer > 20000)
			{
				ghostTimer = Config::currentTimeMillis();
				movementMode = EnemyEntity::SCATTER;
				blueGhost->setMovementMode(EnemyEntity::SCATTER);
				redGhost->setMovementMode(EnemyEntity::SCATTER);
				pinkGhost->setMovementMode(EnemyEntity::SCATTER);
				orangeGhost->setMovementMode(EnemyEntity::SCATTER);
				blueGhost->invertDirection();
				redGhost->invertDirection();
				orangeGhost->invertDirection();
				pinkGhost->invertDirection();
			}
			break;
		}

		// ghost cage
		if (blueGhost->getCageState() == EnemyEntity::LOCKED)
		{
			if (dotCounter < 240 - 30)
			{
				blueGhost->setCageState(EnemyEntity::LEFTPLACE);
			}
		}
		if (orangeGhost->getCageState() == EnemyEntity::LOCKED)
		{
			if (dotCounter < 240 - 80) {
				orangeGhost->setCageState(EnemyEntity::RIGHTPLACE);
			}
		}
		redGhost->execute();
		blueGhost->execute();
		pinkGhost->execute();
		orangeGhost->execute();
		

		showScore(); 
	}
}

void MyLevel::createDots()
{
	// dots horizontal
	for (int i = 0; i < 26; i++)
	{
		entities->push_back(new DotEntity((11 + i * 8) * AMP, 27 * AMP));
	}
	for (int i = 0; i < 26; i++)
	{
		if (i == 6) { i = 8; }
		if (i == 12) { i = 14; }
		if (i == 18) { i = 20; }
		entities->push_back(new DotEntity((11 + i * 8) * AMP, (27 + 24) * AMP));
	}
	for (int i = 1; i < 25; i++)
	{
		if (i == 3) { i = 5; }
		if (i == 12) { i = 14; }
		if (i == 21) { i = 23; }
		entities->push_back(new DotEntity((11 + i * 8) * AMP, (27 + 24 * 2) * AMP));
	}
	for (int i = 0; i < 26; i++)
	{
		if (i == 12) { i = 14; }
		entities->push_back(new DotEntity((11 + i * 8) * AMP, (27 + 24 * 3) * AMP));
	}
	for (int i = 0; i < 26; i++)
	{
		if (i == 6) { i = 8; }
		if (i == 12) { i = 14; }
		if (i == 18) { i = 20; }
		entities->push_back(new DotEntity((11 + i * 8) * AMP, (27 + 8 * 21) * AMP));
	}
	for (int i = 0; i < 26; i++)
	{
		entities->push_back(new DotEntity((11 + i * 8) * AMP, (27 + 8 * 24) * AMP));
	}
	for (int i = 0; i < 26; i++)
	{
		if (i == 12) { i = 14; }
		entities->push_back(new DotEntity((11 + i * 8) * AMP, (27 + 8 * 28) * AMP));
	}

	// vertikale Dots von links nach rechts
	for (int i = 1; i < 28; i++)
	{
		if (i == 3) { i = 7; }
		if (i == 9) { i = 22; }
		if (i == 24) { i = 25; }
		if (i == 26) { i = 27; }
		entities->push_back(new DotEntity(11 * AMP, (27 + i * 8) * AMP));
	}
	entities->push_back(new DotEntity((11 + 8 * 2) * AMP, (27 + 4 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 8 * 2) * AMP, (27 + 5 * 8) * AMP));
	for (int i = 4; i < 28; i++)
	{
		if (i == 6) { i = 7; }
		if (i == 9) { i = 10; }
		if (i == 21) { i = 22; }
		if (i == 24) { i = 25; }
		entities->push_back(new DotEntity((11 + 8 * 5) * AMP, (27 + i * 8) * AMP));
	}
	entities->push_back(new DotEntity((11 + 8 * 8) * AMP, (27 + 4 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 8 * 8) * AMP, (27 + 5 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 8 * 8) * AMP, (27 + 22 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 8 * 8) * AMP, (27 + 23 * 8) * AMP));

	for (int i = 1; i < 28; i++)
	{
		if (i == 3) { i = 7; }
		if (i == 9) { i = 25; }
		entities->push_back(new DotEntity((11 + 11 * 8) * AMP, (27 + i * 8) * AMP));
	}
	//spiegel
	for (int i = 1; i < 28; i++)
	{
		if (i == 3) { i = 7; }
		if (i == 9) { i = 25; }
		entities->push_back(new DotEntity((11 + 14 * 8) * AMP, (27 + i * 8) * AMP));
	}
	entities->push_back(new DotEntity((11 + 17 * 8) * AMP, (27 + 23 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 17 * 8) * AMP, (27 + 22 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 17 * 8) * AMP, (27 + 5 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 17 * 8) * AMP, (27 + 4 * 8) * AMP));
	for (int i = 4; i < 28; i++)
	{
		if (i == 6) { i = 7; }
		if (i == 9) { i = 10; }
		if (i == 21) { i = 22; }
		if (i == 24) { i = 25; }
		entities->push_back(new DotEntity((11 + 20 * 8) * AMP, (27 + i * 8) * AMP));
	}
	entities->push_back(new DotEntity((11 + 23 * 8) * AMP, (27 + 5 * 8) * AMP));
	entities->push_back(new DotEntity((11 + 23 * 8) * AMP, (27 + 4 * 8) * AMP));
	for (int i = 1; i < 28; i++)
	{
		if (i == 3) { i = 7; }
		if (i == 9) { i = 22; }
		if (i == 24) { i = 25; }
		if (i == 26) { i = 27; }
		entities->push_back(new DotEntity((11 + 25 * 8) * AMP, (27 + i * 8) * AMP));
	}

	// Energizer
	entities->push_back(new EnergizerEntity((8 + 0 * 8) * AMP, (24 + 6 * 8) * AMP));
	entities->push_back(new EnergizerEntity((8 + 25 * 8) * AMP, (24 + 6 * 8) * AMP));
	entities->push_back(new EnergizerEntity((8 + 0 * 8) * AMP, (24 + 26 * 8) * AMP));
	entities->push_back(new EnergizerEntity((8 + 25 * 8) * AMP, (24 + 26 * 8) * AMP));

	dotCounter = 240;
	energizerCounter = 4;
}

void MyLevel::pacManExecution()
{
	// TODO make easier to understand
	pacman->alternateMovement();
	pacman->setMemoryRequest(); // save last action
	pacman->requestPuffer(); // get new action
	pacman->execute(); // try it
	if (pacManXWall()) // wall?
	{
		pacman->stepBack(); 
		pacman->requestMemory(); // get saved action
		pacman->execute(); // try saved action
		if (pacManXWall())
		{
			pacman->stepBack();
		}
	}
	pacManCollision();
}

bool MyLevel::pacManXWall()
{
	auto castedWalls = new std::vector<PhysicalObject*>();
	for (unsigned int i = 0; i < walls->size(); i++)
	{
		castedWalls->push_back(static_cast<PhysicalObject*>(walls->at(i)));
	}
	auto collision = getPhysics()->checkCollisions(pacman, castedWalls);

	if (collision->size() > 0)
	{
		return true;
	}
	return false;
}


void MyLevel::pacManCollision()
{
	std::vector<PhysicalObject*>* collisions = getPhysics()->checkCollisions(pacman, getPhysicalObjects());
	
	for (unsigned int i = 0; i < collisions->size(); i++)
	{
		if (DotEntity* dot = dynamic_cast<DotEntity*>(collisions->at(i)))
		{
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				if (entities->at(i) == dot)
				{
					entities->erase(entities->begin() + i);
					delete dot;
					dotCounter--;
					score += 10;
				}
			}
			continue;
		}
		if (EnergizerEntity* energizer = dynamic_cast<EnergizerEntity*>(collisions->at(i)))
		{
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				if (entities->at(i) == energizer)
				{
					entities->erase(entities->begin() + i);
					delete energizer;
					score += 50;
					energizerCounter--;
					blueGhost->energize();
					redGhost->energize();
					pinkGhost->energize();
					orangeGhost->energize();
				}
			}
			continue;
		}
		if (BonusEntity* bonus = dynamic_cast<BonusEntity*>(collisions->at(i)))
		{
			for (unsigned int i = 0; i < entities->size(); i++)
			{
				if (entities->at(i) == bonus1)
				{
					entities->erase(entities->begin() + i);
					delete bonus1;
					score += 100;
					break;
				}
				if (entities->at(i) == bonus2)
				{
					entities->erase(entities->begin() + i);
					delete bonus2;
					score += 100;
					break;
				}
			}
			continue;
		}

		if (EnemyEntity* ghost = dynamic_cast<EnemyEntity*>(collisions->at(i)))
		{
			int factor = 0;
			switch (ghost->getState())
			{
			case EnemyEntity::NONE:
				pacman->request(PlayerEntity::DIE);
				gameState = PACMANDEAD;
				break;
			case EnemyEntity::DEAD: break;
			case EnemyEntity::ENERGIZED:
				if (blueGhost->getState() == EnemyEntity::DEAD)
				{
					factor++;
				}
				if (pinkGhost->getState() == EnemyEntity::DEAD)
				{
					factor++;
				}
				if (redGhost->getState() == EnemyEntity::DEAD)
				{
					factor++;
				}
				if (orangeGhost->getState() == EnemyEntity::DEAD)
				{
					factor++; 
				}
				score += 100 * pow(2, factor);
				ghost->request(EnemyEntity::DEAD);
				break;
			default: break;
			}
			continue;
		}	
	}
}


// getter
PlayerEntity* MyLevel::getPacman()
{
	return pacman;
}

EnemyEntity* MyLevel::getBlueGhost()
{
	return blueGhost;
}

EnemyEntity* MyLevel::getRedGhost()
{
	return redGhost;
}

EnemyEntity* MyLevel::getOrangeGhost()
{
	return orangeGhost;
}

EnemyEntity* MyLevel::getPinkGhost()
{
	return pinkGhost;
}

MyLevel::GameState MyLevel::getGameStateRequest()
{
	return gameStateRequest;
}


void MyLevel::showScore()
{
	std::string s = std::to_string(score);
	char const *pchar = s.c_str();

	text = Text(font, s.c_str(), new Position(24 * AMP, 272 * AMP), AMP, 255, 255, 255);
}