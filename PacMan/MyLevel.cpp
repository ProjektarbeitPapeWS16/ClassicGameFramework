#include "MyLevel.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "WallEntity.h"
#include "DotEntity.h"
#include "EnergizerEntity.h"
#include "Physics.h"
#include "PacManModel.h"

#define AMP 3

MyLevel::MyLevel(int colsGrid, int rowsGrid, int xTileSize, int yTileSize) 
	: Level(colsGrid, rowsGrid, xTileSize, yTileSize, new Physics())
{
	gameState = NORMAL;
	entities = new std::vector<Entity*>();
	pacman = new PlayerEntity(new Boundaries(106 * AMP, 69 * AMP, 13 * AMP, 13 * AMP));

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
	blueGhost->setState(EnemyEntity::MOVE_UP_1);

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
	redGhost->setState(EnemyEntity::MOVE_LEFT_1);

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
	orangeGhost->setState(EnemyEntity::MOVE_UP_1);

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
	pinkGhost->setState(EnemyEntity::MOVE_DOWN_1);

	entities->push_back(pacman);
	entities->push_back(blueGhost);
	entities->push_back(redGhost);
	entities->push_back(orangeGhost);
	entities->push_back(pinkGhost);



	// Left Wall, from bottom to top
	entities->push_back(new WallEntity("textures/Walls/wallCornerDL5x5.bmp", new Boundaries(0 * AMP, 16 * AMP, 5 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x38.bmp", new Boundaries(0 * AMP, 21 * AMP, 4 * AMP, 38 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall5x10L.bmp", new Boundaries(0 * AMP, 59 * AMP, 5 * AMP, 10 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall15x8L.bmp", new Boundaries(5 * AMP, 60 * AMP, 15 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x38.bmp", new Boundaries(0 * AMP, 69 * AMP, 4 * AMP, 38 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUL5x5.bmp", new Boundaries(0 * AMP, 107 * AMP, 5 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(5 * AMP, 108 * AMP, 35 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerDR4x4.bmp", new Boundaries(40 * AMP, 108 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(40 * AMP, 112 * AMP, 4 * AMP, 24 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUR4x4.bmp", new Boundaries(40 * AMP, 136 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(0 * AMP, 136 * AMP, 40 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(0 * AMP, 156 * AMP, 40 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerDR4x4.bmp", new Boundaries(40 * AMP, 156 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(40 * AMP, 160 * AMP, 4 * AMP, 24 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUR4x4.bmp", new Boundaries(40 * AMP, 184 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(5 * AMP, 184 * AMP, 35 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerDL5x5.bmp", new Boundaries(0 * AMP, 184 * AMP, 5 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x70.bmp", new Boundaries(0 * AMP, 189 * AMP, 4 * AMP, 70 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUL5x5.bmp", new Boundaries(0 * AMP, 259 * AMP, 5 * AMP, 5 * AMP)));

	// Down Wall
	entities->push_back(new WallEntity("textures/Walls/wall214x4.bmp", new Boundaries(5 * AMP, 16 * AMP, 214 * AMP, 4 * AMP)));

	// Upper Wall
	entities->push_back(new WallEntity("textures/Walls/wall102x4.bmp", new Boundaries(5 * AMP, 260 * AMP, 102 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall10x5.bmp", new Boundaries(107 * AMP, 259 * AMP, 10 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x31.bmp", new Boundaries(108 * AMP, 228 * AMP, 8 * AMP, 31 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall102x4.bmp", new Boundaries(117 * AMP, 260 * AMP, 102 * AMP, 4 * AMP)));

	// Right Wall, from bottom to top
	entities->push_back(new WallEntity("textures/Walls/wallCornerDR5x5.bmp", new Boundaries(219 * AMP, 16 * AMP, 5 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x38.bmp", new Boundaries(220 * AMP, 21 * AMP, 4 * AMP, 38 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall5x10R.bmp", new Boundaries(219 * AMP, 59 * AMP, 5 * AMP, 10 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall15x8R.bmp", new Boundaries(204 * AMP, 60 * AMP, 15 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x38.bmp", new Boundaries(220 * AMP, 69 * AMP, 4 * AMP, 38 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUR5x5.bmp", new Boundaries(219 * AMP, 107 * AMP, 5 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(184 * AMP, 108 * AMP, 35 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerDL4x4.bmp", new Boundaries(180 * AMP, 108 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(180 * AMP, 112 * AMP, 4 * AMP, 24 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUL4x4.bmp", new Boundaries(180 * AMP, 136 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(184 * AMP, 136 * AMP, 40 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall40x4.bmp", new Boundaries(184 * AMP, 156 * AMP, 40 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerDL4x4.bmp", new Boundaries(180 * AMP, 156 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(180 * AMP, 160 * AMP, 4 * AMP, 24 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUL4x4.bmp", new Boundaries(180 * AMP, 184 * AMP, 4 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall35x4.bmp", new Boundaries(184 * AMP, 184 * AMP, 35 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerDR5x5.bmp", new Boundaries(219 * AMP, 184 * AMP, 5 * AMP, 5 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x70.bmp", new Boundaries(220 * AMP, 189 * AMP, 4 * AMP, 70 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wallCornerUR5x5.bmp", new Boundaries(219 * AMP, 259 * AMP, 5 * AMP, 5 * AMP)));

	// first row of rectangles from top
	entities->push_back(new WallEntity("textures/Walls/wall24x16.bmp", new Boundaries(20 * AMP, 228 * AMP, 24 * AMP, 16 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall32x16.bmp", new Boundaries(60 * AMP, 228 * AMP, 32 * AMP, 16 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall32x16.bmp", new Boundaries(132 * AMP, 228 * AMP, 32 * AMP, 16 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall24x16.bmp", new Boundaries(180 * AMP, 228 * AMP, 24 * AMP, 16 * AMP)));

	// second row of rectangles from top
	entities->push_back(new WallEntity("textures/Walls/wall24x8.bmp", new Boundaries(20 * AMP, 204 * AMP, 24 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall24x8.bmp", new Boundaries(180 * AMP, 204 * AMP, 24 * AMP, 8 * AMP)));

	// |
	// |-  upper left
	// |
	entities->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(60 * AMP, 189 * AMP, 8 * AMP, 23 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall9x10L.bmp", new Boundaries(60 * AMP, 179 * AMP, 9 * AMP, 10 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(60 * AMP, 156 * AMP, 8 * AMP, 23 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(69 * AMP, 180 * AMP, 23 * AMP, 8 * AMP)));

	// ___ upper mid
	//  |
	entities->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(84 * AMP, 204 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall10x9U.bmp", new Boundaries(107 * AMP, 203 * AMP, 10 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(117 * AMP, 204 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(108 * AMP, 180 * AMP, 8 * AMP, 23 * AMP)));

	//  |
	// -|  upper right
	//  |
	entities->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(156 * AMP, 189 * AMP, 8 * AMP, 23 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall9x10R.bmp", new Boundaries(155 * AMP, 179 * AMP, 9 * AMP, 10 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(156 * AMP, 156 * AMP, 8 * AMP, 23 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(132 * AMP, 180 * AMP, 23 * AMP, 8 * AMP)));

	// TODO box mid
	entities->push_back(new WallEntity("textures/Walls/wall56x4.bmp", new Boundaries(84 * AMP, 132 * AMP, 56 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(84 * AMP, 136 * AMP, 4 * AMP, 24 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall4x24.bmp", new Boundaries(136 * AMP, 136 * AMP, 4 * AMP, 24 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall20x4L.bmp", new Boundaries(84 * AMP, 160 * AMP, 20 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall20x4R.bmp", new Boundaries(120 * AMP, 160 * AMP, 20 * AMP, 4 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall16x4special.bmp", new Boundaries(104 * AMP, 160 * AMP, 16 * AMP, 4 * AMP)));

	// rectangles mid
	entities->push_back(new WallEntity("textures/Walls/wall8x32.bmp", new Boundaries(60 * AMP, 108 * AMP, 8 * AMP, 32 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x32.bmp", new Boundaries(156 * AMP, 108 * AMP, 8 * AMP, 32 * AMP)));

	// ___ mid mid
	//  |
	entities->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(84 * AMP, 108 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall10x9U.bmp", new Boundaries(107 * AMP, 107 * AMP, 10 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(117 * AMP, 108 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(108 * AMP, 84 * AMP, 8 * AMP, 23 * AMP)));

	// __ bottom left
	//  |
	entities->push_back(new WallEntity("textures/Walls/wall15x8R.bmp", new Boundaries(20 * AMP, 84 * AMP, 15 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall9x9L.bmp", new Boundaries(35 * AMP, 83 * AMP, 9 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(36 * AMP, 60 * AMP, 8 * AMP, 23 * AMP)));

	// rectangles bottom
	entities->push_back(new WallEntity("textures/Walls/wall32x8.bmp", new Boundaries(60 * AMP, 84 * AMP, 32 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall32x8.bmp", new Boundaries(132 * AMP, 84 * AMP, 32 * AMP, 8 * AMP)));

	// __ bottom left
	//  |
	entities->push_back(new WallEntity("textures/Walls/wall15x8L.bmp", new Boundaries(189 * AMP, 84 * AMP, 15 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall9x9R.bmp", new Boundaries(180 * AMP, 83 * AMP, 9 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(180 * AMP, 60 * AMP, 8 * AMP, 23 * AMP)));

	// __|_ down left
	entities->push_back(new WallEntity("textures/Walls/wall39x8o--.bmp", new Boundaries(20 * AMP, 36 * AMP, 39 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall10x9D.bmp", new Boundaries(59 * AMP, 36 * AMP, 10 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(69 * AMP, 36 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(60 * AMP, 45 * AMP, 8 * AMP, 23 * AMP)));

	// ___ bottom mid
	//  |
	entities->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(84 * AMP, 60 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall10x9U.bmp", new Boundaries(107 * AMP, 59 * AMP, 10 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8-o.bmp", new Boundaries(117 * AMP, 60 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23u.bmp", new Boundaries(108 * AMP, 36 * AMP, 8 * AMP, 23 * AMP)));

	// _|__ down right
	entities->push_back(new WallEntity("textures/Walls/wall39x8--o.bmp", new Boundaries(165 * AMP, 36 * AMP, 39 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall10x9D.bmp", new Boundaries(155 * AMP, 36 * AMP, 10 * AMP, 9 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall23x8o-.bmp", new Boundaries(132 * AMP, 36 * AMP, 23 * AMP, 8 * AMP)));
	entities->push_back(new WallEntity("textures/Walls/wall8x23n.bmp", new Boundaries(156 * AMP, 45 * AMP, 8 * AMP, 23 * AMP)));

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
}


MyLevel::~MyLevel()
{
}


void MyLevel::gameLoop()
{

	slowit++;
	if (slowit % 3 == 0)
	{

		gamecounter++;
		gamecounter = gamecounter % 16;
		/*
		switch (gamecounter)
		{
		case  0:
		case  1:
		case  2:
		case  3:
		case  4: blueGhost->request(EnemyEntity::MOVE_RIGHT);	break;
		case  5:
		case  6:
		case  7:
		case  8: blueGhost->request(EnemyEntity::MOVE_UP);		break;
		case  9:
		case 10:
		case 11:
		case 12: blueGhost->request(EnemyEntity::MOVE_LEFT);	break;
		case 13:
		case 14:
		case 15:
		default: blueGhost->request(EnemyEntity::MOVE_DOWN);	break;;
		}*/
		pacman->setMemoryRequest();
		pacman->requestPuffer();
		pacman->execute();
		handleCollisions();
		if (gameState == PACMANxWALL)
		{
			pacman->requestMemory();
			pacman->execute();

			handleCollisions();
			gameState = NORMAL;
		}
		if (gameState == PACMANDEAD)
		{
			if (endCounter > 10)
			{
				gameState = RESTARTGAME;//neustart
			}
			endCounter++;
		}
	}
	blueGhost->execute();
}

void MyLevel::handleCollisions()
{
	// TODO entities in PhysicalObjects casten, hier selber machen statt von level beziehen
	std::vector<std::pair<PhysicalObject*, PhysicalObject*>> * collisionPairs = getPhysics()->checkCollisions(this->getPhysicalObjects());

	// Collision detection
	if (collisionPairs)
	{
		int counter = 0; // falls Objekte �bereinander liegen wird nur mit einem kollidiert
		for (unsigned int i = 0; i < (*collisionPairs).size(); i++)
		{
			//bool collided = false;

			Entity* first = static_cast<Entity*>(collisionPairs->at(i).first);
			Entity* second = static_cast<Entity*>(collisionPairs->at(i).second);

			if (PlayerEntity* pacman = dynamic_cast<PlayerEntity*>(first))
			{
				//  pacman collides
				// if collides, has to take a step back
				if (counter == 0)
				{
					if (auto wall = dynamic_cast<WallEntity*>(second))
					{
						counter++;
						pacman->stepBack();
						gameState = PACMANxWALL;
						return;
					}
				}
				if (DotEntity* dot = dynamic_cast<DotEntity*>(second))
				{
					for (int i = 0; i < entities->size(); i++)
					{
						if (entities->at(i) == dot)
						{
							entities->erase(entities->begin() + i);
							delete dot;
							return;
						}
					}
				}
				if (EnergizerEntity* energizer = dynamic_cast<EnergizerEntity*>(second))
				{
					for (int i = 0; i < entities->size(); i++)
					{
						if (entities->at(i) == energizer)
						{
							entities->erase(entities->begin() + i);
							delete energizer;
							return;
						}
					}
				}

				if (EnemyEntity* ghost = dynamic_cast<EnemyEntity*>(second))
				{
					pacman->request(PlayerEntity::DIE);
					gameState = PACMANDEAD;
				}
			}
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