#pragma once
#include "Entity.h"

class GameConfig;

// Oil drum at the bottom of the level; where barrels get destroyed [and fire/foxes] spawned
class Entity_OilDrum : public Entity
{
private:
	unsigned long counter = 0;
public:
	Entity_OilDrum(Position* position);
	Image* spritesheet;	// col1: stand, col2: pound chest, col3: throwbarrel down, col4: throwbarrel right
	//Image* getImage() override;
};
